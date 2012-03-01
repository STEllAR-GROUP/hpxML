//  Copyright (c)        2012 Zach Byerly
//  Copyright (c) 2011 - 2012 Bryce Adelstein-Lelbach 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  This is a 1 dimensional hydrodynamics code, using a simple first-order
//  upwind advection scheme (to keep dependencies simple).  1st order in time.  
//  It employs a predictive timestep method in order to eliminate global 
//  barriers after every timestep. Gravity, if any, is given by a static
//  potential.  A dual-energy formalism is also used to allow for heating
//  in the shocks.  

// INCLUDES
#include <hpx/hpx_init.hpp>
#include <hpx/runtime/actions/plain_action.hpp>
#include <hpx/runtime/components/plain_component_factory.hpp>
#include <hpx/lcos/async.hpp>
#include <hpx/lcos/async.hpp>
#include <hpx/lcos/async_future_wait.hpp>
#include <hpx/include/iostreams.hpp>

#include <boost/format.hpp>
#include <boost/math/constants/constants.hpp>

using hpx::naming::id_type;
using hpx::naming::invalid_id;

using hpx::actions::plain_result_action2;

using hpx::lcos::promise;
using hpx::lcos::async;
using hpx::lcos::wait;
using hpx::lcos::eager_future;

using hpx::util::high_resolution_timer;

using boost::program_options::variables_map;
using boost::program_options::options_description;
using boost::program_options::value;

using hpx::init;
using hpx::finalize;
using hpx::find_here;

using hpx::cout;
using hpx::flush;


// USING STATEMENTS

////////////////////////////////////////
// globals

// initialized in hpx_main
boost::uint64_t nt = 0;
boost::uint64_t nx = 0;
boost::uint64_t n_predict = 0;
double fluid_gamma = 0.0;
double x_min = 0.0;
double x_max = 0.0;
double dx = 0.0;
double cfl_factor = 0.0;
double cfl_predict_factor = 0.0;


// this is a single element of a "time array" that will be 1D array
// containing information about timestep size. the index will be 
// the integer timestep number, so time_array[timestep].dt will be 
// the timestep size at that timestep
struct time{
  // default constructor
  time()
    : mtx()
    , dt(0.0)
    , elapsed_time(0.0)
    , computed(false)
  {}
  
  // copy constructor
  time(
       time const& other
       )
    : mtx()
    , dt(other.dt)                     // timestep size
    , elapsed_time(other.elapsed_time) // elapsed time
    , computed(other.computed)
  {}

  hpx::lcos::local_mutex mtx;
  double dt;
  double elapsed_time;
  bool computed;
}
// declaring time_array
  std::vector<time> time_array;


// this is the fundimental element of the hydrodynamics code, the 
// individual cell.  It stores all of the variables that the code 
// tracks their changes in time.  
struct cell{
  // default constructor
  cell()
    : mtx()
    , rho(0.0)    // mass density
    , mom(0.0)    // momentum density
    , etot(0.0)   // total energy density
    , tau(0.0)   // internal energy density (etot - kinetic energy)
    , computed(false)
  {}

  // copy constructor
  cell(
       cell const& other
       )
    : mtx()
    , rho(other.rho)
    , mom(other.mom)
    , etot(other.etot)
    , tau(other.tau)
    , computed(other.computed)
  {}

  hpx::lcos::local_mutex mtx;
  double rho;
  double mom;
  double etot;
  double tau;
  bool computed;
};
  
// declaring grid of all cells for all timesteps
std::vector<std::vector<cell> > grid;

// forward declaration of the compute function
cell compute(boost::uint64_t timestep, boost::uint64_t location);
double timestep_size(uint64_t timestep);
cell initial_sod(boost::uint64_t location);
double get_pressure(cell input);  

// Wrapping in plain_action
typedef plain_result_action2<
  // result type
  cell,

  // arguments 
  boost::uint64_t,
  boost::uint64_t,

  // function
  compute
  > compute_action;

// This generates the required boilerplate we need for remote invocation.
HPX_REGISTER_PLAIN_ACTION(compute_action);

typedef eager_future<compute_action> compute_future;

// this will return the timestep size.  The timestep index will refer to the 
// timestep where it will be USED rather than the timestep where it was 
// calculated.
double timestep_size(uint64_t timestep)
{
  // locking
  hpx::lcos::local_mutex::scoped_lock l(time_array[timestep].mtx);

  // if it has already been calculated, then just return the value
  if (time_array[timestep].calculated)
    return time_array[timestep].dt;

  // if the current timestep is less than n_predict, then we manually
  // decide the timestep
  if (timestep < n_predict)
    {
      time_array[timestep].computed = true;
      time_array[timestep].dt = 0.0001;// we could actually use 
      //the initial conditions to determine this value at runtime
      return time_array[timestep].dt;
    }

  // send back the compute futures for the whole grid
  // n_predict timesteps previous to the one we want to decide
  // the timestep for
  std::vector<promise<cell> > futures;
  for (boost::uint64_t i=0;i<nx;i++)
    futures.push_back(async<compute_action>(here,timestep-n_predict,i));

  // initialize dt_cfl to some arbitrary high value
  double dt_cfl = 1000.0;

  // wait for an array of futures
  wait(futures, [&](std::size_t i, cell this_cell))
    {         
      // look at all of the cells at a timestep, then pick the smallest
      // dt_cfl = cfl_factor*dx/(soundspeed+absolute_velocity)
      double abs_velocity = this_cell.mom/this_cell.rho;
      double pressure = get_pressure(this_cell);
      double soundspeed = sqrt(fluid_gamma*pressure/this_cell.rho);
      double dt_cfl_here = cfl_factor*dx/(soundspeed+abs_velocity);
      if (dt_cfl_here < 0.0) 
        {
          //error, quit everything
        }        
      if (dt_cfl_here < dt_cfl)
        dt_cfl = dt_cfl_here;
      
      
      if (dt_cfl > 999.0) 
        {
          // error, quit everything
        }
      
      // we don't want to let the timestep increase too quickly, so
      // we only let it increase by 50% each timestep
      time_array[timestep].computed = true;
      time_array[timestep].dt = min(
                                    cfl_predict_factor*dt_cfl 
                                    , 
                                    1.5*time_array[timestep-1].dt);
      return time_array[timestep].dt;
    }   
}

cell compute(boost::uint64_t timestep, boost::uint64_t location);
{
  hpx::lcos::local_mutex::scoped_lock l(grid[timestep][location].mtx);
  
  // if it is already computed then just return the value
  if (grid[timestep][location].computed = true)
    return grid[timestep][location];

  // we are going to compute it now!
  grid[timestep][location].computed = true;

  //initial values
  if (t == 0)
    {
      grid[timestep][location] = initial_sod(location);
      return grid[timestep][location];
    }  

  //boundary conditions (using sod shock tube boundaries)
  if ( (location == 0) or (location == nx-1) )
    {
      grid[timestep][location] = initial_sod(location);
      return grid[timestep][location];
    }

  //now we have to actually compute some values. 

  //these are the dependencies, or "stencil" 
  compute_future nleft(here,timestep-1,location-1);
  compute_future nmiddle(here,timestep-1,location);
  compute_future nright(here,timestep-1,location+1);

  // OR is this the correct way to do it?
  //promise<cell> left;
  //left = async<compute_action>(here,timestep-1,location-1);
  //promise<cell> middle;
  //middle = async<compute_action>(here,timestep-1,location);
  //promise<cell> right;
  //right = async<compute_action>(here,timestep-1,location+1);

  // calling this function may or may not make futures
  double dt = timestep_size(timestep);

  cell now;

  cell left   = nleft.get();
  cell middle = nmiddle.get();
  cell right  = nright.get();

  // now that we have all of the information we need, we can proceed with
  // the physics part of the update
  
  // first we will calculate the advection of all of the variables 
  // through the left face of the cell.
  // start by calculating the velocity on the left face
  // if this velocity is positive, then fluid flows from the cell to the left.
  // if it is negative, fluid flows out of the middle cell.
  double velocity_left = (left.mom+middle.mom)/(left.rho+middle.rho);
  if (velocity_left > 0.0)
    {
      now.rho +=  left.rho*velocity_left*dt/dx;
      now.mom +=  left.mom*velocity_left*dt/dx;
      now.etot += left.etot*velocity_left*dt/dx;
      now.tau +=  left.tau*velocity_left*dt/dx;
    }
  else
    {
      now.rho +=  middle.rho*velocity_left*dt/dx;
      now.mom +=  middle.mom*velocity_left*dt/dx;
      now.etot += middle.etot*velocity_left*dt/dx;
      now.tau +=  middle.tau*velocity_left*dt/dx;
    }

  // now repeat the process for the right side
  double velocity_right = (right.mom+middle.mom)/(right.rho+middle.rho);
  if (velocity_right < 0.0)
    {
      now.rho -=  right.rho*velocity_right*dt/dx;
      now.mom -=  right.mom*velocity_right*dt/dx;
      now.etot -= right.etot*velocity_right*dt/dx;
      now.tau -=  right.tau*velocity_right*dt/dx;
    }
  else
    {
      now.rho -=  middle.rho*velocity_right*dt/dx;
      now.mom -=  middle.mom*velocity_right*dt/dx;
      now.etot -= middle.etot*velocity_right*dt/dx;
      now.tau -=  middle.tau*velocity_right*dt/dx;
    }

  // source terms 
  // dmom/dt = 1/rho *dp/dx
  double right_pressure = get_pressure(right);
  double left_pressure = get_pressure(left);
  double middle_pressure = get_pressure(middle);
  now.mom += dt*(left_pressure - right_pressure)/(middle.rho*dx);
  now.eint -= middle_pressure*(left.mom/left.rho - right.mom/right.rho)*dt/dx;

  //dual energy formalism
  double e_kinetic = 0.5*middle.mom*middle.mom/middle.rho;
  double e_internal = middle.etot - e_kinetic;
  if ( abs(e_internal) > 0.1*middle.etot) 
    new.tau = pow(e_internal,1.0/fluid_gamma)

}  

double get_pressure(cell input)
{
  double e_kinetic = 0.5*input.mom*input.mom/input.rho;
  double e_internal = input.etot - e_kinetic;
  if ( (input.etot - e_kinetic) > 0.001*input.etot )
    pressure = (fluid_gamma-1.0)*(input.etot - e_kinetic)
  else
    pressure = (fluid_gamma-1.0)*pow(input.tau,fluid_gamma);

  return pressure;
}

cell initial_sod(boost::uint64_t location)
{
  // calculate what the x coordinate is here
  double x_here = (location-0.5)*dx+x_min;
  
  cell cell_here;
  double e_internal = 0.0;

  // This is the Sod Shock Tube problem, which has a known analytical
  // solution.  A mass and energy contact discontinuity is placed on the grid.
  // A shockwave then forms and propogates through the grid.
  if (x_here < 0.1) 
    {
      cell_here.rho = 1.0;
      e_internal = 2.5;
    }
  else
    {
      cell_here.rho = 0.125;
      e_internal = 0.25;      
    }

  cell_here.mom = 0.0;
  cell_here.tau = pow(e_internal,(1.0/fluid_gamma));
  cell_here.etot = e_internal;  // ONLY true when mom=0, not in general!
  

}
///////////////////////////////////////////////////////////////////////////////
int hpx_main(
    variables_map& vm
    )
{
    
  here = find_here();
  
  // some physics parameters
  nt = 100;
  nx = 100;
  fluid_gamma = 1.4;
  
  x_min = -0.5;
  x_max = 0.5;
  dx = (x_max - x_min)/(nx-2);

  cfl_factor = 0.5;
  cfl_predict_factor = 0.8;
  n_predict = 10;

  cout << (boost::format("nt = %1%\n") % nt) << flush;
  cout << (boost::format("nx = %1%\n") % nx) << flush;

  // allocating the time array
  time_array = std::vector<time>(nt);
  
  // allocating the grid 2d array of all of the cells for all timesteps
  grid = std::vector<std::vector<cell> >(nt, std::vector<cell>(nx));

  {
    //HPX stuff goes here

    // Keep track of the time required to execute.
    high_resolution_timer t;

    std::vector<promise<cell> > futures;
    for (boost::uint64_t i=0;i<nx;i++)
      futures.push_back(async<compute_action>(here,nt-1,i));
    
    // open file for output
    std::ofstream outfile;
    outfile.open ("output.dat");

    wait(futures, [&](std::size_t i, cell n)
         { double x_here = (location-0.5)*dx+x_min;
           outfile << (boost::format("%1% %2%\n") % x_here % n.rho) << flush; });

    outfile.close();

    char const* fmt = "elapsed time: %1% [s]\n";
    std::cout << (boost::format(fmt) % t.elapsed());
    
  }

    finalize();
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
int main(
    int argc
  , char* argv[]
    )
{
    // Configure application-specific options.
    options_description cmdline("usage: " HPX_APPLICATION_STRING " [options]");

    // Initialize and run HPX.
    return init(cmdline, argc, argv);
}


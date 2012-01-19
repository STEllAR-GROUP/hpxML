//  Copyright (c) 2011 Matthew Anderson
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/applier/applier.hpp>
#include <hpx/runtime/threads/thread.hpp>
#include <hpx/runtime/components/component_type.hpp>
#include <hpx/runtime/components/server/managed_component_base.hpp>
#include <hpx/runtime/actions/component_action.hpp>
#include <hpx/lcos/eager_future.hpp>
#include <hpx/lcos/async_future_wait.hpp>
#include <hpx/include/iostreams.hpp>

#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/lexical_cast.hpp>

#include "point.hpp"
#include "../stubs/point.hpp"

#include <string>
#include <sstream>
#include <fstream>

double unifRand() {
  return rand()/double(RAND_MAX);
}
double unifRand(double a,double b)
{
  return (b-a)*unifRand() + a;
}

///////////////////////////////////////////////////////////////////////////////
namespace gtc { namespace server
{
    void point::init(std::size_t objectid,parameter const& par)
    {
        idx_ = objectid;

        tauii_ = -1.0; // initially collisionless

        // initial mesh
        particle_domain_location_=objectid%par->npartdom;
        toroidal_domain_location_=objectid/par->npartdom;
        pi_ = 4.0*atan(1.0);
   
        // Domain decomposition in toroidal direction
        mzeta_ = par->mzetamax/par->ntoroidal;
        double tmp1 = (double) toroidal_domain_location_;
        double tmp2 = (double) par->ntoroidal;
        double tmp3 = (double) (toroidal_domain_location_+1);
        zetamin_ = 2.0*pi_*tmp1/tmp2;
        zetamax_ = 2.0*pi_*tmp3/tmp2;

        double tmp4 = (double) mzeta_;
        deltaz_ = (zetamax_-zetamin_)/tmp4;

        myrank_toroidal_ = objectid;
        left_pe_ = (myrank_toroidal_-1+par->ntoroidal)% par->ntoroidal;
        right_pe_ = (myrank_toroidal_+1)% par->ntoroidal;

        qtinv_.resize(par->mpsi+1);
        itran_.resize(par->mpsi+1);
        mtheta_.resize(par->mpsi+1);
        deltat_.resize(par->mpsi+1);
        rtemi_.resize(par->mpsi+1);
        rteme_.resize(par->mpsi+1);
        rden_.resize(par->mpsi+1);
        igrid_.resize(par->mpsi+1);
        pmarki_.resize(par->mpsi+1);
        pmarke_.resize(par->mpsi+1);
        phi00_.resize(par->mpsi+1);
        phip00_.resize(par->mpsi+1);
        hfluxpsi_.resize(par->mpsi+1);
        zonali_.resize(par->mpsi+1);
        zonale_.resize(par->mpsi+1);
        gradt_.resize(par->mpsi+1);
        eigenmode_.resize(par->m_poloidal,par->num_mode,par->mpsi);

        // --- Define poloidal grid ---
        double tmp5 = (double) par->mpsi;
        deltar_ = (par->a1-par->a0)/tmp5;

        // grid shift associated with fieldline following coordinates
        double tmp6 = (double) par->mthetamax;
        double tdum = 2.0*pi_*par->a1/tmp6;

        // initial data
        for (std::size_t i=0;i<par->mpsi+1;i++) {
          double r = par->a0 + deltar_*i;
          std::size_t two = 2;
          double tmp7 = pi_*r/tdum + 0.5;
          std::size_t tmp8 = (std::size_t) tmp7;
          mtheta_[i] = (std::max)(two,(std::min)(par->mthetamax,two*tmp8)); // even # poloidal grid
          deltat_[i] = 2.0*pi_/mtheta_[i];
          double q = par->q0 + par->q1*r/par->a + par->q2*r*r/(par->a*par->a);
          double tmp9 = mtheta_[i]/q + 0.5;
          std::size_t tmp10 = (std::size_t) tmp9;
          itran_[i] = tmp10;
          double tmp11 = (double) mtheta_[i];
          double tmp12 = (double) itran_[i];
          qtinv_[i] = tmp11/tmp12;  // q value for coordinate transformation
          qtinv_[i] = 1.0/qtinv_[i]; // inverse q to avoid divide operation
          itran_[i] = itran_[i] - mtheta_[i]*(itran_[i]/mtheta_[i]);
        }

        // When doing mode diagnostics, we need to switch from the field-line following
        // coordinates alpha-zeta to a normal geometric grid in theta-zeta. This
        // translates to a greater number of grid points in the zeta direction, which
        // is mtdiag. Precisely, mtdiag should be mtheta/q but since mtheta changes
        // from one flux surface to another, we use a formula that gives us enough
        // grid points for all the flux surfaces considered.
        mtdiag_ = (par->mthetamax/par->mzetamax)*par->mzetamax;
        if ( par->nonlinear > 0.5 ) mtdiag_ = mtdiag_/2;

        // starting point for a poloidal grid
        igrid_[0] = 1;
        for (std::size_t i=1;i<par->mpsi+1;i++) {
          igrid_[i] = igrid_[i-1]+mtheta_[i-1]+1;
        }

        // number of grids on a poloidal plane
        mgrid_ = 0;
        for (std::size_t i=0;i<mtheta_.size();i++) {
          mgrid_ += mtheta_[i] + 1;
        }
        std::size_t mi_local = par->micell*(mgrid_-par->mpsi)*mzeta_;  // # of ions in toroidal domain
        mi_ = par->micell*(mgrid_-par->mpsi)*mzeta_/par->npartdom; // # of ions per processor
        if ( mi_ <  (mi_local%par->npartdom) ) mi_++;
        std::size_t me_local = par->mecell*(mgrid_-par->mpsi)*mzeta_;  // # of electrons in toroidal domain
        std::size_t me_ = par->mecell*(mgrid_-par->mpsi)*mzeta_/par->npartdom; // # of electrons per processor
        if ( me_ < (me_local%par->npartdom) ) me_++;

        double tmp13 = (double) mi_;
        double tmp14 = (double) me_;
        std::size_t mimax = static_cast<std::size_t>(mi_ + 100*std::ceil(sqrt(tmp13))); // ions array upper bound
        std::size_t memax = static_cast<std::size_t>(me_ + 100*std::ceil(sqrt(tmp14))); // electrons array upper bound

        pgyro_.resize(5,mgrid_+1,1);
        tgyro_.resize(5,mgrid_+1,1);
        markeri_.resize(mzeta_+1,mgrid_+1,1);
        densityi_.resize(mzeta_+1,mgrid_+1,1);
        densitye_.resize(mzeta_+1,mgrid_+1,1);
        phi_.resize(mzeta_+1,mgrid_+1,1);
        evector_.resize(4,mzeta_+1,mgrid_+1);
        recvls_.resize(4,mgrid_+1,1);
        jtp1_.resize(3,mgrid_,mzeta_+1);
        jtp2_.resize(3,mgrid_,mzeta_+1);
        wtp1_.resize(3,mgrid_,mzeta_+1);
        wtp2_.resize(3,mgrid_,mzeta_+1);
        dtemper_.resize(mgrid_,mzeta_,1);
        heatflux_.resize(mgrid_,mzeta_,1);

        phitmp_.resize(mzeta_+1,mgrid_+1,1);

        pfluxpsi_.resize(par->mflux);
        rdtemi_.resize(par->mflux);
        rdteme_.resize(par->mflux);

        // initialize arrays
        // temperature and density on the grid, T_i=n_0=1 at mid-radius
        std::fill( rtemi_.begin(),rtemi_.end(),1.0);
        std::fill( rteme_.begin(),rteme_.end(),1.0);
        std::fill( rden_.begin(),rden_.end(),1.0);
        std::fill( phip00_.begin(),phip00_.end(),0.0);
        std::fill( zonali_.begin(),zonali_.end(),0.0);
        std::fill( zonale_.begin(),zonale_.end(),0.0);
        for (std::size_t i=0;i<phi_.size();i++) {
          phi_[i] = 0.0;
        }
        std::fill( pfluxpsi_.begin(),pfluxpsi_.end(),0.0);
        std::fill( rdtemi_.begin(),rdtemi_.end(),0.0);
        std::fill( rdteme_.begin(),rdteme_.end(),0.0);

        // # of marker per grid, Jacobian=(1.0+r*cos(theta+r*sin(theta)))*(1.0+r*cos(theta))
        std::fill( pmarki_.begin(),pmarki_.end(),0.0);

        for (std::size_t i=0;i<par->mpsi+1;i++) {
          double r = par->a0 + deltar_*i;
          for (std::size_t j=1;j<=mtheta_[i];j++) {
            std::size_t ij = igrid_[i] + j;
            for (std::size_t k=1;k<=mzeta_;k++) {
              double zdum = zetamin_ + k*deltaz_;
              double tdum = j*deltat_[i]+zdum*qtinv_[i];
              markeri_(k,ij,0) = pow(1.0+r*cos(tdum),2);
              pmarki_[i] = pmarki_[i] + markeri_(k,ij,0);
            }
          }
          double rmax = (std::min)(par->a1,r+0.5*deltar_);
          double rmin = (std::max)(par->a0,r-0.5*deltar_);
          double tmp15 = (double) mi_*par->npartdom;
          tdum = tmp15*(rmax*rmax-rmin*rmin)/(par->a1*par->a1-par->a0*par->a0);
          for (std::size_t j=1;j<=mtheta_[i];j++) {
            std::size_t ij = igrid_[i] + j;
            for (std::size_t k=1;k<=mzeta_;k++) {
              markeri_(k,ij,0) = tdum*markeri_(k,ij,0)/pmarki_[i];
              markeri_(k,ij,0) = 1.0/markeri_(k,ij,0);
            }
          }
          pmarki_[i] = 1.0/(par->ntoroidal*tdum);
          for (std::size_t j=0;j<markeri_.isize();j++) {
            markeri_(j,igrid_[i],0) = markeri_(j,igrid_[i]+mtheta_[i],0);
          }
        }
        std::size_t nparam;
        if ( par->track_particles ) {
          // Not implemented yet
          nparam = 7;
        } else {
          // No tagging of the particles
          nparam = 6;
        }
        zion_.resize(nparam+1,mimax+1,1);
        zion0_.resize(nparam+1,mimax+1,1);
        jtion0_.resize(nparam+1,mimax+1,1);
        jtion1_.resize(5,mimax+1,1);
        kzion_.resize(mimax+1);
        wzion_.resize(mimax+1);
        wpion_.resize(5,mimax+1,1);
        wtion0_.resize(5,mimax+1,1);
        wtion1_.resize(5,mimax+1,1);

        if ( par->nhybrid > 0 ) {
          BOOST_ASSERT(false);
          // not implemented yet
        }

        // 4-point gyro-averaging for sqrt(mu)=gyroradius on grid of magnetic coordinates
        // rho=gyroradius*sqrt(2/(b/b_0))*sqrt(mu/mu_0), mu_0*b_0=m*v_th^2
        // dtheta/delta_x=1/(r*(1+r*cos(theta))), delta_x=poloidal length increase
        for (std::size_t i=0;i<par->mpsi+1;i++) {
          double r = par->a0 + deltar_*i;
          for (std::size_t j=0;j<=mtheta_[i];j++) {
            std::size_t ij = igrid_[i] + j;
            double tdum = deltat_[i]*j;
            double b = 1.0/(1.0+r*cos(tdum));
            double dtheta_dx = 1.0/r;
            // first two points perpendicular to field line on poloidal surface
            double rhoi = sqrt(2.0/b)*par->gyroradius;

            pgyro_(1,ij,0) = -rhoi;
            pgyro_(2,ij,0) = rhoi;
            // non-orthorgonality between psi and theta: tgyro=-rhoi*dtheta_dx*r*sin(tdum)
            tgyro_(1,ij,0) = 0.0;
            tgyro_(2,ij,0) = 0.0;

            // the other two points tangential to field line
            tgyro_(3,ij,0) = -rhoi*dtheta_dx;
            tgyro_(4,ij,0) = rhoi*dtheta_dx;
            pgyro_(3,ij,0) = rhoi*0.5*rhoi/r;
            pgyro_(4,ij,0) = rhoi*0.5*rhoi/r;
          }
        }

        // initiate radial interpolation for grid
        for (std::size_t k=1;k<=mzeta_;k++) {
          double zdum = zetamin_ + k*deltaz_;
          for (std::size_t i=1;i<par->mpsi;i++) {
            for (std::size_t ip=1;ip<=2;ip++) {
              std::size_t indp = (std::min)(par->mpsi,i+ip);
              double tmp = (std::max)(0.0,(double) i-ip);
              std::size_t indt = (std::size_t) tmp;
              for (std::size_t j=1;j<=mtheta_[i];j++) {
                std::size_t ij = igrid_[i] + j;
// upward
                double tdum = (j*deltat_[i]+zdum*(qtinv_[i]-qtinv_[indp]))/deltat_[indp];
                std::size_t jt = static_cast<std::size_t>(floor(tdum));
                double wt = tdum - jt;
                jt = (jt+mtheta_[indp])%(mtheta_[indp]);
                if ( ip == 1 ) {
                  wtp1_(1,ij,k) = wt;
                  jtp1_(1,ij,k) = static_cast<double>(igrid_[indp] + jt);
                } else {
                  wtp2_(1,ij,k) = wt;
                  jtp2_(1,ij,k) = static_cast<double>(igrid_[indp] + jt);
                }
// downward
                tdum = (j*deltat_[i]+zdum*(qtinv_[i]-qtinv_[indt]))/deltat_[indt];
                jt = static_cast<std::size_t>(floor(tdum));
                wt = tdum - jt;
                jt = (jt+mtheta_[indt])%mtheta_[indt];
                if ( ip == 1 ) {
                  wtp1_(2,ij,k) = wt;
                  jtp1_(2,ij,k) = static_cast<double>(igrid_[indt] + jt);
                } else {
                  wtp2_(2,ij,k) = wt;
                  jtp2_(2,ij,k) = static_cast<double>(igrid_[indt] + jt);
                }
              }
            }
          }
        }

    }

    void point::load(std::size_t objectid,parameter const& par)
    {
      // initialize random number generator
      srand((unsigned int)(objectid+5));

      double rmi = 1.0/(mi_*par->npartdom);
      double pi2_inv = 0.5/pi_;
      double w_initial = 1.0e-3;
      if ( par->nonlinear < 0.5 ) w_initial = 1.0e-12;
      std::size_t ntracer = 0;
      if ( objectid == 0 ) ntracer = 1;

      for (std::size_t m=1;m<=mi_;m++) {
        zion_(1,m,0) = sqrt(par->a0*par->a0 + ( (m+objectid*mi_)-0.5 )*(par->a1*par->a1-par->a0*par->a0)*rmi);
      } 

      if ( par->track_particles ) BOOST_ASSERT(false); // not implemented yet 

      // Set zion(2:6,1:mi) to uniformly distributed random values between 0 and 1
      // set random zion 
      for (std::size_t i=2;i<=6;i++) {
        for (std::size_t j=1;j<=mi_;j++) {
          zion_(i,j,0) = unifRand(0,1);
        }
      }

      // poloidal: uniform in alpha=theta_0+r*sin(alpha_0), theta_0=theta+r*sin(theta)
      for (std::size_t m=1;m<=mi_;m++) {
        zion_(2,m,0) = 2.0*pi_*(zion_(2,m,0)-0.5);
        zion0_(2,m,0) = zion_(2,m,0); // zion0(2,:) for temporary storage
      }

      for (std::size_t i=1;i<=10;i++) {
        for (std::size_t m=1;m<=mi_;m++) {
          zion_(2,m,0) = zion_(2,m,0)*pi2_inv+10.0; // period of 1
          zion_(2,m,0) = 2.0*pi_*(zion_(2,m,0)-floor(zion_(2,m,0)));
        }
      }

      // Maxwellian distribution in v_para, <v_para^2>=1.0, use zion0(4,:) as temporary storage
      double SMALL = 1.e-20;
      double c0 = 2.515517;
      double c1 = 0.802853;
      double c2 = 0.010328;
      double d1 = 1.432788;
      double d2 = 0.189269;
      double d3 = 0.001308;

      for (std::size_t m=1;m<=mi_;m++) {
        double z4tmp = zion_(4,m,0);
        zion_(4,m,0) = zion_(4,m,0)-0.5;
        if ( zion_(4,m,0) > 0.0 ) zion0_(4,m,0) = 1.0;
        else zion0_(4,m,0) = -1.0;
        zion_(4,m,0) = sqrt( (std::max)(SMALL,log(1.0/(std::max)(SMALL,pow(zion_(4,m,0),2)))));
        zion_(4,m,0) = zion_(4,m,0) - (c0+c1*zion_(4,m,0)+c2*pow(zion_(4,m,0),2))/
                                    (1.0+d1*zion_(4,m,0)+d2*pow(zion_(4,m,0),2)+d3*pow(zion_(4,m,0),3));
        if ( zion_(4,m,0) > par->umax ) zion_(4,m,0) = z4tmp;
      }

      for (std::size_t m=1;m<=mi_;m++) {
        // toroidal:  uniformly distributed in zeta
        zion_(3,m,0) = zetamin_+(zetamax_-zetamin_)*zion_(3,m,0);
        zion_(4,m,0) = zion0_(4,m,0)*(std::min)(par->umax,zion_(4,m,0));

        // initial random weight
        zion_(5,m,0) = 2.0*w_initial*(zion_(5,m,0)-0.5)*(1.0+cos(zion_(2,m,0)));

        // Maxwellian distribution in v_perp, <v_perp^2>=1.0
        zion_(6,m,0) = (std::max)(SMALL,(std::min)(par->umax*par->umax,-log((std::max)(SMALL,zion_(6,m,0)))));
      }

      // transform zion(1,:) to psi, zion(4,:) to rho_para, zion(6,:) to sqrt(mu)
      double vthi = par->gyroradius*abs(par->qion)/par->aion;
      for (std::size_t m=1;m<=mi_;m++) {
        zion0_(1,m,0) = 1.0/(1.0+zion_(1,m,0)*cos(zion_(2,m,0))); // B-field
        zion_(1,m,0) = 0.5*zion_(1,m,0)*zion_(1,m,0);
        zion_(4,m,0) = vthi*zion_(4,m,0)*par->aion/(par->qion*zion0_(1,m,0));
        zion_(6,m,0) = sqrt(par->aion*vthi*vthi*zion_(6,m,0)/zion0_(1,m,0));
      }

      if ( objectid == 0 ) {
        zion_(1,ntracer,0) = 0.5*pow((0.5*(par->a0+par->a1)),2);
        zion_(2,ntracer,0) = 0.0;
        zion_(3,ntracer,0) = 0.5*(zetamin_+zetamax_);
        zion_(4,ntracer,0) = 0.5*vthi*par->aion/par->qion;
        zion_(5,ntracer,0) = 0.0;
        zion_(6,ntracer,0) = sqrt(par->aion*vthi*vthi);
      }

      if ( par->iload == false ) {
        for (std::size_t m=1;m<=mi_;m++) {
          zion0_(6,m,0) = 1.0;
        }
      } else {
        std::cerr << " Not implemented yet " << std::endl;
      }

      if ( par->nhybrid > 0 ) {
        std::cerr << " Not implemented yet " << std::endl;
      }
    }

    void point::chargei(std::size_t istep, std::vector<hpx::naming::id_type> const& point_components, parameter const& par)
    {

      double delr = 1.0/deltar_;
      double delz = 1.0/deltaz_;
      std::vector<double> delt;
      delt.resize( deltat_.size() );
      for (std::size_t i=0;i<deltat_.size();i++) {
        delt[i] = 2.0*pi_/deltat_[i];
      }
      double smu_inv = sqrt(par->aion)/(abs(par->qion)*par->gyroradius);
      double pi2_inv = 0.5/pi_;
      for (std::size_t i=0;i<=mzeta_;i++) {
        for (std::size_t j=0;j<=mgrid_;j++) {
          densityi_(i,j,0) = 0.0;
        }
      }
      std::size_t zero = 0;

      for (std::size_t m=1;m<=mi_;m++) {
        double psitmp = zion_(1,m,0);
        double thetatmp = zion_(2,m,0);
        double zetatmp = zion_(3,m,0);
        double rhoi = zion_(6,m,0)*smu_inv;

        double r = sqrt(2.0*psitmp);
        std::size_t tmp = (std::size_t) ((r-par->a0)*delr+0.5);
        double dip = (std::max)(0.0,(double) (std::min)(par->mpsi,tmp));
        std::size_t ip = (std::size_t) dip;
        std::size_t tmp2 = (std::size_t) (thetatmp*pi2_inv*delt[ip]+0.5);
        double djt = (std::max)(0.0,(double) (std::min)(mtheta_[ip],tmp2));
        std::size_t jt = (std::size_t) djt;
        std::size_t ipjt = igrid_[ip] + jt;

        double wz1 = (zetatmp-zetamin_)*delz;
        std::size_t kk = (std::max)(zero,(std::min)(par->mpsi-1,(std::size_t) wz1));
        kzion_[m] = static_cast<double>(kk);
        wzion_[m] = wz1 - kk;

        for (std::size_t larmor=1;larmor<=4;larmor++) {
          double rdum = delr*(std::max)(0.0,(std::min)(par->a1-par->a0,r+rhoi*pgyro_(larmor,ipjt,0)-par->a0));
          std::size_t ii = (std::max)(zero,(std::min)(par->mpsi-1,(std::size_t) rdum));
          double wp1 = rdum - ii;
          wpion_(larmor,m,0) = wp1;

          // particle position in theta
          double tflr = thetatmp + rhoi*tgyro_(larmor,ipjt,0);

          // inner flux surface
          std::size_t im = ii;
          double tdum = pi2_inv*(tflr-zetatmp*qtinv_[im])+10.0;
          tdum = (tdum - floor(tdum))*delt[im];
          std::size_t j00 = (std::max)(zero,(std::min)(mtheta_[im]-1,(std::size_t) tdum));
          jtion0_(larmor,m,0) = static_cast<double>(igrid_[im] + j00);
          wtion0_(larmor,m,0) = tdum - j00;

          // outer flux surface
          im = ii;
          tdum = pi2_inv*(tflr-zetatmp*qtinv_[im])+10.0;
          tdum = (tdum - floor(tdum))*delt[im];
          std::size_t j01 = (std::max)(zero,(std::min)(mtheta_[im]-1,(std::size_t) tdum));
          jtion1_(larmor,m,0) = static_cast<double>(igrid_[im] + j01);
          wtion1_(larmor,m,0) = tdum - j01;
        }
      }

      if ( istep == 0 ) return;

      for (std::size_t m=1;m<=mi_;m++) {
        double weight = zion_(5,m,0);

        std::size_t kk = static_cast<std::size_t>(kzion_[m]);
        double wz1 = weight*wzion_[m];
        double wz0 = weight-wz1;

        for (std::size_t larmor=1;larmor<=4;larmor++) {
          double wp1 = wpion_(larmor,m,0);
          double wp0 = 1.0-wp1;

          double wt10 = wp0*wtion0_(larmor,m,0);
          double wt00 = wp0 - wt10;

          double wt11 = wp1*wtion1_(larmor,m,0);
          double wt01 = wp1-wt11;

          std::size_t ij = static_cast<std::size_t>(jtion0_(larmor,m,0));
          densityi_(kk,ij,0) = densityi_(kk,ij,0) + wz0*wt00;
          densityi_(kk+1,ij,0) = densityi_(kk+1,ij,0) + wz1*wt00;

          ij = ij + 1;
          densityi_(kk,ij,0) = densityi_(kk,ij,0) + wz0*wt10;
          densityi_(kk+1,ij,0)   = densityi_(kk+1,ij,0)   + wz1*wt10;

          ij = static_cast<std::size_t>(jtion1_(larmor,m,0));
          densityi_(kk,ij,0) = densityi_(kk,ij,0) + wz0*wt01;
          densityi_(kk+1,ij,0)   = densityi_(kk+1,ij,0)   + wz1*wt01;

          ij = ij + 1;
          densityi_(kk,ij,0) = densityi_(kk,ij,0) + wz0*wt11;
          densityi_(kk+1,ij,0)   = densityi_(kk+1,ij,0)   + wz1*wt11;
        }
      }

      if ( par->npartdom > 1 ) {
        std::cerr << " Not implemented yet " << std::endl;
        BOOST_ASSERT(false);
      }

      // poloidal end cell, discard ghost cell j=0
      for (std::size_t i=0;i<=par->mpsi;i++) {
        for (std::size_t j=0;j<densityi_.isize();j++) {
          densityi_(j,igrid_[i]+mtheta_[i],0) = densityi_(j,igrid_[i]+mtheta_[i],0) + densityi_(j,igrid_[i],0);
        }
      }

      // send densityi to the left; receive from the right
      {
        typedef std::vector<hpx::lcos::promise< std::valarray<double> > > lazy_results_type;
        lazy_results_type lazy_results;
        lazy_results.push_back( stubs::point::get_densityi_async( point_components[right_pe_] ) );
        hpx::lcos::wait(lazy_results,
              boost::bind(&point::chargei_callback, this, _1, _2));
      }

      if ( myrank_toroidal_ == par->ntoroidal-1 ) {
        // B.C. at zeta=2*pi is shifted
        size_t strides[]= {1,1};
        std::size_t lengths[2];
        for (std::size_t i=0;i<=par->mpsi;i++) {
          std::size_t ii = igrid_[i];
          std::size_t jt = mtheta_[i];
          std::size_t start = ii+1;
          lengths[0]= jt+1;
          lengths[1]= 1; 
          std::gslice mygslice (start,std::valarray<size_t>(lengths,2),std::valarray<size_t>(strides,2)); 
          std::valarray<double> trecv = recvr_[mygslice];
          trecv.cshift(itran_[i]);
          for (std::size_t j=ii+1;j<=ii+jt;j++) {
            densityi_(mzeta_,j,0) += trecv[j-(ii+1)];
          }
        }
      } else {
        // B.C. at zeta<2*pi is continuous
        for (std::size_t j=0;j<densityi_.jsize();j++) {
          densityi_(mzeta_,j,0) += recvr_[j];
        }
      }

      // zero out charge in radial boundary cell
      for (std::size_t i=0;i<par->nbound;i++) {
        for (std::size_t j=0;j<densityi_.isize();j++) {
          for (std::size_t k=igrid_[i];k<igrid_[i]+mtheta_[i];k++) {
            densityi_(j,k,0) *= ((double) i)/par->nbound;
          } 
          for (std::size_t k=igrid_[par->mpsi-i];k<igrid_[par->mpsi-i]+mtheta_[par->mpsi-i];k++) {
            densityi_(j,k,0) *= ((double) i)/par->nbound;
          }
        }
      }

      // flux surface average and normalization
      std::fill( zonali_.begin(),zonali_.end(),0.0);

      for (std::size_t i=0;i<=par->mpsi;i++) {
        for (std::size_t j=1;j<=mtheta_[i];j++) {
          for (std::size_t k=1;k<=mzeta_;k++) {
            std::size_t ij = igrid_[i] + j; 
            zonali_[i] += 0.25*densityi_(k,ij,0);
            densityi_(k,ij,0) *= 0.25*markeri_(k,ij,0);
          }
        }
      }

      // global sum of phi00 broadcast to every toroidal PE
      {
        adum_.resize(zonali_.size());
        std::fill( adum_.begin(),adum_.end(),0.0);
        typedef std::vector<hpx::lcos::promise< std::vector<double> > > lazy_results_type;
        lazy_results_type lazy_results;
        BOOST_FOREACH(hpx::naming::id_type const& gid, point_components)
        {
          lazy_results.push_back( stubs::point::get_zonali_async( gid ) );
        }
        hpx::lcos::wait(lazy_results,
              boost::bind(&point::chargei_zonali_callback, this, _1, _2));
      }
      for (std::size_t i=0;i<zonali_.size();i++) {
        zonali_[i] = adum_[i]*pmarki_[i];
      }

      for (std::size_t i=0;i<=par->mpsi;i++) {
        for (std::size_t j=1;j<=mtheta_[i];j++) {
          for (std::size_t k=1;k<=mzeta_;k++) {
            std::size_t ij = igrid_[i] + j;
            densityi_(k,ij,0) -= zonali_[i];
          }
        }
        // poloidal BC condition
        for (std::size_t j=1;j<=mzeta_;j++) {
          densityi_(j,igrid_[i],0) = densityi_(j,igrid_[i]+mtheta_[i],0);
        } 
      } 

      // enforce charge conservation for zonal flow mode
      double rdum = 0.0;      
      double tdum = 0.0;
      for (std::size_t i=1;i<=par->mpsi-1;i++) {
        double r = par->a0 + deltar_*i;
        rdum += r;
        tdum += r*zonali_[i];
      }
      tdum /= rdum;
      for (std::size_t i=1;i<=par->mpsi-1;i++) {
        zonali_[i] -= tdum;
      }

    }

    bool point::chargei_zonali_callback(std::size_t i,std::vector<double> const& zonali)
    {
      for (std::size_t i=0;i<zonali.size();i++) {
        adum_[i] += zonali[i];
      }
      return true;
    }

    bool point::chargei_callback(std::size_t i,std::valarray<double> const& density)
    {
      recvr_.resize(density.size());
      recvr_ = density;
      return true;
    }

    std::valarray<double> point::get_densityi()
    {
      return densityi_.slicer(6,0);
    }

    std::vector<double> point::get_zonali()
    {
      return zonali_;
    }

    void point::smooth(std::size_t iflag, std::vector<hpx::naming::id_type> const& point_components, std::size_t idiag, parameter const& par)
    {
      for (std::size_t j=0;j<phitmp_.jsize();j++) {
        for (std::size_t i=0;i<phitmp_.isize();i++) {
          phitmp_(i,j,0) = 0.0;
        }
      }  

      if ( iflag == 0 ) {
        for (std::size_t i=1;i<=mgrid_;i++) {
          for (std::size_t j=1;j<=mzeta_;j++) {
            phitmp_(j,i,0) = densityi_(j,i,0);
          }
        }
      } else if ( iflag == 1 ) {
        for (std::size_t i=1;i<=mgrid_;i++) {
          for (std::size_t j=1;j<=mzeta_;j++) {
            phitmp_(j,i,0) = densityi_(j,i,0);
          }
        }
      } else {
        for (std::size_t i=1;i<=mgrid_;i++) {
          for (std::size_t j=1;j<=mzeta_;j++) {
            phitmp_(j,i,0) = phi_(j,i,0);
          }
        }
      }

      std::size_t ismooth;
      ismooth = 1;
      if ( par->nonlinear < 0.5 ) ismooth = 0;
      
      std::vector<double> phism;
      std::valarray<double> pright,pleft;
      phism.resize(mgrid_+1);
      pright.resize(par->mthetamax+1);
      pleft.resize(par->mthetamax+1);

      for (std::size_t ip=1;ip<=ismooth;ip++) {
        // radial smoothing
        for (std::size_t i=1;i<=par->mpsi-1;i++) {
          for (std::size_t j=0;j<phitmp_.isize();j++) {
            phitmp_(j,igrid_[i],0) = phitmp_(j,igrid_[i]+mtheta_[i],0);
          } 
        }

        for (std::size_t k=1;k<=mzeta_;k++) {
          std::fill( phism.begin(),phism.end(),0.0);
          for (std::size_t i=1;i<=par->mpsi-1;i++) {
            for (std::size_t j=1;j<=mtheta_[i];j++) {
              std::size_t ij = igrid_[i] + j;

              phism[ij] = 0.25*((1.0-wtp1_(1,ij,k))*phitmp_(k,jtp1_(1,ij,k),0)+
                   wtp1_(1,ij,k)*phitmp_(k,jtp1_(1,ij,k)+1,0)+
                   (1.0-wtp1_(2,ij,k))*phitmp_(k,jtp1_(2,ij,k),0)+
                   wtp1_(2,ij,k)*phitmp_(k,jtp1_(2,ij,k)+1,0))-
                   0.0625*((1.0-wtp2_(1,ij,k))*phitmp_(k,jtp2_(1,ij,k),0)+
                   wtp2_(1,ij,k)*phitmp_(k,jtp2_(1,ij,k)+1,0)+
                   (1.0-wtp2_(2,ij,k))*phitmp_(k,jtp2_(2,ij,k),0)+
                   wtp2_(2,ij,k)*phitmp_(k,jtp2_(2,ij,k)+1,0));
            }
          }

          for (std::size_t i=0;i<phism.size();i++) {
            phitmp_(k,i,0) = 0.625*phitmp_(k,i,0) + phism[i];
          }
        }

        // poloidal smoothing (-0.0625 0.25 0.625 0.25 -0.0625)
        for (std::size_t i=1;i<=par->mpsi-1;i++) {
          std::size_t ii = igrid_[i];
          std::size_t jt = mtheta_[i];
          for (std::size_t k=1;k<=mzeta_;k++) {
            for (std::size_t kk=1;kk<=jt;kk++) {
              pright[kk] = phitmp_(k,ii+kk,0);
            }
            std::valarray<double> m_pright = pright.cshift(-1);
            std::valarray<double> p_pright = pright.cshift(1);
            std::valarray<double> m2_pright = pright.cshift(-2);
            std::valarray<double> p2_pright = pright.cshift(2);
            for (std::size_t kk=1;kk<=jt;kk++) {
              phitmp_(k,ii+kk,0) = 0.625*pright[kk] +
                 0.25*(m_pright[kk]+p_pright[kk])-
                 0.0625*(m2_pright[kk]+p2_pright[kk]);
            }
          }
        }
 
        // parallel smoothing
        // get phi from the left
        {
          typedef std::vector<hpx::lcos::promise< std::valarray<double> > > lazy_results_type;
          lazy_results_type lazy_results;
          lazy_results.push_back( stubs::point::get_phi_async( point_components[left_pe_],mzeta_ ) );
          hpx::lcos::wait(lazy_results,
                boost::bind(&point::phil_callback, this, _1, _2));
        }

        // get phi from the right
        {
          typedef std::vector<hpx::lcos::promise< std::valarray<double> > > lazy_results_type;
          lazy_results_type lazy_results;
          std::size_t one = 1; 
          lazy_results.push_back( stubs::point::get_phi_async( point_components[right_pe_],one ) );
          hpx::lcos::wait(lazy_results,
                boost::bind(&point::phir_callback, this, _1, _2));
        }

        for (std::size_t i=1;i<=par->mpsi-1;i++) {
          std::size_t ii = igrid_[i]; 
          std::size_t jt = mtheta_[i]; 
          if (myrank_toroidal_ == 0 ) { // down-shift for zeta=0
            std::valarray<double> trecvl;
            trecvl.resize(jt);
            for (std::size_t jj=ii+1;jj<=ii+jt;jj++) {
              trecvl[jj-(ii+1)] = recvl_[jj];
            }
            trecvl.cshift(-itran_[i]);
            for (std::size_t jj=1;jj<=jt;jj++) {
              pleft[jj] = trecvl[jj-1];  
              pright[jj] = recvr_[ii+jj];
            }
          } else if (myrank_toroidal_ == par->ntoroidal-1 ) { // up-shift for zeta=2*pi
            std::valarray<double> trecvr;
            trecvr.resize(jt);
            for (std::size_t jj=ii+1;jj<=ii+jt;jj++) {
              trecvr[jj-(ii+1)] = recvr_[jj];
            }
            trecvr.cshift(itran_[i]);
            for (std::size_t jj=1;jj<=jt;jj++) {
              pright[jj] = trecvr[jj-1]; // pesky fortran/C++ index difference
              pleft[jj] = recvl_[ii+jj];  
            }
          } else {
            for (std::size_t jj=1;jj<=jt;jj++) {
              pleft[jj] = recvl_[ii+jj];
              pright[jj] = recvr_[ii+jj];
            }
          }

          for (std::size_t j=1;j<=mtheta_[i];j++) {
            std::size_t ij = igrid_[i] + j;
            std::valarray<double> ptemp = phitmp_.slicer(7,ij); 
            if ( mzeta_ == 1 ) {
              phitmp_(1,ij,0) = 0.5*ptemp[1] + 0.25*(pleft[j] + pright[j]);
            } else if ( mzeta_ == 2 ) {
              phitmp_(1,ij,0) = 0.5*ptemp[1] + 0.25*(pleft[j] + pright[j]);
              phitmp_(2,ij,0) = 0.5*ptemp[2] + 0.25*(ptemp[1] + pright[j]);
            } else {
              phitmp_(1,ij,0) = 0.5*ptemp[1] + 0.25*(pleft[j] + pright[j]);
              phitmp_(mzeta_,ij,0) = 0.5*ptemp[mzeta_] + 0.25*(ptemp[mzeta_-1]+pright[j]);
              for (std::size_t k=2;k<=mzeta_-1;k++) {
                phitmp_(k,ij,0) = 0.5*ptemp[k] + 0.25*(ptemp[k-1]+ptemp[k+1]);
              }
            }
          }
        }
      }

      // toroidal BC: send phi to right and receive from left
      {
        typedef std::vector<hpx::lcos::promise< std::valarray<double> > > lazy_results_type;
        lazy_results_type lazy_results;
        lazy_results.push_back( stubs::point::get_phi_async( point_components[left_pe_],mzeta_ ) );
        hpx::lcos::wait(lazy_results,
              boost::bind(&point::phil_callback, this, _1, _2));
      }

      if ( myrank_toroidal_ == 0 ) {
        for (std::size_t i=1;i<=par->mpsi-1;i++) {
          std::size_t ii = igrid_[i];
          std::size_t jt = mtheta_[i];
          std::valarray<double> trecvl;
          trecvl.resize(jt);
          for (std::size_t jj=ii+1;jj<=ii+jt;jj++) {
            trecvl[jj-(ii+1)] = recvl_[jj];
          }
          trecvl.cshift(-itran_[i]);
          for (std::size_t jj=ii+1;jj<=ii+jt;jj++) {
            phitmp_(0,jj,0) = trecvl[jj-(ii+1)];
          }
        }
      } else {
        for (std::size_t j=0;j<recvl_.size();j++) {
          phitmp_(0,j,0) = recvl_[j];
        }
      }

      // poloidal BC
      for (std::size_t i=1;i<=par->mpsi-1;i++) {
        for (std::size_t j=0;j<phitmp_.isize();j++) {
          phitmp_(j,igrid_[i],0) = phitmp_(j,igrid_[i] + mtheta_[i],0);
        } 
      }

      // radial boundary
      for (std::size_t i=igrid_[0];i<=igrid_[0]+mtheta_[0];i++) {
        for (std::size_t j=0;j<phitmp_.isize();j++) {
          phitmp_(j,i,0) = 0.0;
        }
      } 
      for (std::size_t i=igrid_[par->mpsi];i<=igrid_[par->mpsi]+mtheta_[par->mpsi];i++) {
        for (std::size_t j=0;j<phitmp_.isize();j++) {
          phitmp_(j,i,0) = 0.0;
        }
      } 

      if ( iflag == 0 ) {
        for (std::size_t i=1;i<=mgrid_;i++) {
          for (std::size_t j=0;j<phitmp_.isize();j++) {
            densityi_(j,i,0)  = phitmp_(j,i,0);
          } 
        }
      } else if ( iflag == 1 ) {
        for (std::size_t i=1;i<=mgrid_;i++) {
          for (std::size_t j=0;j<phitmp_.isize();j++) {
            densitye_(j,i,0)  = phitmp_(j,i,0);
          } 
        }
      } else {
        for (std::size_t i=1;i<=mgrid_;i++) {
          for (std::size_t j=0;j<phitmp_.isize();j++) {
            phi_(j,i,0)  = phitmp_(j,i,0);
          } 
        }
      }

      // solve zonal flow: phi00=r*E_r, E_r(a0)=0. Trapezoid rule
      std::vector<double> den00;
      den00.resize(par->mpsi+1);
      if ( iflag == 3 ) {
        if ( par->nhybrid == 0 ) {
          for(std::size_t i=0;i<phip00_.size();i++) {
            phip00_[i] = par->qion*zonali_[i];
          }
        } 
        if ( par->nhybrid > 0 ) {
          for(std::size_t i=0;i<phip00_.size();i++) {
            phip00_[i] = par->qion*zonali_[i] + par->qelectron*zonale_[i] ;
          }
        }

        for(std::size_t ismooth=1;ismooth<=1;ismooth++) {
          den00[0] = phip00_[0]; 
          den00[par->mpsi] = phip00_[par->mpsi];
          den00[1] = phip00_[3];
          den00[par->mpsi-1] = phip00_[par->mpsi-3];
          for(std::size_t j=2;j<=par->mpsi-2;j++) {
            den00[j] = phip00_[j-2] + phip00_[j+2];
          }
          for(std::size_t j=1;j<=par->mpsi-1;j++) {
            den00[j] = 0.625*phip00_[j] + 0.25*(phip00_[j-1] + phip00_[j+1])
                          -0.0625*den00[j];
          }
          phip00_ = den00;
        }

        den00 = phip00_;
        std::fill( phip00_.begin(),phip00_.end(),0.0);
        for (std::size_t i=1;i<=par->mpsi;i++) {
          double r = par->a0 + deltar_*i;
          phip00_[i] = phip00_[i-1] + 0.5*deltar_*( (r-deltar_)*den00[i-1]+r*den00[i] );
        }

        // d phi/dr, in equilibrium unit
        for (std::size_t i=0;i<=par->mpsi;i++) {
          double r = par->a0 + deltar_*i;
          phip00_[i] = -phip00_[i]/r;
        }

        // add FLR contribution using Pade approximation: b*<phi>=(1+b)*<n>
        phi00_ = den00;
        for (std::size_t i=0;i<phi00_.size();i++) {
          phi00_[i] *= par->gyroradius*par->gyroradius;
        }
        for (std::size_t i=1;i<=par->mpsi-1;i++) {
          phi00_[i] = phi00_[i] + 0.5*(phip00_[i+1]+phip00_[i-1])/deltar_;
        }

        // (0,0) mode potential store in phi00
        std::fill( phip00_.begin(),phip00_.end(),0.0);
        for (std::size_t i=1;i<=par->mpsi;i++) {
          phi00_[i] = phi00_[i-1] + 0.5*deltar_*(phip00_[i-1]+phip00_[i]);
        }
        if ( par->mode00 == 0 ) {
          std::fill( phip00_.begin(),phip00_.end(),0.0);
        }
      }

      // Interpolate on a flux surface from fieldline coordinates to magnetic
      // coordinates. Use mtdiag for both poloidal and toroidal grid points.
      std::size_t zero = 0;
      std::vector<double> xz,filter;
      std::vector<dcmplx> yz;
      xz.resize(mtdiag_);
      yz.resize(mtdiag_/2+1 + 1);
      eachzeta_.resize((par->idiag2-par->idiag1+1)*mtdiag_*mtdiag_/par->ntoroidal/par->ntoroidal + 1 );
      array<double> phiflux;
      phiflux.resize(mtdiag_/par->ntoroidal+1,mtdiag_+1,par->idiag2-par->idiag1);
      filter.resize(mtdiag_/2+1 + 1);
      allzeta_.resize((par->idiag2-par->idiag1+1)*mtdiag_*mtdiag_/par->ntoroidal + 1 );
      y_eigen_.resize(mtdiag_/par->ntoroidal*par->num_mode + 1);
      if ( iflag > 1 ) {
        if ( par->nonlinear < 0.5 || (iflag == 3 && idiag == 0 ) ) {
          std::fill( xz.begin(),xz.end(),0.0);
          std::fill( yz.begin(),yz.end(),0.0);
          // ESSL would normally go here
          std::size_t one = 1; 
          std::size_t mzbig = (std::max)(one,mtdiag_/par->mzetamax);
          std::size_t mzmax = par->mzetamax*mzbig;
          std::size_t mz = mzeta_*mzbig;
          std::size_t meachtheta = mtdiag_/par->ntoroidal;
          std::size_t icount = meachtheta*mz*(par->idiag2-par->idiag1+1);
          double dt = 2.0*pi_/mtdiag_; 
          double pi2_inv = 0.5/pi_;
          std::fill( filter.begin(),filter.end(),0.0);
          for (std::size_t i=0;i<par->nmode.size();i++) {
            filter[par->nmode[i]+1] = 1.0/mzmax;
          }
          std::fill( allzeta_.begin(),allzeta_.end(),0.0);

          for (std::size_t k=1;k<=mzeta_;k++) {
            for (std::size_t kz=1;kz<=mzbig;kz++) {
              double wz = ((double) kz)/((double)mzbig);
              double zdum = zetamin_ + deltaz_*((k-1)+wz);
              for (std::size_t i=par->idiag1;i<=par->idiag2;i++) {
                std::size_t ii = igrid_[i];
                for (std::size_t j=1;j<=mtdiag_;j++) {
                  double tdum = pi2_inv*(dt*j-zdum*qtinv_[i]) + 10.0;
                  tdum = (tdum - floor(tdum))*mtheta_[i];
                  std::size_t jt = (std::max)(zero,(std::min)(mtheta_[i]-1,(std::size_t) tdum));
                  double wt = tdum - jt; 
                  phiflux(kz+(k-1)*mzbig,j,i-par->idiag1) = 
                    ((1.0-wt)*phi_(k,ii+jt,0) + wt*phi_(k,ii+jt+1,0))*wz
                  + (1.0-wz)*((1.0-wt)*phi_(k-1,ii+jt,0)+wt*phi_(k-1,ii+jt+1,0)); 
                }
              }
            } 
          }

          // transpose 2-d matrix from (ntoroidal,mzeta*mzbig) to (1,mzetamax*mzbig)
          for (std::size_t jpe=0;jpe<=par->ntoroidal-1;jpe++) {
            for (std::size_t j=1;j<=meachtheta;j++) {
              std::size_t jt = jpe*meachtheta+j;
              std::size_t indt = (j-1)*mz;
              for (std::size_t i=par->idiag1;i<=par->idiag2;i++) {
                std::size_t indp1 = indt + (i-par->idiag1)*meachtheta*mz;
                for (std::size_t k=1;k<=mz;k++) {
                  std::size_t indp = indp1 + k;
                  eachzeta_[indp] = phiflux(k,jt,i-par->idiag1);
                }
              }
            }

            // Gather
            {
              typedef std::vector<hpx::lcos::promise< std::vector<double> > > lazy_results_type;
              lazy_results_type lazy_results;
              BOOST_FOREACH(hpx::naming::id_type const& gid, point_components)
              {
                lazy_results.push_back( stubs::point::get_eachzeta_async( gid ) );
              }
              std::size_t length = (par->idiag2-par->idiag1+1)*mtdiag_*mtdiag_/par->ntoroidal/par->ntoroidal;
              hpx::lcos::wait(lazy_results,
                    boost::bind(&point::eachzeta_callback, this, _1, _2,boost::ref(length)));
            }

          }

          // transform to k space
          for (std::size_t j=1;j<=meachtheta;j++) {
            std::size_t indt1 = (j-1)*mz;
            for (std::size_t i=par->idiag1;i<=par->idiag2;i++) {
              std::size_t indt=indt1+(i-par->idiag1)*meachtheta*mz;

              for (std::size_t kz=0;kz<=par->ntoroidal-1;kz++) {
                for (std::size_t k=1;k<=mz;k++) {
                  std::size_t indp = kz*icount+indt+k;
                  xz[kz*mz+k] = allzeta_[indp];
                }
              }
              // ifdef ESSL
              // TEST
              // call fftr1d(1,mtdiag,scale,xz,yz,2)

              // record mode information for diagnostic
              if ( i == par->mpsi/2 ) {
                for (std::size_t kz=1;kz<=par->num_mode;kz++) {
                  y_eigen_[j+meachtheta*(kz-1)] = yz[par->nmode[kz]+1];
                }
              }

              if ( par->nonlinear < 0.5 ) {
                // linear run only keep a few modes
                for (std::size_t kk=0;kk<yz.size();kk++) {
                  yz[kk] *= filter[kk];
                }
                // transform back to real space
                // ESSL
                // TEST
                // call fftr1d(-1,mtdiag,scale,xz,yz,2)
 
                // transpose back to (ntoroidal,mz)
                for (std::size_t kz=0;kz<=par->ntoroidal-1;kz++) {
                  for (std::size_t k=1;k<=mz;k++) { 
                    std::size_t indp = kz*icount+indt+k;
                    allzeta_[indp] = xz[kz*mz+k];
                  }
                }
              }
            }
          }

          if ( par->nonlinear < 0.5 ) {
            std::cerr << " This condition is not fully implemented yet. Sorry " << std::endl;
            BOOST_ASSERT(false);
          }

        }
      }

      if ( iflag == 2 ) {
        std::cerr << " This only occurs if nhybrid > 0, which is not fully implemented yet.  Sorry " << std::endl;
      }

      if ( iflag == 3 && idiag == 0 ) { 
        // Diagnostic not implemented yet
      }

    }

    std::valarray<double> point::get_phi(std::size_t depth)
    {
      return phitmp_.slicer(6,depth);
    }

    bool point::phir_callback(std::size_t i,std::valarray<double> const& phi)
    {
      recvr_.resize(phi.size());
      recvr_ = phi;
      return true;
    }

    bool point::phil_callback(std::size_t i,std::valarray<double> const& phi)
    {
      recvl_.resize(phi.size());
      recvl_ = phi;
      return true;
    }

    bool point::eachzeta_callback(std::size_t i,std::vector<double> const& eachzeta,std::size_t length)
    {
      //std::size_t length = (par->idiag2-par->idiag1+1)*mtdiag_*mtdiag_/par->ntoroidal/par->ntoroidal;
      for (std::size_t j=1;j<=length;j++) {
        allzeta_[i*length + j] = eachzeta[j];
      }
      return true;
    }

    std::vector<double> point::get_eachzeta()
    {
      return eachzeta_;
    }

    void point::field(std::vector<hpx::naming::id_type> const& point_components,                      parameter const& par)
    {
      std::valarray<double> pright,pleft;
      pright.resize(par->mthetamax+1);
      pleft.resize(par->mthetamax+1);

      // finite difference for e-field in equilibrium unit
      double diffr = 0.5/deltar_;
      std::vector<double> difft;
      difft.resize(deltat_.size());
      for (std::size_t i=0;i<deltat_.size();i++) {
        difft[i] = 0.5/deltat_[i];
      }
      double diffz = 0.5/deltaz_;
      for (std::size_t i=1;i<=mgrid_;i++) {
        for (std::size_t j=0;j<=mzeta_;j++) {
          for (std::size_t k=1;k<=3;k++) {
            evector_(k,j,i) = 0.0;
          }
        }
      }

      for (std::size_t k=1;k<=mzeta_;k++) {
        for (std::size_t i=1;i<=par->mpsi-1;i++) {
          double r = par->a0 + deltar_*i;
          double drdp = 1.0/r;
          for (std::size_t j=1;j<=mtheta_[i];j++) {
            std::size_t ij = igrid_[i] + j; 
 
            evector_(1,k,ij) = drdp*diffr*((1.0-wtp1_(1,ij,k))*phi_(k,jtp1_(1,ij,k),0)+
                   wtp1_(1,ij,k)*phi_(k,jtp1_(1,ij,k)+1,0)-
                   ((1.0-wtp1_(2,ij,k))*phi_(k,jtp1_(2,ij,k),0)+ 
                   wtp1_(2,ij,k)*phi_(k,jtp1_(2,ij,k)+1,0)));
          } 
        }
      }

      for (std::size_t i=1;i<=par->mpsi-1;i++) {
        for (std::size_t k=1;k<=mzeta_;k++) {
          for (std::size_t j=1;j<=mtheta_[i];j++) {
            std::size_t ij = igrid_[i] + j; 
            std::size_t jt = j+1-mtheta_[i]*(j/mtheta_[i]);
            evector_(2,k,ij) = difft[i]*(phi_(k,igrid_[i]+jt,0)-phi_(k,igrid_[i]+j-1,0));
          }
        }
      }

      // get phi from the left
      {
        typedef std::vector<hpx::lcos::promise< std::valarray<double> > > lazy_results_type;
        lazy_results_type lazy_results;
        lazy_results.push_back( stubs::point::get_phi_async( point_components[left_pe_],mzeta_ ) );
        hpx::lcos::wait(lazy_results,
              boost::bind(&point::phil_callback, this, _1, _2));
      }

      // get phi from the right
      {
        typedef std::vector<hpx::lcos::promise< std::valarray<double> > > lazy_results_type;
        lazy_results_type lazy_results;
        std::size_t one = 1; 
        lazy_results.push_back( stubs::point::get_phi_async( point_components[right_pe_],one ) );
        hpx::lcos::wait(lazy_results,
              boost::bind(&point::phir_callback, this, _1, _2));
      }

      // unpack phi_boundary and calculate E_zeta at boundaries, mzeta=1
      for (std::size_t i=1;i<=par->mpsi-1;i++) {
        std::size_t ii = igrid_[i]; 
        std::size_t jt = mtheta_[i]; 
        if (myrank_toroidal_ == 0 ) { // down-shift for zeta=0
          std::valarray<double> trecvl;
          trecvl.resize(jt);
          for (std::size_t jj=ii+1;jj<=ii+jt;jj++) {
            trecvl[jj-(ii+1)] = recvl_[jj];
          }
          trecvl.cshift(-itran_[i]);
          for (std::size_t jj=1;jj<=jt;jj++) {
            pleft[jj] = trecvl[jj-1];  
            pright[jj] = recvr_[ii+jj];
          }
        } else if (myrank_toroidal_ == par->ntoroidal-1 ) { // up-shift for zeta=2*pi
          std::valarray<double> trecvr;
          trecvr.resize(jt);
          for (std::size_t jj=ii+1;jj<=ii+jt;jj++) {
            trecvr[jj-(ii+1)] = recvr_[jj];
          }
          trecvr.cshift(itran_[i]);
          for (std::size_t jj=1;jj<=jt;jj++) {
            pright[jj] = trecvr[jj-1]; // pesky fortran/C++ index difference
            pleft[jj] = recvl_[ii+jj];  
          }
        } else {
          for (std::size_t jj=1;jj<=jt;jj++) {
            pleft[jj] = recvl_[ii+jj];
            pright[jj] = recvr_[ii+jj];
          }
        }

        // d_phi/d_zeta
        for (std::size_t j=1;j<=mtheta_[i];j++) {
          std::size_t ij = igrid_[i] + j;
          if ( mzeta_ == 1 ) {
            evector_(3,1,ij) = (pright[j]-pleft[j])*diffz;
          } else if ( mzeta_ == 2 ) {
            evector_(3,1,ij) = (phi_(2,ij,0)-pleft[j])*diffz;
            evector_(3,2,ij) = (pright[j] - phi_(1,ij,0))*diffz;
          } else {
            evector_(3,1,ij) = (phi_(2,ij,0)-pleft[j])*diffz;
            evector_(3,mzeta_,ij) = (pright[j]-phi_(mzeta_-1,ij,0))*diffz;
            for (std::size_t jj=2;jj<=mzeta_-1;jj++) {
              evector_(3,jj,ij) = (phi_(jj+1,ij,0)-phi_(jj-1,ij,0))*diffz;
            }
          }
        }
      }

      // adjust the difference between safety factor q and qtinv for fieldline coordinate
      for (std::size_t i=1;i<=par->mpsi-1;i++) {
        double r = par->a0 + deltar_*i;
        double q = par->q0 + par->q1*r/par->a + par->q2*r*r/(par->a*par->a);
        double delq = (1.0/q - qtinv_[i]);

        for (std::size_t j=1;j<=mtheta_[i];j++) {
          std::size_t ij = igrid_[i] + j;
          for (std::size_t jj=0;jj<evector_.jsize();jj++) {
            evector_(3,jj,ij) += delq*evector_(2,jj,ij); 
          }
        }
      }

      // add (0,0) mode, d phi/d psi
      if ( par->mode00 == 1 ) {
        for (std::size_t i=1;i<=par->mpsi-1;i++) {
          double r = par->a0 + deltar_*i;
          std::size_t ii = igrid_[i]; 
          std::size_t jt = mtheta_[i];
          for (std::size_t j=ii+1;j<=ii+jt;j++) {
            for (std::size_t k=1;k<=mzeta_;k++) {
              evector_(1,k,j) += phip00_[i]/r;
            }
          }
        }
      }

      // get evector from the left
      {
        typedef std::vector<hpx::lcos::promise< std::valarray<double> > > lazy_results_type;
        lazy_results_type lazy_results;
        lazy_results.push_back( stubs::point::get_evector_async( point_components[left_pe_],1,mzeta_ ) );
        lazy_results.push_back( stubs::point::get_evector_async( point_components[left_pe_],2,mzeta_ ) );
        lazy_results.push_back( stubs::point::get_evector_async( point_components[left_pe_],3,mzeta_ ) );
        hpx::lcos::wait(lazy_results,
              boost::bind(&point::evector_callback, this, _1, _2));
      }

      // unpack end point data for k=0
      if (myrank_toroidal_ == 0 ) { // down-shift for zeta=0
        std::valarray<double> trecvlA,trecvlB,trecvlC;
        for (std::size_t i=1;i<=par->mpsi-1;i++) {
          std::size_t ii = igrid_[i]; 
          std::size_t jt = mtheta_[i]; 
          trecvlA.resize(jt);
          trecvlB.resize(jt);
          trecvlC.resize(jt);
          for (std::size_t jj=ii+1;jj<=ii+jt;jj++) {
            trecvlA[jj-(ii+1)] = recvls_(1,jj,0);
            trecvlB[jj-(ii+1)] = recvls_(2,jj,0);
            trecvlC[jj-(ii+1)] = recvls_(3,jj,0);
          }
          trecvlA.cshift(-itran_[i]);
          trecvlB.cshift(-itran_[i]);
          trecvlC.cshift(-itran_[i]);
          for (std::size_t jj=ii+1;jj<=ii+jt;jj++) {
            evector_(1,0,jj) = trecvlA[jj-(ii+1)]; 
            evector_(2,0,jj) = trecvlB[jj-(ii+1)]; 
            evector_(3,0,jj) = trecvlC[jj-(ii+1)]; 
          }
        }
      } else {
        for (std::size_t i=1;i<=mgrid_;i++) { 
          evector_(1,0,i) = recvls_(1,i,0);
          evector_(2,0,i) = recvls_(2,i,0);
          evector_(3,0,i) = recvls_(3,i,0);
        }
      }

      // poloidal end point
      for (std::size_t i=1;i<=par->mpsi-1;i++) {
        for (std::size_t j=0;j<=mzeta_;j++) {
          evector_(1,j,igrid_[i]) = evector_(1,j,igrid_[i]+mtheta_[i]);
          evector_(2,j,igrid_[i]) = evector_(2,j,igrid_[i]+mtheta_[i]);
          evector_(3,j,igrid_[i]) = evector_(3,j,igrid_[i]+mtheta_[i]);
        }
      } 
 
    }

    bool point::evector_callback(std::size_t i,std::valarray<double> const& evector)
    {
      for (std::size_t j=1;j<=mgrid_;j++) {
        recvls_(i,j,0) = evector[j];
      }
      return true;
    }

    std::valarray<double> point::get_evector(std::size_t depth,std::size_t extent)
    {
      return evector_.full_slicer(0,depth,extent);
    }
    

}}


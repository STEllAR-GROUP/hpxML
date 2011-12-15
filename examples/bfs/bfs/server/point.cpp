//  Copyright (c) 2011 Matthew Anderson
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/include/iostreams.hpp>

#include "../stubs/point.hpp"
#include "point.hpp"

#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>
#include <fstream>

///////////////////////////////////////////////////////////////////////////////
namespace bfs { namespace server
{
    void point::init(std::size_t objectid,std::size_t grainsize,
        std::size_t max_num_neighbors,std::vector<std::size_t> const& nodelist,
        std::vector<std::size_t> const& neighborlist,
        boost::numeric::ublas::mapped_vector<std::size_t> const& index)
    {
        hpx::lcos::local_mutex::scoped_lock l(mtx_);
        idx_ = objectid;
        grainsize_ = grainsize; 
        neighbors_.resize(grainsize_);
        visited_.resize(grainsize_);
        parent_.resize(grainsize_);
        level_.resize(grainsize_);
        for (std::size_t i=0;i<grainsize_;i++) {
          neighbors_[i].reserve(max_num_neighbors);
          visited_[i] = false;
        }
 
        boost::numeric::ublas::mapped_vector<bool> initialized;
        // initialize the mapping
        for (std::size_t i=0;i<nodelist.size();i++) {
          std::size_t node = nodelist[i];
          std::size_t neighbor = neighborlist[i];
          if ( index(node) == idx_ && node != neighbor ) {
            mapping_.insert_element(node,0);
            initialized.insert_element(node,false);
          }
          if ( index(neighbor) == idx_ && node != neighbor ) {
            mapping_.insert_element(neighbor,0);
            initialized.insert_element(neighbor,false);
          }
        }

        std::size_t count = 0;
        for (std::size_t i=0;i<nodelist.size();i++) {
          std::size_t node = nodelist[i];
          std::size_t neighbor = neighborlist[i];
          BOOST_ASSERT(count < grainsize_);
          if ( index(node) == idx_ && node != neighbor ) {
            if ( initialized(node) == false ) {
              mapping_(node) = count;
              initialized(node) = true;
              count++;
            } 
            neighbors_[ mapping_(node) ].push_back(neighbor);
          }

          BOOST_ASSERT(count < grainsize_);
          // symmetrize
          if ( index(neighbor) == idx_ && node != neighbor ) {
            if ( initialized(neighbor) == false ) {
              mapping_(neighbor) = count;
              initialized(neighbor) = true;
              count++;
            }
            neighbors_[ mapping_(neighbor) ].push_back(node);
    
          }
        } 
    }

    void point::reset_visited(std::size_t id) {
      hpx::lcos::local_mutex::scoped_lock l(mtx_);
      std::fill( visited_.begin(),visited_.end(),false);
    }

    std::vector<std::size_t> point::traverse(std::size_t level,std::size_t parent,std::size_t edge)
    {
        hpx::lcos::local_mutex::scoped_lock l(mtx_);
        if ( visited_[mapping_(edge)] == false ) {
            visited_[mapping_(edge)] = true;
            parent_[mapping_(edge)] = parent;
            level_[mapping_(edge)] = level; 

            // Return the neighbors.
            return neighbors_[mapping_(edge)];
        } else {
            // Don't return neighbors.
            std::vector<std::size_t> tmp;
            return tmp;
        }
    }

    std::size_t point::get_parent(std::size_t edge)
    {
      hpx::lcos::local_mutex::scoped_lock l(mtx_);
      if ( visited_[mapping_(edge)] == false ) {
        return 0;
      } else {
        return parent_[mapping_(edge)];
      }
    }

    std::size_t point::get_level(std::size_t edge)
    {
      hpx::lcos::local_mutex::scoped_lock l(mtx_);
      if ( visited_[mapping_(edge)] == false ) {
        return 0;
      } else {
        return level_[mapping_(edge)];
      }
    }
}}


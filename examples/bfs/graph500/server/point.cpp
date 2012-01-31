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

/* Spread the two 64-bit numbers into five nonzero values in the correct
 * range. */
void make_mrg_seed(uint64_t userseed1, uint64_t userseed2, uint_fast32_t* seed) {
  seed[0] = (userseed1 & 0x3FFFFFFF) + 1;
  seed[1] = ((userseed1 >> 30) & 0x3FFFFFFF) + 1;
  seed[2] = (userseed2 & 0x3FFFFFFF) + 1;
  seed[3] = ((userseed2 >> 30) & 0x3FFFFFFF) + 1;
  seed[4] = ((userseed2 >> 60) << 4) + (userseed1 >> 60) + 1;
}

static void compute_edge_range(int rank, int size, int64_t M, int64_t* start_idx, int64_t* end_idx) {
  int64_t rankc = (int64_t)(rank);
  int64_t sizec = (int64_t)(size);
  *start_idx = rankc * (M / sizec) + (rankc < (M % sizec) ? rankc : (M % sizec));
  *end_idx = (rankc + 1) * (M / sizec) + (rankc + 1 < (M % sizec) ? rankc + 1 : (M % sizec));
}

///////////////////////////////////////////////////////////////////////////////
namespace graph500 { namespace server
{
    void point::init(std::size_t objectid,std::size_t log_numverts,std::size_t number_partitions)
    {
      // Spread the two 64-bit numbers into five nonzero values in the correct
      //  range.
      uint_fast32_t seed[5];
      uint64_t userseed1 = 1;
      uint64_t userseed2 = 1;
      make_mrg_seed(userseed1, userseed2, seed);

      int64_t M = INT64_C(16) << log_numverts;

      int64_t start_idx, end_idx;
      compute_edge_range(objectid, number_partitions, M, &start_idx, &end_idx);
      int64_t nedges = end_idx - start_idx;

      local_edges_.resize(nedges);

    //  generate_kronecker_range(seed, log_numverts, start_idx, end_idx, &*local_edges_.begin());
      // As this doesn't work yet without C support, read the file as a stop-gap measure 
      {
        // stop-gap measure
        std::string const graphfile = "g10.txt";
        std::string line;
        std::string val1,val2;
        std::ifstream myfile;
        myfile.open(graphfile);
        std::size_t count = 0;
        if (myfile.is_open()) {
          while (myfile.good()) {
            while (std::getline(myfile,line)) {
              std::istringstream isstream(line);
              std::getline(isstream,val1,' ');
              std::getline(isstream,val2,' ');
              std::size_t node = boost::lexical_cast<std::size_t>(val1);
              std::size_t neighbor = boost::lexical_cast<std::size_t>(val2);
              if ( count >= start_idx && count < end_idx ) {
                // Record it
                // increment all nodes and neighbors by 1; the smallest edge number is 1
                // edge 0 is reserved for the parent of the root and for unvisited edges
                local_edges_[count-start_idx].v0 = node + 1; 
                local_edges_[count-start_idx].v1 = neighbor + 1;
              }
              count++;
            }
          }
        }
      }

      // find the biggest node or neighbor
      std::size_t maxnode = 0;
      minnode_ = 99999;
      for (std::size_t i=0;i<local_edges_.size();i++) {
        if ( local_edges_[i].v0 > maxnode ) maxnode = local_edges_[i].v0;
        if ( local_edges_[i].v1 > maxnode ) maxnode = local_edges_[i].v1;

        if ( local_edges_[i].v0 < minnode_ ) minnode_ = local_edges_[i].v0;
        if ( local_edges_[i].v1 < minnode_ ) minnode_ = local_edges_[i].v1;
      }
      maxnode++;
      std::size_t N = maxnode-minnode_;

      neighbors_.resize(maxnode-minnode_);

      for (std::size_t i=0;i<local_edges_.size();i++) {
        std::size_t node = local_edges_[i].v0;
        std::size_t neighbor = local_edges_[i].v1;
        if ( node != neighbor ) {
          neighbors_[node-minnode_].push_back(neighbor);
          neighbors_[neighbor-minnode_].push_back(node);
        }
      }

      level_.resize(N);
      parent_.resize(N);
      visited_.resize(N);
      std::fill( visited_.begin(),visited_.end(),false);
      std::fill( level_.begin(),level_.end(),0);
      std::fill( parent_.begin(),parent_.end(),0);
    }

    void point::bfs()
    {
    }

}}


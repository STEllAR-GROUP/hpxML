//  Copyright (c) 2007-2013 Hartmut Kaiser
//  Copyright (c) 2014-2015 Thomas Heller
//  Copyright (c) 2014-2015 John Biddiscombe
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// config
#include <hpx/config/defines.hpp>
#include <hpx/hpx_fwd.hpp>

// util
#include <hpx/util/command_line_handling.hpp>
#include <hpx/util/runtime_configuration.hpp>
#include <hpx/util/high_resolution_timer.hpp>
#include <hpx/util/safe_bool.hpp>
#include <hpx/util/memory_chunk_pool_allocator.hpp>

// The memory pool specialization need to be pulled in before encode_parcels
#define JB_MEM_POOL
#ifdef JB_MEM_POOL
 #include "RdmaMemoryPool.h"
#else
 #include <hpx/util/memory_chunk_pool.hpp>
#endif

// parcelport
#include <hpx/runtime.hpp>
#include <hpx/runtime/parcelset/parcelport.hpp>
#include <hpx/runtime/parcelset/parcel_buffer.hpp>
#include <hpx/runtime/parcelset/encode_parcels.hpp>
#include <hpx/runtime/parcelset/decode_parcels.hpp>
#include <hpx/plugins/parcelport_factory.hpp>

// Local parcelport plugin
#include <connection_handler_verbs.hpp>
//
#include <hpx/plugins/parcelport/header.hpp>

// rdmahelper library
#include "RdmaLogging.h"
#include "RdmaController.h"
#include "RdmaDevice.h"

using namespace hpx::parcelset::policies;


namespace hpx { namespace parcelset { namespace policies { namespace verbs
{
    struct locality {
      static const char *type() {
        FUNC_START_DEBUG_MSG;
        FUNC_END_DEBUG_MSG;
        return "verbs";
      }

      explicit locality(boost::uint32_t ip, boost::uint32_t port) :
            ip_(ip), port_(port), qp_(0xFFFF) {}

      locality() : ip_(0xFFFF), port_(0), qp_(0xFFFF) {}

      // some condition marking this locality as valid
      operator util::safe_bool<locality>::result_type() const {
        //    FUNC_START_DEBUG_MSG;
        //    FUNC_END_DEBUG_MSG;
        return util::safe_bool<locality>()(ip_ != boost::uint32_t(0xFFFF));
      }

      void save(util::portable_binary_oarchive & ar) const {
        // save the state
        FUNC_START_DEBUG_MSG;
        ar.save(ip_);
        FUNC_END_DEBUG_MSG;
      }

      void load(util::portable_binary_iarchive & ar) {
        // load the state
        FUNC_START_DEBUG_MSG;
        ar.load(ip_);
        FUNC_END_DEBUG_MSG;
      }

    private:
      friend bool operator==(locality const & lhs, locality const & rhs) {
        FUNC_START_DEBUG_MSG;
        FUNC_END_DEBUG_MSG;
        return lhs.ip_ == rhs.ip_;
      }

      friend bool operator<(locality const & lhs, locality const & rhs) {
        FUNC_START_DEBUG_MSG;
        FUNC_END_DEBUG_MSG;
        return lhs.ip_ < rhs.ip_;
      }

      friend std::ostream & operator<<(std::ostream & os, locality const & loc) {
        FUNC_START_DEBUG_MSG;
        boost::io::ios_flags_saver
        ifs(os);
        os << loc.ip_;
        FUNC_END_DEBUG_MSG
        return os;
      }
    public:
      boost::uint32_t ip_;
      boost::uint32_t port_;
      boost::uint32_t qp_;
    };

    class parcelport: public parcelset::parcelport {
    private:
      static parcelset::locality here(util::runtime_configuration const& ini) {
        FUNC_START_DEBUG_MSG;
        if (ini.has_section("hpx.parcel.verbs")) {
          util::section const * sec = ini.get_section("hpx.parcel.verbs");
          if (NULL != sec) {
            std::string ibverbs_enabled(sec->get_entry("enable", "0"));
            if (boost::lexical_cast<int>(ibverbs_enabled)) {
              _ibverbs_ifname    = sec->get_entry("ifname",    HPX_PARCELPORT_VERBS_IFNAME);
              _ibverbs_device    = sec->get_entry("device",    HPX_PARCELPORT_VERBS_DEVICE);
              _ibverbs_interface = sec->get_entry("interface", HPX_PARCELPORT_VERBS_INTERFACE);
              char buffty[256];
              _ibv_ip = hpx::parcelset::policies::verbs::Get_rdma_device_address(_ibverbs_device.c_str(), _ibverbs_interface.c_str(), buffty);
              LOG_DEBUG_MSG("here() got hostname of " << buffty);
            }
          }
        }
        if (ini.has_section("hpx.agas")) {
          util::section const* sec = ini.get_section("hpx.agas");
          if (NULL != sec) {
            LOG_DEBUG_MSG("hpx.agas port number " << hpx::util::get_entry_as<boost::uint16_t>(*sec, "port", HPX_INITIAL_IP_PORT));
            _port = hpx::util::get_entry_as<boost::uint16_t>(*sec, "port", HPX_INITIAL_IP_PORT);
          }
        }
        if (ini.has_section("hpx.parcel")) {
          util::section const* sec = ini.get_section("hpx.parcel");
          if (NULL != sec) {
            LOG_DEBUG_MSG("hpx.parcel port number " << hpx::util::get_entry_as<boost::uint16_t>(*sec, "port", HPX_INITIAL_IP_PORT));
          }
        }
        FUNC_END_DEBUG_MSG;
        return parcelset::locality(locality(_ibv_ip, _ibv_ip));
      }

    public:
      parcelport(util::runtime_configuration const& ini,
          util::function_nonser<void(std::size_t, char const*)> const& on_start_thread,
          util::function_nonser<void()> const& on_stop_thread) :
            parcelset::parcelport(ini, here(ini), "verbs"), archive_flags_(boost::archive::no_header)
      , stopped_(false)
//      , parcels_sent_(0)
    #ifndef JB_MEM_POOL
      , chunk_pool_(4096, 32)
    #endif
      {
        FUNC_START_DEBUG_MSG;
        //    _port   = 0;
    #ifdef BOOST_BIG_ENDIAN
        std::string endian_out = get_config_entry("hpx.parcel.endian_out", "big");
    #else
        std::string endian_out = get_config_entry("hpx.parcel.endian_out", "little");
    #endif
        if (endian_out == "little")
          archive_flags_ |= util::endian_little;
        else if (endian_out == "big")
          archive_flags_ |= util::endian_big;
        else {
          HPX_ASSERT(endian_out == "little" || endian_out == "big");
        }

        if (!this->allow_array_optimizations()) {
          archive_flags_ |= util::disable_array_optimization;
          archive_flags_ |= util::disable_data_chunking;
          LOG_DEBUG_MSG("Disabling array optimization and data chunking");
        } else {
          if (!this->allow_zero_copy_optimizations()) {
            archive_flags_ |= util::disable_data_chunking;
            LOG_DEBUG_MSG("Disabling data chunking");
          }
        }
        _rdmaController = std::make_shared<RdmaController>(_ibverbs_device.c_str(), _ibverbs_interface.c_str(), _port);

        FUNC_END_DEBUG_MSG;
      }

      static RdmaControllerPtr _rdmaController;
      static std::string       _ibverbs_ifname;
      static std::string       _ibverbs_device;
      static std::string       _ibverbs_interface;
      static boost::uint32_t   _port;
      static boost::uint32_t   _ibv_ip;
      //
      typedef std::map<boost::uint32_t, boost::uint32_t> ip_map;
      typedef ip_map::iterator                           ip_map_iterator;
      //
      ip_map ip_qp_map;

      // pointer to verbs completion member function type
      typedef int (parcelport::*parcel_member_function)(struct ibv_wc *completion, RdmaClientPtr);

      // actual handler for completions
      int handle_verbs_completion(struct ibv_wc *completion, RdmaClientPtr client)
      {
        LOG_DEBUG_MSG("Completion yay!!!");
        uint64_t wr_id = completion->wr_id;
        RdmaMemoryRegion *region = (RdmaMemoryRegion *)completion->wr_id;
        //
        send_wr_map::iterator it_s;
        get_wr_map::iterator  it_z;
        if ((it_s = SendCompletionMap.find(wr_id)) != SendCompletionMap.end()) {
          // a send has completed successfully
          error_code ec;
          // call the write_handler
          std::get<1>(it_s->second).operator()(ec, std::get<0>(it_s->second));
          // it is now safe to release the memory for this region
          SendCompletionMap.erase(it_s);
          chunk_pool_->deallocate(region);
          // if this message had multiple SGEs then release other regions
          if (std::get<2>(it_s->second)) {
            chunk_pool_->deallocate(reinterpret_cast<RdmaMemoryRegion*>(std::get<2>(it_s->second)));
          }
          chunk_pool_->deallocate(region);
        }
        if ((it_z = ZeroCopyGetCompletionMap.find(wr_id)) != ZeroCopyGetCompletionMap.end()) {
          LOG_ERROR_MSG("A zero copy get has completed, implement this");
        }
        else {
          // this was an unexpected receive, i.e a new parcel
          LOG_DEBUG_MSG("Entering receive section");
          // decrement counter that keeps preposted queue full
          client->popReceive();
          //
          util::high_resolution_timer timer;
          // get the header
          header_type *h = (header_type*)region->getAddress();

          LOG_DEBUG_MSG( "received " <<
                 "buffer size is " << decnumber(h->size())
              << "numbytes is " << decnumber(h->numbytes())
              << "num_chunks is zerocopy( " << decnumber(h->num_chunks().first) << ") "
              << ", normal( " << decnumber(h->num_chunks().second) << ") "
              << " piggyback " << decnumber((h->piggy_back()!=NULL))
              << " tag is " << decnumber(h->tag())
              );

          char *piggy_back = h->piggy_back();
          char *main_chunk = &((char*)h)[header_type::pos_piggy_back_data];
          // if the main serialization chunk is piggybacked in second SGE

          // determine the size of the chunk buffer
          std::size_t num_zero_copy_chunks =
              static_cast<std::size_t>(
                  static_cast<boost::uint32_t>(h->num_chunks().first));
          std::size_t num_non_zero_copy_chunks =
              static_cast<std::size_t>(
                  static_cast<boost::uint32_t>(h->num_chunks().second)) - (piggy_back ? 1 : 0);
          //
          std::size_t total_chunks = num_zero_copy_chunks + num_non_zero_copy_chunks;

          // since not all code is implemented, setting this flag to false disables final parcel receive call
          bool parcel_complete = true;

          // @TODO : implement this chunk get handling
          std::allocator<char> alloc;
          rcv_buffer_type buffer(alloc);

          performance_counters::parcels::data_point& data = buffer.data_point_;
          data.time_ = timer.elapsed_nanoseconds();
          data.bytes_ = static_cast<std::size_t>(buffer.size_);

          buffer.data_.resize(static_cast<std::size_t>(h->size()));
          buffer.num_chunks_ = h->num_chunks();
          int tag = h->tag();

          // allocate space for chunks
          buffer.transmission_chunks_.resize(total_chunks);

          // for each zerocopy chunk, we must do an rdma get
          if (num_zero_copy_chunks != 0) {
              parcel_complete = false;
              // allocate a parcel_buffer for each chunk
              buffer.chunks_.resize(num_zero_copy_chunks, rcv_data_type(alloc));
              for (std::size_t z=0; z<num_zero_copy_chunks; z++) {
                LOG_ERROR_MSG("Implement RDMA GET operation for zerocopy");
              }
          }

          if (piggy_back) {
              std::memcpy(&buffer.data_[0], piggy_back, buffer.data_.size());
              LOG_DEBUG_MSG("Copied piggyback data into buffer - WHY we want zero-copy");
              if (num_non_zero_copy_chunks != 0) {
                LOG_DEBUG_MSG("Should not ever receive extra chunks when piggybacked data present");
              }
          }

          // for each normal chunk, we must do an rdma get
          if (num_non_zero_copy_chunks != 0) {
              parcel_complete = false;
              // allocate a parcel_buffer for each chunk
              buffer.chunks_.resize(num_non_zero_copy_chunks, rcv_data_type(alloc));
              for (std::size_t z=0; z<num_non_zero_copy_chunks; z++) {
                LOG_ERROR_MSG("Implement RDMA GET operation for normal");
              }
          }



/*
          std::size_t chunk_idx = 0;
          for(auto & c: buffer.chunks_)
          {
              std::size_t chunk_size = buffer.transmission_chunks_[chunk_idx++].second;
              c.resize(chunk_size);
              {
                parcel_complete = false;
                LOG_DEBUG_MSG("Must receive a chunk/message (multiple chunks)");
              }
          }

          data.time_ = timer.elapsed_nanoseconds() - data.time_;
*/
          if (parcel_complete) {
            decode_message(*this, std::move(buffer), 1);
//            decode_parcel(*this, std::move(buffer));
            LOG_DEBUG_MSG("parcel decode called for complete parcel");
          }
          else {
            LOG_DEBUG_MSG("incomplete parcel");
          }
        }
        _rdmaController->refill_client_receives();
        return 0;
      }

      ~parcelport() {
        FUNC_START_DEBUG_MSG;
        _rdmaController = nullptr;
        FUNC_END_DEBUG_MSG;
      }

      /// return true if this pp can be used at bootstrapping, otherwise omit
      bool can_bootstrap() const {
        //    FUNC_START_DEBUG_MSG;
        //    FUNC_END_DEBUG_MSG;
        return false;
      }

      /// Return the name of this locality
      std::string get_locality_name() const {
        FUNC_START_DEBUG_MSG;

        FUNC_END_DEBUG_MSG;
        // return ip address + ?
        return "verbs";
      }

      parcelset::locality agas_locality(util::runtime_configuration const & ini) const {
        FUNC_START_DEBUG_MSG;
        // load all components as described in the configuration information
        if (ini.has_section("hpx.agas")) {
          util::section const* sec = ini.get_section("hpx.agas");
          if (NULL != sec) {
            LOG_DEBUG_MSG("Returning some made up agas locality")
                    return
                        parcelset::locality(
                            locality(
                                _ibv_ip
                                , _port
                            )
                        );
          }
        }
        FUNC_END_DEBUG_MSG;
        // ibverbs can't be used for bootstrapping
        LOG_DEBUG_MSG("Returning NULL agas locality")
        return parcelset::locality(locality(0xFFFF, 0));
      }

      parcelset::locality create_locality() const {
        FUNC_START_DEBUG_MSG;
        FUNC_END_DEBUG_MSG;
        return parcelset::locality(locality());
      }

      void put_parcels(std::vector<parcelset::locality> dests,
          std::vector<parcel> parcels,
          std::vector<write_handler_type> handlers)
      {
          HPX_ASSERT(dests.size() == parcels.size());
          HPX_ASSERT(dests.size() == handlers.size());
          for(std::size_t i = 0; i != dests.size(); ++i)
          {
              put_parcel(dests[i], parcels[i], handlers[i]);
          }
      }

      void send_early_parcel(parcelset::locality const & dest, parcel& p) {
        FUNC_START_DEBUG_MSG;
        FUNC_END_DEBUG_MSG;
        // Only necessary if your PP an be used at bootstrapping
        put_parcel(dest, p, boost::bind(&parcelport::early_write_handler, this, ::_1, p));
      }

      util::io_service_pool* get_thread_pool(char const* name) {
        FUNC_START_DEBUG_MSG;
        FUNC_END_DEBUG_MSG;
        return 0;
      }

      // This parcelport doesn't maintain a connection cache
      boost::int64_t get_connection_cache_statistics(connection_cache_statistics_type, bool reset) {
        FUNC_START_DEBUG_MSG;
        FUNC_END_DEBUG_MSG;
        return 0;
      }

      void remove_from_connection_cache(parcelset::locality const& loc) {
        FUNC_START_DEBUG_MSG;
        FUNC_END_DEBUG_MSG;
      }

      bool run(bool blocking = true) {
        FUNC_START_DEBUG_MSG;
        _rdmaController->startup();
    #ifdef JB_MEM_POOL
        LOG_DEBUG_MSG("Fetching memory pool");
        chunk_pool_ = _rdmaController->getMemoryPool();
    #endif
        LOG_DEBUG_MSG("Setting Completion function");
        // need to use std:bind here as rdmahelper lib uses it too
        auto completion_function = std::bind( &parcelport::handle_verbs_completion, this, std::placeholders::_1, std::placeholders::_2);
        _rdmaController->setCompletionFunction(completion_function);

        FUNC_END_DEBUG_MSG;
        // This should start the receiving side of your PP
        return true;
      }

      void stop(bool blocking = true) {
        FUNC_START_DEBUG_MSG;
            stopped_ = true;
        FUNC_END_DEBUG_MSG;
        // Stop receiving and sending of parcels
      }

      void enable(bool new_state) {
        FUNC_START_DEBUG_MSG;
        FUNC_END_DEBUG_MSG;
        // enable/disable sending and receiving of parcels
      }

      int archive_flags_;
      boost::atomic<bool> stopped_;

      typedef header<DEFAULT_MEMORY_POOL_CHUNK_SIZE>          header_type;
      typedef hpx::lcos::local::spinlock                      mutex_type;
    #ifdef JB_MEM_POOL
      typedef char                                            memory_type;
      typedef RdmaMemoryPool                                  memory_pool_type;
      typedef std::shared_ptr<memory_pool_type>               memory_pool_ptr_type;
      typedef hpx::util::detail::memory_chunk_pool_allocator
          <memory_type, memory_pool_type, mutex_type>         allocator_type;
      typedef std::vector<memory_type, allocator_type>        snd_data_type;
      typedef std::vector<memory_type, std::allocator<memory_type>>  rcv_data_type;
      typedef parcel_buffer<snd_data_type>                        snd_buffer_type;
      typedef parcel_buffer<rcv_data_type, rcv_data_type>         rcv_buffer_type;
      memory_pool_ptr_type                                    chunk_pool_;
    #else
      typedef util::memory_chunk_pool<>                       memory_pool_type;
      typedef hpx::util::detail::memory_chunk_pool_allocator
          <char, memory_pool_type, mutex_type> allocator_type;
      typedef std::vector<char, allocator_type>               data_type;
      typedef parcel_buffer<data_type>                        snd_buffer_type;
      typedef parcel_buffer<data_type, data_type>             rcv_buffer_type;
      memory_pool_type                                        chunk_pool_;
    #endif
      tag_provider tag_provider_;

//      performance_counters::parcels::gatherer& parcels_sent_;

      typedef std::tuple<parcelset::parcel, parcelset::parcelhandler::write_handler_type, uint64_t> handler_tuple;
      typedef std::map<uint64_t, handler_tuple> send_wr_map;

      typedef std::pair<parcelset::parcel, parcelset::parcelhandler::write_handler_type> handler_pair;
      typedef std::map<uint64_t, handler_pair> get_wr_map;

      // store na_verbs_op_id objects using a map referenced by verbs work request ID
      send_wr_map SendCompletionMap;
      get_wr_map ZeroCopyGetCompletionMap;

      void put_parcel(parcelset::locality const & dest, parcel p, write_handler_type f) {
        FUNC_START_DEBUG_MSG;
        boost::uint32_t dest_ip = dest.get<locality>().ip_;
        LOG_DEBUG_MSG("Locality " << ipaddress(_ibv_ip) << " Sending packet to " << ipaddress(dest_ip) );
        //
        RdmaClientPtr client;
        ip_map_iterator ip_it = ip_qp_map.find(dest_ip);
        if (ip_it!=ip_qp_map.end()) {
          LOG_DEBUG_MSG("Connection found with qp " << ip_it->second);
          client = _rdmaController->getClient(ip_it->second);
        }
        else {
          LOG_DEBUG_MSG("Connection required to " << ipaddress(dest_ip));
          client = _rdmaController->makeServerToServerConnection(dest_ip, _rdmaController->getPort());
          ip_qp_map[dest_ip] = client->getQpNum();
        }

        // connection ok, we can now send required info to the remote peer
        {
          util::high_resolution_timer timer;
    #ifdef JB_MEM_POOL
          allocator_type alloc(*chunk_pool_.get());
          snd_buffer_type buffer(alloc);
    #else
          allocator_type alloc(chunk_pool_);
          snd_buffer_type buffer(alloc);
    #endif
          // encode the parcel directly into an rdma pinned memory block
          // if the serialization overflows the block, panic and rewrite this.
          LOG_DEBUG_MSG("Encoding parcel");
          encode_parcels(&p, std::size_t(-1), buffer, archive_flags_, chunk_pool_->default_chunk_size());
          buffer.data_point_.time_ = timer.elapsed_nanoseconds();

          // create a tag (not used at the moment)
          tag_provider::tag tag(tag_provider_());
          LOG_DEBUG_MSG("Tag generated is " << tag.tag_);

          // Get the block of pinned memory where the message was encoded
          LOG_DEBUG_MSG("Marking block for the header ");
          RdmaMemoryRegion *chunk_region = chunk_pool_->RegionFromAddress((char*)buffer.data_.data());

          RdmaMemoryRegion *header_region = chunk_pool_->allocateRegion();
          char *header_memory = (char*)(header_region->getAddress());

          // create the header in the pinned memory block
          LOG_DEBUG_MSG("Placement new for the header with piggyback copy disabled");
          header_type *h = new(header_memory) header_type(buffer, tag, true);
          h->assert_valid();
          LOG_DEBUG_MSG(
                 "buffer size is " << decnumber(h->size())
              << "numbytes is " << decnumber(h->numbytes())
              << "num_chunks is zerocopy( " << decnumber(h->num_chunks().first) << ") "
              << ", normal( " << decnumber(h->num_chunks().second) << ") "
              << "tag is " << decnumber(h->tag())
              );

          // for each zerocopy chunk, we must create a memory region
          if (h->num_chunks().first>0) {
            for (int c=0; c<h->num_chunks().first; c++) {
              LOG_ERROR_MSG("Implement zero copy registered block info for chunk " << c);
            }
          }

          auto & chunks = buffer.transmission_chunks_;
          if (!chunks.empty())
          {
            if (chunks.size())
              {
              LOG_DEBUG_MSG("Chunks size is " << chunks.size() << " and sizeof transmission_chunk_type is "
                  << sizeof(typename snd_buffer_type::transmission_chunk_type));

//                  util::mpi_environment::scoped_lock l;
//                  MPI_Isend(
//                      chunks.data()
//                    , static_cast<int>(
//                          chunks.size()
//                        * sizeof(typename Buffer::transmission_chunk_type)
//                      )
//                    , MPI_BYTE
//                    , dest
//                    , tag
//                    , util::mpi_environment::communicator()
//                    , &request
//                  );
//                  wait_request = &request;
              }
          }

          // send the header to the destination, add wr_id to completion map
          chunk_region->setMessageLength(h->size());
          header_region->setMessageLength(header_type::pos_piggy_back_data);
          RdmaMemoryRegion *rlist[] = { header_region, chunk_region };
          uint64_t wr_id = client->postSend_xN(rlist, 2, true, false, 0);
          SendCompletionMap[wr_id] = std::make_tuple(p, f, (uint64_t)(chunk_region));
          LOG_DEBUG_MSG("wr_id for send added to WR completion map "
              << hexpointer(wr_id) << " Entries " << SendCompletionMap.size());

          // log the time spent in performance counter
          buffer.data_point_.time_ =
              timer.elapsed_nanoseconds() - buffer.data_point_.time_;
//          parcels_sent_.add_data(buffer.data_point_);

        }
        // Send a single parcel, after successful sending, f should be called.
        FUNC_END_DEBUG_MSG;
      }

      bool do_background_work(std::size_t num_thread) {
            if (stopped_)
                return false;
         //    FUNC_START_DEBUG_MSG;
        _rdmaController->eventMonitor(0);
        //    FUNC_END_DEBUG_MSG;
        // This is called whenever a HPX OS thread is idling, can be used to poll for incoming messages
        return true;
      }

    private:

      // Only needed for bootstrapping
      void early_write_handler(boost::system::error_code const& ec, parcel const & p) {
        FUNC_START_DEBUG_MSG;
        if (ec) {
          // all errors during early parcel handling are fatal
          boost::exception_ptr exception = hpx::detail::get_exception(hpx::exception(ec), "mpi::early_write_handler",
              __FILE__, __LINE__,
              "error while handling early parcel: " + ec.message() + "(" + boost::lexical_cast < std::string
              > (ec.value()) + ")" + parcelset::dump_parcel(p));

          hpx::report_error(exception);
        }
        FUNC_END_DEBUG_MSG;
      }
    };
}
}
}
}

namespace hpx {
namespace traits {
// Inject additional configuration data into the factory registry for this
// type. This information ends up in the system wide configuration database
// under the plugin specific section:
//
//      [hpx.parcel.verbs]
//      ...
//      priority = 100
//
template<>
struct plugin_config_data<hpx::parcelset::policies::verbs::parcelport> {
  static char const* priority() {
    FUNC_START_DEBUG_MSG;
    static int log_init = false;
    if (!log_init) {
      initLogging();
      log_init = true;
    }
    FUNC_END_DEBUG_MSG;
    return "100";
  }

  // This is used to initialize your parcelport, for example check for availability of devices etc.
  static void init(int *argc, char ***argv, util::command_line_handling &cfg) {
    FUNC_START_DEBUG_MSG;

    FUNC_END_DEBUG_MSG;
  }

  static char const* call() {
    FUNC_START_DEBUG_MSG;
    FUNC_END_DEBUG_MSG;

//      LOG_DEBUG_MSG("\n"
//          "ifname = ${HPX_PARCELPORT_VERBS_IFNAME:" HPX_PARCELPORT_VERBS_IFNAME "}\n"
//          "device = ${HPX_PARCELPORT_VERBS_DEVICE:" HPX_PARCELPORT_VERBS_DEVICE "}\n"
//          "interface = ${HPX_PARCELPORT_VERBS_INTERFACE:" HPX_PARCELPORT_VERBS_INTERFACE "}\n"
//          "memory_chunk_size = ${HPX_PARCEL_IBVERBS_MEMORY_CHUNK_SIZE:"
//          BOOST_PP_STRINGIZE(HPX_PARCELPORT_VERBS_MEMORY_CHUNK_SIZE) "}\n"
//          "max_memory_chunks = ${HPX_PARCEL_IBVERBS_MAX_MEMORY_CHUNKS:"
//          BOOST_PP_STRINGIZE(HPX_PARCELPORT_VERBS_MAX_MEMORY_CHUNKS) "}\n"
//          "zero_copy_optimization = 0\n"
//          "io_pool_size = 2\n"
//          "use_io_pool = 1\n"
//          "enable = 0");
    return
        "ifname = ${HPX_PARCELPORT_VERBS_IFNAME:" HPX_PARCELPORT_VERBS_IFNAME "}\n"
        "device = ${HPX_PARCELPORT_VERBS_DEVICE:" HPX_PARCELPORT_VERBS_DEVICE "}\n"
        "interface = ${HPX_PARCELPORT_VERBS_INTERFACE:" HPX_PARCELPORT_VERBS_INTERFACE "}\n"
        "memory_chunk_size = ${HPX_PARCEL_IBVERBS_MEMORY_CHUNK_SIZE:"
        BOOST_PP_STRINGIZE(HPX_PARCELPORT_VERBS_MEMORY_CHUNK_SIZE) "}\n"
    "max_memory_chunks = ${HPX_PARCEL_IBVERBS_MAX_MEMORY_CHUNKS:"
    BOOST_PP_STRINGIZE(HPX_PARCELPORT_VERBS_MAX_MEMORY_CHUNKS) "}\n"
    "zero_copy_optimization = 0\n"
    "io_pool_size = 2\n"
    "use_io_pool = 1\n"
    "enable = 0"
    ;
  }
};
}
}
RdmaControllerPtr hpx::parcelset::policies::verbs::parcelport::_rdmaController;
std::string       hpx::parcelset::policies::verbs::parcelport::_ibverbs_ifname;
std::string       hpx::parcelset::policies::verbs::parcelport::_ibverbs_device;
std::string       hpx::parcelset::policies::verbs::parcelport::_ibverbs_interface;
boost::uint32_t   hpx::parcelset::policies::verbs::parcelport::_ibv_ip;
boost::uint32_t   hpx::parcelset::policies::verbs::parcelport::_port;


HPX_REGISTER_PARCELPORT(hpx::parcelset::policies::verbs::parcelport, verbs);

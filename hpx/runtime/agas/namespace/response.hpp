////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPX_FB40C7A4_33B0_4C64_A16B_2A3FEEB237ED)
#define HPX_FB40C7A4_33B0_4C64_A16B_2A3FEEB237ED

#include <boost/move/move.hpp>
#include <boost/assert.hpp>
#include <boost/variant.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include <hpx/exception.hpp>
#include <hpx/util/serialize_sequence.hpp>
#include <hpx/runtime/agas/namespace/method_code.hpp>
#include <hpx/runtime/agas/network/gva.hpp>
#include <hpx/runtime/naming/name.hpp>
#include <hpx/runtime/components/component_type.hpp>

// The number of types that response's variant can represent.
#define HPX_AGAS_RESPONSE_SUBTYPES 8

namespace hpx { namespace agas
{

// TODO: Ensure that multiple invocations of get_data get optimized into the
// same jump table.
template <
    typename Protocol
>
struct response
{
  public:
    response()
        : mc(invalid_request) 
        , status(invalid_status)
        , data(boost::fusion::make_vector())
    {}

    response(
        method_code type_
      , naming::gid_type lower_
      , naming::gid_type upper_
      , boost::uint32_t prefix_
      , error status_ = success
        )
      : mc(type_)
      , status(status_)
      , data(boost::fusion::make_vector(lower_, upper_, prefix_))
    {
        // TODO: verification of method_code
    }

    response(
        method_code type_
      , gva<Protocol> const& gva_
      , boost::uint32_t prefix_
      , error status_ = success
        )
      : mc(type_)
      , status(status_)
      , data(boost::fusion::make_vector(gva_, prefix_))
    {
        // TODO: verification of method_code
    }

    response(
        method_code type_
      , gva<Protocol> const& gva_
      , error status_ = success
        )
      : mc(type_)
      , status(status_)
      , data(boost::fusion::make_vector(gva_))
    {
        // TODO: verification of method_code
    }

    response(
        method_code type_
      , boost::uint64_t count_
      , boost::int32_t ctype_
      , error status_ = success
        )
      : mc(type_)
      , status(status_)
      , data(boost::fusion::make_vector(count_, ctype_))
    {
        // TODO: verification of method_code
    }

    response(
        method_code type_
      , boost::uint64_t count_
      , components::component_type ctype_
      , error status_ = success
        )
      : mc(type_)
      , status(status_)
      , data(boost::fusion::make_vector(count_, boost::int32_t(ctype_)))
    {
        // TODO: verification of method_code
    }

    response(
        method_code type_
      , boost::uint64_t count_
      , error status_ = success
        )
      : mc(type_)
      , status(status_)
      , data(boost::fusion::make_vector(count_))
    {
        // TODO: verification of method_code
    }
    
    response(
        method_code type_
      , components::component_type ctype_
      , error status_ = success
        )
      : mc(type_)
      , status(status_)
      , data(boost::fusion::make_vector(boost::int32_t(ctype_)))
    {
        // TODO: verification of method_code
    }

    response(
        method_code type_
      , boost::int32_t ctype_
      , error status_ = success
        )
      : mc(type_)
      , status(status_)
      , data(boost::fusion::make_vector(ctype_))
    {
        // TODO: verification of method_code
    }

    response(
        method_code type_
      , std::vector<boost::uint32_t> const& prefixes_
      , error status_ = success
        )
      : mc(type_)
      , status(status_)
      , data(boost::fusion::make_vector(prefixes_))
    {
        // TODO: verification of method_code
    }

    response(
        method_code type_
      , naming::gid_type gid_
      , error status_ = success
        )
      : mc(type_)
      , status(status_)
      , data(boost::fusion::make_vector(gid_))
    {
        // TODO: verification of method_code
    }

    response(
        method_code type_
      , error status_ = success
        )
      : mc(type_)
      , status(status_)
      , data(boost::fusion::make_vector())
    {
        // TODO: verification of method_code
    }

    // copy constructor
    response(
        response const& other
        )
      : mc(other.mc)
      , status(other.status)
      , data(other.data)
    {}   

    // copy assignment
    response& operator=(
        response const& other
        )
    {
        if (this != &other)
        {
            mc = other.mc;
            status = other.status;
            data = other.data;
        } 
        return *this;
    }

    gva<Protocol> get_gva(
        error_code& ec = throws
        ) const
    { 
        return get_data<subtype_gva, 0>(ec); 
    } 

    boost::uint64_t get_count(
        error_code& ec = throws
        ) const
    { // {{{
        boost::uint64_t ctype = 0;

        // Don't let the first attempt throw.
        error_code first_try;
        ctype = get_data<subtype_count, 0>(first_try);

        // If the first try failed, check again.
        if (first_try)
            ctype = get_data<subtype_count_ctype, 0>(ec);
        else if (&ec != &throws)
            ec = make_success_code();

        return ctype; 
    } // }}} 

    std::vector<boost::uint32_t> get_localities(
        error_code& ec = throws
        ) const
    { 
        return get_data<subtype_prefixes, 0>(ec); 
    } 

    boost::int32_t get_component_type(
        error_code& ec = throws
        ) const
    { // {{{
        boost::int32_t ctype = 0;

        // Don't let the first attempt throw.
        error_code first_try;
        ctype = get_data<subtype_ctype, 0>(first_try);

        // If the first try failed, check again.
        if (first_try)
            ctype = get_data<subtype_count_ctype, 1>(ec);
        else if (&ec != &throws)
            ec = make_success_code();

        return ctype; 
    } // }}} 

    boost::uint32_t get_prefix(
        error_code& ec = throws
        ) const
    { 
        return get_data<subtype_gid_gid_prefix, 2>(ec); 
    } 

    naming::gid_type get_gid(
        error_code& ec = throws
        ) const
    { 
        return get_data<subtype_gid, 0>(ec); 
    } 

    naming::gid_type get_lower_bound(
        error_code& ec = throws
        ) const
    {
        return get_data<subtype_gid_gid_prefix, 0>(ec); 
    }

    naming::gid_type get_upper_bound(
        error_code& ec = throws
        ) const
    {
        return get_data<subtype_gid_gid_prefix, 1>(ec); 
    }

    method_code get_method() const
    {
        return mc;
    }

    error get_status() const
    {
        return status;
    } 
 
  private:
    friend class boost::serialization::access;

    enum subtype
    {
        subtype_gid_gid_prefix  = 0x0
      , subtype_gva             = 0x1
      , subtype_count_ctype     = 0x2
      , subtype_count           = 0x3
      , subtype_ctype           = 0x4
      , subtype_prefixes        = 0x5
      , subtype_gid             = 0x6
      , subtype_void            = 0x7
    }; 

    // The order of the variant types is significant, and should not be changed
    typedef boost::variant<
        // 0x0
        // primary_ns_bind_locality
        boost::fusion::vector3<
            naming::gid_type // lower bound
          , naming::gid_type // upper bound 
          , boost::uint32_t  // prefix 
        >
        // 0x1
        // primary_ns_resolve_gid
        // primary_ns_unbind_gid
      , boost::fusion::vector1<
            gva<Protocol>   // gva
        >
        // 0x2
        // primary_ns_decrement
      , boost::fusion::vector2<
            boost::uint64_t // count
          , boost::int32_t  // ctype
        > 
        // 0x3
        // primary_ns_increment
      , boost::fusion::vector1<
            boost::uint64_t // count
        >
        // 0x4
        // component_ns_bind_prefix
        // component_ns_bind_name
        // component_ns_resolve_name
      , boost::fusion::vector1<
            boost::int32_t // ctype
        > 
        // 0x5
        // primary_ns_localities
        // component_ns_resolve_id
      , boost::fusion::vector1<
            std::vector<boost::uint32_t> // prefixes
        >
        // 0x6 
        // symbol_ns_resolve
      , boost::fusion::vector1<
            naming::gid_type // gid
        >
        // 0x7
        // primary_ns_unbind_locality
        // primary_ns_bind_gid
        // component_ns_unbind
        // symbol_ns_bind
        // symbol_ns_unbind
        // symbol_ns_iterate
      , boost::fusion::vector0<
        >
    > data_type;

    template <
        subtype Type
      , int N
    >
    typename boost::fusion::result_of::value_at_c<
        typename boost::mpl::at_c<
            typename data_type::types, Type
        >::type, N
    >::type
    get_data(
        error_code& ec = throws
        ) const
    { // {{{
        typedef typename boost::mpl::at_c<
            typename data_type::types, Type
        >::type vector_type;

        typedef typename boost::fusion::result_of::value_at_c<
            vector_type, N
        >::type return_type;

        switch (data.which())
        {
            case Type:
            {
                vector_type const* v = boost::get<vector_type>(&data); 

                if (!v)
                {
                    HPX_THROWS_IF(ec, invalid_data
                      , "response::get_data"
                      , "internal data corruption"); 
                    return return_type(); 
                }

                if (&ec != &throws)
                    ec = make_success_code();

                return boost::fusion::at_c<N>(*v);
            }

            default: {
                HPX_THROWS_IF(ec, bad_parameter, 
                    "response::get_data",
                    "invalid operation for request type");
                return return_type();
            }
        };
    } // }}} 

    template <
        typename Archive
    >
    struct save_visitor : boost::static_visitor<void> 
    {
      private:
        Archive& ar;

      public:
        save_visitor(
            Archive& ar_
            )
          : ar(ar_)
        {}

        template <
            typename Sequence
        >
        void operator()(
            Sequence const& seq
            ) const
        {
            // TODO: verification?
            util::serialize_sequence(ar, seq);
        }
    }; 

    template <
        typename Archive
    >
    void save(
        Archive& ar
      , const unsigned int
        ) const
    { // {{{
        // TODO: versioning?
        int which = data.which();

        ar & which; 
        ar & mc;
        ar & status;
        boost::apply_visitor(save_visitor<Archive>(ar), data);  
    } // }}}

#define HPX_LOAD_SEQUENCE(z, n, _)                                          \
    case n:                                                                 \
        {                                                                   \
            typename boost::mpl::at_c<                                      \
                typename data_type::types, n                                \
            >::type d;                                                      \
            util::serialize_sequence(ar, d);                                \
            data = d;                                                       \
            return;                                                         \
        }                                                                   \
    /**/

    template <
        typename Archive
    >
    void load(
        Archive& ar
      , const unsigned int
        )
    { // {{{
        // TODO: versioning
        int which = -1;

        ar & which;
        ar & mc;
        ar & status;

        // Build the jump table.
        switch (which)
        {
            BOOST_PP_REPEAT(HPX_AGAS_RESPONSE_SUBTYPES, HPX_LOAD_SEQUENCE, _)

            default: {
                HPX_THROW_EXCEPTION(invalid_data, 
                    "response::load",
                    "unknown or invalid data loaded");
                return;
            }
        };
    } // }}}

#undef HPX_LOAD_SEQUENCE

    BOOST_SERIALIZATION_SPLIT_MEMBER()

    method_code mc;
    error status;
    data_type data;
};

}}

#endif // HPX_FB40C7A4_33B0_4C64_A16B_2A3FEEB237ED


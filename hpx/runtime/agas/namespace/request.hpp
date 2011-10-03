////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPX_AB01A9FE_45BE_43EF_B9AD_05B701B06685)
#define HPX_AB01A9FE_45BE_43EF_B9AD_05B701B06685

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

// The number of types that request's variant can represent.
#define HPX_AGAS_REQUEST_SUBTYPES 9

namespace hpx { namespace agas
{

// TODO: Ensure that multiple invocations of get_data get optimized into the
// same jump table.
struct request
{
  public:
    request()
        : mc(invalid_request) 
        , data(boost::fusion::make_vector())
    {}

    // REVIEW: Should the GVA here be a resolved address?
    request(
        method_code type_
      , naming::gid_type const& gid_
      , gva const& gva_ 
        )
      : mc(type_)
      , data(boost::fusion::make_vector(gid_, gva_))
    {
        // TODO: verification of method_code
    }

    request(
        method_code type_
      , naming::gid_type const& gid_
      , boost::uint64_t count_  
        )
      : mc(type_)
      , data(boost::fusion::make_vector(gid_, count_))
    {
        // TODO: verification of method_code
    }

    request(
        method_code type_
      , naming::gid_type const& gid_
        )
      : mc(type_)
      , data(boost::fusion::make_vector(gid_))
    {
        // TODO: verification of method_code
    }

    request(
        method_code type_
      , naming::locality const& locality_
      , boost::uint64_t count_  
        )
      : mc(type_)
      , data(boost::fusion::make_vector(locality_, count_))
    {
        // TODO: verification of method_code
    }

    request(
        method_code type_
      , naming::locality const& locality_
        )
      : mc(type_)
      , data(boost::fusion::make_vector(locality_))
    {
        // TODO: verification of method_code
    }

    request(
        method_code type_
      , components::component_type ctype_ 
        )
      : mc(type_)
      , data(boost::fusion::make_vector(boost::int32_t(ctype_)))
    {
        // TODO: verification of method_code
    }

    request(
        method_code type_
      , boost::int32_t ctype_ 
        )
      : mc(type_)
      , data(boost::fusion::make_vector(ctype_))
    {
        // TODO: verification of method_code
    }

    request(
        method_code type_
      , std::string const& name_
      , boost::uint32_t prefix_ 
        )
      : mc(type_)
      , data(boost::fusion::make_vector(name_, prefix_))
    {
        // TODO: verification of method_code
    }

    request(
        method_code type_
      , std::string const& name_
      , naming::gid_type const& gid_ 
        )
      : mc(type_)
      , data(boost::fusion::make_vector(name_, gid_))
    {
        // TODO: verification of method_code
    }

    request(
        method_code type_
      , std::string const& name_
        )
      : mc(type_)
      , data(boost::fusion::make_vector(name_))
    {
        // TODO: verification of method_code
    }

    request(
        method_code type_
      , symbol_namespace::iterate_function_type const& f_ 
        )
      : mc(type_)
      , data(boost::fusion::make_vector(f_))
    {
        // TODO: verification of method_code
    }

    request(
        method_code type_
        )
      : mc(type_)
      , data(boost::fusion::make_vector())
    {
        // TODO: verification of method_code
    }

    // copy constructor
    request(
        request const& other
        )
      : mc(other.mc)
      , data(other.data)
    {}   

    // copy assignment
    request& operator=(
        request const& other
        )
    {
        if (this != &other)
        {
            mc = other.mc;
            data = other.data;
        } 
        return *this;
    }

    gva get_gva(
        error_code& ec = throws
        ) const
    { 
        return get_data<subtype_gid_gva, 1>(ec); 
    } 

    boost::uint64_t get_count(
        error_code& ec = throws
        ) const
    { // {{{
        boost::uint64_t count = 0;

        // Don't let the first attempt throw.
        error_code first_try;
        count = get_data<subtype_gid_count, 1>(first_try);

        // If the first try failed, check again.
        if (first_try)
            count = get_data<subtype_locality_count, 1>(ec);
        else if (&ec != &throws)
            ec = make_success_code();

        return count; 
    } // }}} 

    boost::int32_t get_component_type(
        error_code& ec = throws
        ) const
    { 
        return get_data<subtype_ctype, 0>(ec); 
    } 

    boost::uint32_t get_prefix(
        error_code& ec = throws
        ) const
    { 
        return get_data<subtype_name_prefix, 1>(ec); 
    } 

    symbol_namespace::iterate_function_type get_iterate_function(
        error_code& ec = throws
        ) const
    { 
        return get_data<subtype_iterate_function, 0>(ec); 
    } 

    naming::locality get_locality(
        error_code& ec = throws
        ) const
    { // {{{
        naming::locality l;

        // Don't let the first attempt throw.
        error_code first_try;
        l = get_data<subtype_locality_count, 0>(first_try);

        // If the first try failed, check again.
        if (first_try)
            l = get_data<subtype_locality, 0>(ec);
        else if (&ec != &throws)
            ec = make_success_code();

        return l; 
    } // }}} 
    
    naming::gid_type get_gid(
        error_code& ec = throws
        ) const
    { // {{{ 
        naming::gid_type gid = naming::invalid_gid;

        // Don't let any attempt except the last throw.
        error_code try_;
        gid = get_data<subtype_gid, 0>(try_);

        // If the first try failed, check again.
        if (try_)
            gid = get_data<subtype_gid_gva, 0>(try_);

        else if (&ec != &throws)
        {
            ec = make_success_code();
            return gid;
        }

        // If the second try failed, check again.
        if (try_)
            gid = get_data<subtype_gid_count, 0>(try_);

        else if (&ec != &throws)
        {
            ec = make_success_code();
            return gid;
        }
 
        // If the third try failed, check again.
        if (try_)
            gid = get_data<subtype_name_gid, 1>(ec);

        else if (&ec != &throws)
            ec = make_success_code();

        return gid;
    } // }}} 

    std::string get_name(
        error_code& ec = throws
        ) const
    { // {{{ 
        std::string name = "";

        // Don't let any attempt except the last throw.
        error_code try_;
        name = get_data<subtype_name, 0>(try_);

        // If the first try failed, check again.
        if (try_)
            name = get_data<subtype_name_prefix, 0>(try_);

        else if (&ec != &throws)
        {
            ec = make_success_code();
            return name;
        }

        // If the second try failed, check again.
        if (try_)
            name = get_data<subtype_name_gid, 0>(ec);

        else if (&ec != &throws)
            ec = make_success_code();

        return name;
    } // }}} 

    method_code get_method() const
    {
        return mc;
    }
 
  private:
    friend class boost::serialization::access;

    enum subtype
    {
        subtype_gid_gva             = 0x0
      , subtype_gid_count           = 0x1
      , subtype_gid                 = 0x2
      , subtype_locality_count      = 0x3
      , subtype_locality            = 0x4
      , subtype_ctype               = 0x5
      , subtype_name_prefix         = 0x6
      , subtype_name_gid            = 0x7
      , subtype_name                = 0x8
      , subtype_iterate_function    = 0x9
      , subtype_void                = 0xa
    }; 

    // The order of the variant types is significant, and should not be changed
    typedef boost::variant<
        // 0x0
        // primary_ns_bind_gid
      , boost::fusion::vector2<
            naming::gid_type                        // gid
          , gva                                     // resolved address
        >
        // 0x1
        // primary_ns_unbind_gid
        // primary_ns_increment
        // primary_ns_decrement
      , boost::fusion::vector2<
            naming::gid_type                        // gid
          , boost::uint64_t                         // count
        >
        // 0x2
        // primary_ns_page_fault
      , boost::fusion::vector1<
            naming::gid_type                        // gid
        >
        // 0x3
        // primary_ns_bind_locality
      , boost::fusion::vector2<
            naming::locality                        // locality
          , boost::uint64_t                         // count
        >
        // 0x4
        // primary_ns_unbind_locality
      , boost::fusion::vector1<
            naming::locality                        // locality
        >
        // 0x5
        // component_ns_resolve_id
      , boost::fusion::vector1<
          , boost::int32_t                          // ctype 
        >
        // 0x6
        // component_ns_bind_prefix
      , boost::fusion::vector2<
            std::string                             // name 
          , boost::uint32_t                         // prefix 
        >
        // 0x7
        // symbol_ns_bind
      , boost::fusion::vector2<
            std::string                             // name 
          , naming::gid_type                        // gid 
        >
        // 0x8
        // component_ns_resolve_name
        // component_ns_bind_name
        // component_ns_unbind
        // symbol_ns_resolve
        // symbol_ns_unbind
      , boost::fusion::vector1<
            std::string                             // name 
        >
        // 0x9
        // symbol_ns_iterate
      , boost::fusion::vector1<
            symbol_namespace::iterate_function_type // f
        >
        // 0xa
        // primary_ns_localities
      , boost::fusion::vector0<
        >
    > data_type;

    // {{{ variant helper TODO: consolidate with helpers in response
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
                      , "request::get_data"
                      , "internal data corruption"); 
                    return return_type(); 
                }

                if (&ec != &throws)
                    ec = make_success_code();

                return boost::fusion::at_c<N>(*v);
            }

            default: {
                HPX_THROWS_IF(ec, bad_parameter, 
                    "request::get_data",
                    "invalid operation for request type");
                return return_type();
            }
        };
    } // }}} 
    // }}}

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

        // Build the jump table.
        switch (which)
        {
            BOOST_PP_REPEAT(HPX_AGAS_REQUEST_SUBTYPES, HPX_LOAD_SEQUENCE, _)

            default: {
                HPX_THROW_EXCEPTION(invalid_data, 
                    "request::load",
                    "unknown or invalid data loaded");
                return;
            }
        };
    } // }}}

#undef HPX_LOAD_SEQUENCE

    BOOST_SERIALIZATION_SPLIT_MEMBER()

    method_code mc;
    data_type data;
};

}}

#endif // HPX_AB01A9FE_45BE_43EF_B9AD_05B701B06685


//  Copyright (c) 2015-2016 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_main.hpp>
#include <hpx/include/naming.hpp>
#include <hpx/include/components.hpp>
#include <hpx/include/actions.hpp>
#include <hpx/include/component_storage.hpp>
#include <hpx/util/lightweight_test.hpp>

///////////////////////////////////////////////////////////////////////////////
struct test_server
  : hpx::components::migration_support<
        hpx::components::simple_component_base<test_server>
    >
{
    test_server(int data = 0) : data_(data) {}
    ~test_server() {}

    hpx::id_type call() const
    {
        return hpx::find_here();
    }

    void busy_work() const
    {
        hpx::this_thread::sleep_for(boost::chrono::seconds(1));
    }

    int get_data() const
    {
        return data_;
    }

    // Components which should be migrated using hpx::migrate<> need to
    // be Serializable and CopyConstructable. Components can be
    // MoveConstructable in which case the serialized data is moved into the
    // components constructor.
    test_server(test_server const& rhs) : data_(rhs.data_) {}
    test_server(test_server && rhs) : data_(rhs.data_) {}

    test_server& operator=(test_server const & rhs)
    {
        data_ = rhs.data_;
        return *this;
    }
    test_server& operator=(test_server && rhs)
    {
        data_ = rhs.data_;
        return *this;
    }

    HPX_DEFINE_COMPONENT_ACTION(test_server, call, call_action);
    HPX_DEFINE_COMPONENT_ACTION(test_server, busy_work, busy_work_action);
    HPX_DEFINE_COMPONENT_ACTION(test_server, get_data, get_data_action);

    template <typename Archive>
    void serialize(Archive& ar, unsigned version)
    {
        ar & data_;
    }

private:
    int data_;
};

typedef hpx::components::simple_component<test_server> server_type;
HPX_REGISTER_COMPONENT(server_type, test_server);

typedef test_server::call_action call_action;
HPX_REGISTER_ACTION_DECLARATION(call_action);
HPX_REGISTER_ACTION(call_action);

typedef test_server::busy_work_action busy_work_action;
HPX_REGISTER_ACTION_DECLARATION(busy_work_action);
HPX_REGISTER_ACTION(busy_work_action);

typedef test_server::get_data_action get_data_action;
HPX_REGISTER_ACTION_DECLARATION(get_data_action);
HPX_REGISTER_ACTION(get_data_action);

struct test_client
  : hpx::components::client_base<test_client, test_server>
{
    typedef hpx::components::client_base<test_client, test_server>
        base_type;

    test_client() {}

    test_client(hpx::shared_future<hpx::id_type> const& id) : base_type(id) {}

    hpx::id_type call() const
    {
        return call_action()(this->get_id());
    }

    hpx::future<void> busy_work() const
    {
        return hpx::async<busy_work_action>(this->get_id());
    }

    int get_data() const
    {
        return get_data_action()(this->get_id());
    }
};

///////////////////////////////////////////////////////////////////////////////
bool test_migrate_component_to_storage(hpx::id_type const& source,
    hpx::components::component_storage storage, hpx::id_type::management_type t)
{
    hpx::id_type oldid;

    {
        // create component on given locality
        test_client t1 = hpx::new_<test_client>(source, 42);
        HPX_TEST_NEQ(hpx::naming::invalid_id, t1.get_id());

        // the new object should live on the source locality
        HPX_TEST_EQ(t1.call(), source);
        HPX_TEST_EQ(t1.get_data(), 42);

        // remember the original id for later resurrection
        oldid = hpx::id_type(t1.get_id().get_gid(), t);

        try {
            // migrate of t1 to the target storage
            test_client t2(hpx::components::migrate_to_storage(t1, storage));
            HPX_TEST_EQ(hpx::naming::invalid_id, t2.get_id());
        }
        catch (hpx::exception const&) {
            return false;
        }

        HPX_TEST_EQ(storage.size_sync(), std::size_t(1));

        // make sure all local references go out of scope if t == unmanaged
    }

    HPX_TEST_EQ(storage.size_sync(), std::size_t(1));

    {
        test_client t1(hpx::components::migrate_from_storage<test_server>(oldid));

        // the id of the newly resurrected object should be the same as the old id
        HPX_TEST_EQ(oldid, t1.get_id());

        // the new object should live on the (original) source locality
        HPX_TEST_EQ(t1.call(), source);
        HPX_TEST_EQ(t1.get_data(), 42);

        HPX_TEST_EQ(storage.size_sync(), std::size_t(0));
    }

    return true;
}

bool test_migrate_component_to_storage(hpx::id_type const& source,
    hpx::id_type const& target, hpx::components::component_storage storage,
    hpx::id_type::management_type t)
{
    hpx::id_type oldid;

    {
        // create component on given locality
        test_client t1 = hpx::new_<test_client>(source, 42);
        HPX_TEST_NEQ(hpx::naming::invalid_id, t1.get_id());

        // the new object should live on the source locality
        HPX_TEST_EQ(t1.call(), source);
        HPX_TEST_EQ(t1.get_data(), 42);

        // remember the original id for later resurrection
        oldid = hpx::id_type(t1.get_id().get_gid(), t);

        try {
            // migrate of t1 to the target storage
            test_client t2(hpx::components::migrate_to_storage(t1, storage));
            HPX_TEST_EQ(hpx::naming::invalid_id, t2.get_id());
        }
        catch (hpx::exception const&) {
            return false;
        }

        HPX_TEST_EQ(storage.size_sync(), std::size_t(1));

        // make sure all local references go out of scope if t == unmanaged
    }

    HPX_TEST_EQ(storage.size_sync(), std::size_t(1));

    {
        test_client t1(hpx::components::migrate_from_storage<test_server>(
            oldid, target));

        // the id of the newly resurrected object should be the same as the old id
        HPX_TEST_EQ(oldid, t1.get_id());
        HPX_TEST_EQ(t1.get_data(), 42);

        // the new object should now live on the target locality
        HPX_TEST_EQ(t1.call(), target);

        HPX_TEST_EQ(storage.size_sync(), std::size_t(0));
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////
bool test_migrate_busy_component_to_storage(hpx::id_type const& source,
    hpx::components::component_storage storage, hpx::id_type::management_type t)
{
    hpx::id_type oldid;

    {
        // create component on given locality
        test_client t1 = hpx::new_<test_client>(source, 42);
        HPX_TEST_NEQ(hpx::naming::invalid_id, t1.get_id());

        // the new object should live on the source locality
        HPX_TEST_EQ(t1.call(), source);
        HPX_TEST_EQ(t1.get_data(), 42);

        // remember the original id for later resurrection
        oldid = hpx::id_type(t1.get_id().get_gid(), t);

        // add some concurrent busy work
        hpx::future<void> busy_work = t1.busy_work();

        try {
            // migrate of t1 to the target storage
            test_client t2(hpx::components::migrate_to_storage(t1, storage));
            HPX_TEST_EQ(hpx::naming::invalid_id, t2.get_id());
        }
        catch (hpx::exception const&) {
            return false;
        }

        // the busy work should be finished by now, wait anyways
        busy_work.wait();

        HPX_TEST_EQ(storage.size_sync(), std::size_t(1));

        // make sure all local references go out of scope if t == unmanaged
    }

    HPX_TEST_EQ(storage.size_sync(), std::size_t(1));

    {
        test_client t1(hpx::components::migrate_from_storage<test_server>(oldid));

        // the id of the newly resurrected object should be the same as the old id
        HPX_TEST_EQ(oldid, t1.get_id());

        // the new object should live on the (original) source locality
        HPX_TEST_EQ(t1.call(), source);
        HPX_TEST_EQ(t1.get_data(), 42);

        HPX_TEST_EQ(storage.size_sync(), std::size_t(0));
    }

    return true;
}

bool test_migrate_busy_component_to_storage(hpx::id_type const& source,
    hpx::id_type const& target, hpx::components::component_storage storage,
    hpx::id_type::management_type t)
{
    hpx::id_type oldid;

    {
        // create component on given locality
        test_client t1 = hpx::new_<test_client>(source, 42);
        HPX_TEST_NEQ(hpx::naming::invalid_id, t1.get_id());

        // the new object should live on the source locality
        HPX_TEST_EQ(t1.call(), source);
        HPX_TEST_EQ(t1.get_data(), 42);

        // remember the original id for later resurrection
        oldid = hpx::id_type(t1.get_id().get_gid(), t);

        // add some concurrent busy work
        hpx::future<void> busy_work = t1.busy_work();

        try {
            // migrate of t1 to the target storage
            test_client t2(hpx::components::migrate_to_storage(t1, storage));
            HPX_TEST_EQ(hpx::naming::invalid_id, t2.get_id());
        }
        catch (hpx::exception const&) {
            return false;
        }

        // the busy work should be finished by now, wait anyways
        busy_work.wait();

        HPX_TEST_EQ(storage.size_sync(), std::size_t(1));

        // make sure all local references go out of scope if t == unmanaged
    }

    HPX_TEST_EQ(storage.size_sync(), std::size_t(1));

    {
        test_client t1(hpx::components::migrate_from_storage<test_server>(
            oldid, target));

        // the id of the newly resurrected object should be the same as the old id
        HPX_TEST_EQ(oldid, t1.get_id());
        HPX_TEST_EQ(t1.get_data(), 42);

        // the new object should now live on the target locality
        HPX_TEST_EQ(t1.call(), target);

        HPX_TEST_EQ(storage.size_sync(), std::size_t(0));
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////
// transparent resurrection is not implemented yet
// bool test_migrate_component_from_storage(hpx::id_type const& source,
//     hpx::components::component_storage storage)
// {
//     hpx::id_type oldid;
//
//     {
//         // create component on given locality
//         test_client t1 = hpx::new_<test_client>(source, 42);
//         HPX_TEST_NEQ(hpx::naming::invalid_id, t1.get_id());
//
//         // the new object should live on the source locality
//         HPX_TEST_EQ(t1.call(), source);
//         HPX_TEST_EQ(t1.get_data(), 42);
//
//         // remember the original id for later action invocation
//         oldid = t1.get_id();
//
//         try {
//             // migrate of t1 to the target storage
//             test_client t2(hpx::components::migrate_to_storage(t1, storage));
//             HPX_TEST_EQ(hpx::naming::invalid_id, t2.get_id());
//         }
//         catch (hpx::exception const&) {
//             return false;
//         }
//
//         HPX_TEST_EQ(storage.size_sync(), std::size_t(1));
//     }
//
//     HPX_TEST_EQ(storage.size_sync(), std::size_t(1));
//
//     // The object is stored in the storage now, apply an action which should
//     // transparently bring it back.
//     {
//         test_client t1;
//         t1.reset(oldid);
//
//         // transparently resurrect object on the original source locality
//         HPX_TEST_EQ(t1.call(), source);
//         HPX_TEST_EQ(t1.get_data(), 42);
//
//         HPX_TEST_EQ(storage.size_sync(), std::size_t(0));
//     }
//
//     return true;
// }

///////////////////////////////////////////////////////////////////////////////
void test_storage(hpx::id_type const& here, hpx::id_type const& there)
{
    // create a new storage instance
    hpx::components::component_storage storage(here);
    HPX_TEST_NEQ(hpx::naming::invalid_id, storage.get_id());

    {
        HPX_TEST(test_migrate_component_to_storage(here, storage,
            hpx::id_type::unmanaged));
        HPX_TEST(test_migrate_component_to_storage(here, storage,
            hpx::id_type::managed));

        HPX_TEST(test_migrate_component_to_storage(there, storage,
            hpx::id_type::unmanaged));
        HPX_TEST(test_migrate_component_to_storage(there, storage,
            hpx::id_type::managed));
    }
    {
        HPX_TEST(test_migrate_component_to_storage(here, there, storage,
            hpx::id_type::unmanaged));
        HPX_TEST(test_migrate_component_to_storage(here, there, storage,
            hpx::id_type::managed));

        HPX_TEST(test_migrate_component_to_storage(there, here, storage,
            hpx::id_type::unmanaged));
        HPX_TEST(test_migrate_component_to_storage(there, here, storage,
            hpx::id_type::managed));
    }
    {
        HPX_TEST(test_migrate_busy_component_to_storage(here, storage,
            hpx::id_type::unmanaged));
        HPX_TEST(test_migrate_busy_component_to_storage(here, storage,
            hpx::id_type::managed));

        HPX_TEST(test_migrate_busy_component_to_storage(there, storage,
            hpx::id_type::unmanaged));
        HPX_TEST(test_migrate_busy_component_to_storage(there, storage,
            hpx::id_type::managed));
    }
    {
        HPX_TEST(test_migrate_busy_component_to_storage(here, there, storage,
            hpx::id_type::unmanaged));
        HPX_TEST(test_migrate_busy_component_to_storage(here, there, storage,
            hpx::id_type::managed));

        HPX_TEST(test_migrate_busy_component_to_storage(there, here, storage,
            hpx::id_type::unmanaged));
        HPX_TEST(test_migrate_busy_component_to_storage(there, here, storage,
            hpx::id_type::managed));
    }

// transparent resurrection is not implemented yet
//     HPX_TEST(test_migrate_component_from_storage(here, storage));
}

int main()
{
    test_storage(hpx::find_here(), hpx::find_here());

    for (hpx::id_type const& id: hpx::find_remote_localities())
    {
        test_storage(hpx::find_here(), id);
        test_storage(id, hpx::find_here());
        test_storage(id, id);
    }

    return hpx::util::report_errors();
}


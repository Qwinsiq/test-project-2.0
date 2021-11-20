#pragma once
#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/Connection.hpp>
#include <sysrepo-cpp/Subscription.hpp>


class NetConfAgent
{
    private:
    std::unique_ptr<sysrepo::Connection>  connection;
    public:
    NetConfAgent();
    void subscribeForModelChanges();
};
#pragma once
#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/Connection.hpp>
#include <sysrepo-cpp/Subscription.hpp>


class NetConfAgent
{
    private:
    std::unique_ptr<sysrepo::Session> session;
    std::unique_ptr<sysrepo::Connection>  connection;
    std::unique_ptr<sysrepo::Subscription> subscription;
    public:
    NetConfAgent();
    bool subscribeForModelChanges();
};
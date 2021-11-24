#pragma once
#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/Connection.hpp>
#include <sysrepo-cpp/Subscription.hpp>
#include <libyang-cpp/DataNode.hpp>
#include <optional>

class NetConfAgent
{
    private:
    sysrepo::Connection  connection;
    sysrepo::Session session;
    std::optional<sysrepo::Subscription> subscription;
    public:
    NetConfAgent();
    void subscribeForModelChanges();
    bool fetchData(std::string path, std::string& str);
   };
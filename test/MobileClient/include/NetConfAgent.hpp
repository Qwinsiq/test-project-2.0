#pragma once
#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/Connection.hpp>
#include <sysrepo-cpp/Subscription.hpp>
#include <libyang-cpp/DataNode.hpp>
#include <optional>

class NetConfAgent    
{
    public:
    NetConfAgent();
    void subscribeForModelChanges(std::string path);
    bool fetchData(std::string path, std::string& str);
    bool registerOperData(std::string& path, std::string value);
    void changeData(const std::string path, std::string value);
   private:
    sysrepo::Connection  _connection;
    sysrepo::Session _session;
    std::optional<sysrepo::Subscription> _subscription;
};
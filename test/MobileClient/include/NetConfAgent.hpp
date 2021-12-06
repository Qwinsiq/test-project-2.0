#pragma once
#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/Connection.hpp>
#include <sysrepo-cpp/Subscription.hpp>
#include <libyang-cpp/DataNode.hpp>
#include <optional>
#include "constants.hpp"

class MobileClient;
class NetConfAgent    
{
    public:
    NetConfAgent();
    void subscribeForModelChanges(std::string path, MobileClient& client);
    bool fetchData(std::string path, std::string& str);
    bool registerOperData(std::string& path, std::string value);
    void changeData(const std::string path, std::string value);
    void deleteData(const std::string path);
   private:
    sysrepo::Connection  _connection;
    sysrepo::Session _session;
    std::optional<sysrepo::Subscription> _subscription;
};
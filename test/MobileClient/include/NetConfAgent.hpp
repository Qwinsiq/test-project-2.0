#pragma once
#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/Connection.hpp>
#include <sysrepo-cpp/Subscription.hpp>
#include <libyang-cpp/DataNode.hpp>
#include <optional>
#include "constants.hpp"
namespace comutator{ 
class MobileClient;
class NetConfAgent    
{
    public:
    NetConfAgent();
    /*
    @brief Makes subscription on concrete path on running Data
    @param modelName- name of model, where our subscription item is locate
    @param path- path to our item
    @param client- object of MobileClient that call metod subscribeForModelChange
    @return true- if subscription is succesfel created
            false-if subscription is not created
    */
    bool subscribeForModelChanges(std::string modelName, std::string path, MobileClient& client);

    /*
    @brief copy Data, that locate by path into string
    @param  path- path to coping Data
    @param str- string, which will be recorded Data
    @return true-if Data succesful coped,
            false-if any Data wasn't coped ib any Datastore(Running,Operational)
    */
    bool fetchData(std::string path, std::string& str);

    /*
    @brief Makes subscription on concrete path on operational Data
    @param modelName- name of model, where our subscription item is locate
    @param path- path to our item
    @param client- object of MobileClient that call metod registerOperData
    @return true- if subscription is succesfel created
            false-if subscription is not created
    */
    bool registerOperData(std::string modelName, std::string path, MobileClient& client);

    /*
    @brief change Data in a specific path
    @param path- path in which is located changing Data
    @param value- new Data that have to be recorded
    */
    void changeData(const std::string path, std::string value);

    /*
    @brief delete Data in specific path
    @param path- path in which is located Data needed to delete
    */
    void deleteData(const std::string path);

   private:
    sysrepo::Connection  _connection;
    sysrepo::Session _session;
    std::optional<sysrepo::Subscription> _subscription;
    std::optional<sysrepo::Subscription> _operSub;
};
}
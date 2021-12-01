#include "/home/qwinsiq/Desktop/test_project/test/MobileClient/include/NetConfAgent.hpp"
#include <iostream>
#include <optional>
#include <string>
#include <atomic>

NetConfAgent::NetConfAgent() : _connection(), _session(_connection.sessionStart())
{
    
    //_session.switchDatastore(sysrepo::Datastore::Operational);
    //_session.copyConfig(sysrepo::Datastore::Running, "commutator");
}
bool NetConfAgent::fetchData(std::string path, std::string &str)
{
    auto data = _session.getData(path.c_str());
    if (data != std::nullopt)
    {
        str = data->findPath(path.c_str()).value().asTerm().valueStr();
        std::cout << str;
        return true;
    }
    else
    {
        std::cout << "Data is empty";
        return false;
    }
}
void NetConfAgent::changeData(const std::string path, std::string value)
{
    const char *s = path.c_str();
    const char *r = value.c_str();
    _session.setItem(s, r);
    _session.applyChanges();
}
void NetConfAgent::subscribeForModelChanges(std::string path)
{
    const char *s = path.c_str();
    sysrepo::ModuleChangeCb moduleChangeCb = [](sysrepo::Session _session, auto, auto, auto, auto, auto) -> sysrepo::ErrorCode
    {
        std::cout << " change Data form callback in subscribeForModelChange\n";
        return sysrepo::ErrorCode::Ok;
    };
    _subscription = _session.onModuleChange("commutator", moduleChangeCb, s, 0, sysrepo::SubscribeOptions::DoneOnly);
}
bool NetConfAgent::registerOperData(std::string &path, std::string value)
{
    std::optional<libyang::DataNode> toSet;
    sysrepo::ErrorCode retCode;
    sysrepo::OperGetItemsCb operGetCb = [&](sysrepo::Session, auto, auto, auto, auto, auto, std::optional<libyang::DataNode> &parent)
    {
        parent = toSet;
        std::cout << "call back in operData is called\n";

        return retCode;
    };
    //_session.switchDatastore(sysrepo::Datastore::Operational);
    toSet =_session.getContext().newPath(path.c_str(), value.c_str());
    _subscription = _session.onOperGetItems("commutator", operGetCb, path.c_str());
   // _session.switchDatastore(sysrepo::Datastore::Running);
   // _session.setItem(path.c_str(),value.c_str());
    std::cout << " metod is called \n";
    return true;
}
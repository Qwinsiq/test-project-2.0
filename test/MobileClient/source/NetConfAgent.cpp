#include "/home/qwinsiq/Desktop/test_project/test/MobileClient/include/NetConfAgent.hpp"
#include <iostream>
#include <optional>
#include <string>

NetConfAgent::NetConfAgent() : _connection(), _session(_connection.sessionStart())
{
    _session.copyConfig(sysrepo::Datastore::Running, "commutator");
}
bool NetConfAgent::fetchData(std::string path, std::string &str)
{
    const char *s = path.c_str();
    auto data = _session.getData(s);
    str = data->findPath(s).value().asTerm().valueStr();
    std::cout << str;
    if (data != !std::nullopt)
        return true;
    else
    {
        std::cout << "Data is empty";
        return false;
    }
}
void NetConfAgent::setData(const std::string path, std::string value)
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
        return sysrepo::ErrorCode::Ok;
    };
    _subscription = _session.onModuleChange("commutator", moduleChangeCb, s, 0, sysrepo::SubscribeOptions::DoneOnly);
}
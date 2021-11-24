#include "/home/qwinsiq/Desktop/test_project/test/MobileClient/include/NetConfAgent.hpp"
#include <iostream>
#include <optional>
#include <string>

NetConfAgent::NetConfAgent():connection(),session(connection.sessionStart())
{ 
    session.copyConfig(sysrepo::Datastore::Running, "commutator");
}
bool NetConfAgent::fetchData(std::string path,std::string& str )
{
    const char* s=path.c_str();
    auto data=session.getData(s);
    str=data->findPath(s).value().asTerm().valueStr();
    std::cout<<str;
    if(!data)
    return true;
    else return false;
}
void NetConfAgent::subscribeForModelChanges()
{
        int called={0};
    sysrepo::ModuleChangeCb moduleChangeCb = [&called] (sysrepo::Session session, auto, auto, auto, auto, auto) -> sysrepo::ErrorCode {
            called++;
            std::cout<<"function called "<<called<<std::endl;
            return sysrepo::ErrorCode::Ok;
        };
   subscription= session.onModuleChange("commutator", moduleChangeCb, nullptr,0,sysrepo::SubscribeOptions::DoneOnly);
   
}
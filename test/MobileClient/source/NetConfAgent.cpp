#include "/home/qwinsiq/Desktop/test_project/test/MobileClient/include/NetConfAgent.hpp"
#include <iostream>
#include <optional>

NetConfAgent::NetConfAgent():connection(),session(connection.sessionStart())
{ 
    session.copyConfig(sysrepo::Datastore::Startup, "commutator");
}
void NetConfAgent::fetchData(const char* path)
{
std::cout<<session.getData(path);
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
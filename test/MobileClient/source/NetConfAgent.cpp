#include "/home/qwinsiq/Desktop/test_project/test/MobileClient/include/NetConfAgent.hpp"
#include <iostream>
#include <optional>
#include <string>

NetConfAgent::NetConfAgent():connection(),session(connection.sessionStart())
{ 
    session.copyConfig(sysrepo::Datastore::Startup, "commutator");
}
bool NetConfAgent::fetchData(std::string path,std::string& str )
{
    const char* s=path.c_str();
    auto r=session.getData(s);
    str=r.printStr(0,0);
    std::cout<<str;
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
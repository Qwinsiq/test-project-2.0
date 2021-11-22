#include "/home/qwinsiq/Desktop/test_project/test/MobileClient/include/NetConfAgent.hpp"
#include <iostream>

NetConfAgent::NetConfAgent()
{ 
}

void NetConfAgent::subscribeForModelChanges()
{
    connection=std::make_unique<sysrepo::Connection>();
    auto  session= connection->sessionStart();
    session.copyConfig(sysrepo::Datastore::Startup, "test_module");
    int called={0};
    sysrepo::ModuleChangeCb moduleChangeCb = [&called] (auto, auto, auto, auto, auto, auto) -> sysrepo::ErrorCode {
            called++;
            return sysrepo::ErrorCode::Ok;
        };
    auto subscription=session.onModuleChange("test_module", moduleChangeCb);
    subscription.onModuleChange("test_module",moduleChangeCb);
    session.setItem("/test_module:leafInt32", "123");
    session.applyChanges();
    std::cout<<"function called "<<called<<std::endl;
    }
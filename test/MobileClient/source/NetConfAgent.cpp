#include "/home/qwinsiq/Desktop/test_project/test/MobileClient/include/NetConfAgent.hpp"
#include <iostream>

NetConfAgent::NetConfAgent()
{ 
}

bool NetConfAgent::subscribeForModelChanges()
{
    connection=std::make_unique<sysrepo::Connection>();
    std::unique_ptr<sysrepo::Session> q (new sysrepo::Session(connection->sessionStart()));
    session=std::move(q);
    session->copyConfig(sysrepo::Datastore::Startup, "test_module");
    int called={0};
    sysrepo::ModuleChangeCb moduleChangeCb = [&called] (auto, auto, auto, auto, auto, auto) -> sysrepo::ErrorCode {
            called++;
            return sysrepo::ErrorCode::Ok;
        };
    
}
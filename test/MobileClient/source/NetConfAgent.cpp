#include "/home/qwinsiq/Desktop/test_project/test/MobileClient/include/NetConfAgent.hpp"
#include <iostream>

NetConfAgent::NetConfAgent()
{ 
}

void NetConfAgent::subscribeForModelChanges()
{
    connection=std::make_unique<sysrepo::Connection>();
    auto  session= connection->sessionStart();
    int called={0};
    sysrepo::ModuleChangeCb moduleChangeCb = [&called] (auto, auto, auto, auto, auto, auto) -> sysrepo::ErrorCode {
            called++;
            return sysrepo::ErrorCode::Ok;
        };
    auto subscription=session.onModuleChange("testmodel", moduleChangeCb);
    subscription.onModuleChange("testmodel",moduleChangeCb);
    std::cout<<"function called "<<called<<std::endl;
    }
#include "NetConfAgent.hpp"
#include <iostream>

NetConfAgent::NetConfAgent()
{ 
}

bool NetConfAgent::subscribeForModelChanges()
{
    connection=std::make_unique<sysrepo::Connection>();
    std::unique_ptr<sysrepo::Session> q (new sysrepo::Session(connection->sessionStart()));
    session=std::move(q);
}
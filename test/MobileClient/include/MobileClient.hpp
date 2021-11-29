#pragma once
#include "NetConfAgent.hpp"
#include <string>
enum class state
{
 idle,
 busy,
 active
};
 class MobileClient
 {
     public:
     MobileClient();
     bool Register(std::string number);
     void setName(std::string name);
     ~MobileClient();
     private:
     std::string _name;
     std::string _number;
     std::string _incomingNumber;
     state _state;
     std::unique_ptr<NetConfAgent> _netConfAgent;
 };

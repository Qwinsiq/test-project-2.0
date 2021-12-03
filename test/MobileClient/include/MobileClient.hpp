#pragma once
#include "NetConfAgent.hpp"
#include <string>
#include "constants.hpp"
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
     bool call(std::string number);
     void answer();
     void handleModuleChange(std::string path, std::string value);
     const std::string makePath(std::string number, std::string leaf);
     private:
     std::string _name;
     std::string _number;
     std::string _incomingNumber;
     state _state;
     
     std::unique_ptr<NetConfAgent> _netConfAgent;
 };

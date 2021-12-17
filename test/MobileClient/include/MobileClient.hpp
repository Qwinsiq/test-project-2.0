#pragma once
#include "NetConfAgent.hpp"
#include <string>

namespace comutator{ 
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

     /*
     @brief registers abonent with specific number
     @param number- number of registered abonent
     @return true- abonent succesful created
             false-abonent hasn't been created
     */

    MobileClient(std::unique_ptr<INetConfAgent> NetConf);

     bool Register(std::string number);

     /*
     @brief set Name of abonent, must be used before registration of number
     @param name- Name that need to set 
     */
     void setName(std::string name);

     /*
     @brief call abonents
     @param number- abonents number that neeed to call
     @return true- call is succesful
            false- call is nit succesful
     */
     bool call(std::string number);

     /*
     @brief unregisters abonent
     @return true-unregistration is succesfull
            false-unregistration is not possible
     */
     bool unregister();

     /*
     @brief answers thr incoming call
     */
     bool answer();

     /*
     @brief ends teh call
     */
     void callEnd();
     
     /*
     @brief rejects incoming call
     */
     void reject();
     
     /*
     @brief moted is called in SubscribeForMadelChange and reactes for changes on specific subscribs
     @param path- path where changes were
     @param value - value that was set
     */
     void handleModuleChange(std::string path, std::string value);

     /*
     @brief gets seted Name
     @returns string that contains Name of abonent
     */
     std::string getName();

     private:
     
     const std::string makePath(std::string number, std::string leaf);
     
     std::string _name;
     std::string _number;
     std::string _incomingNumber;
     state _state;
     std::string _out;
    
     std::unique_ptr<INetConfAgent> _netConfAgent;
 };
}
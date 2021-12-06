#include "MobileClient.hpp"
#include <iostream>

MobileClient::MobileClient()
{
    _netConfAgent = std::make_unique<NetConfAgent>();
}
const std::string MobileClient::makePath(std::string number, const std::string path)
{
    std::string str = path;
    str.replace(str.find("key"), 3, number);
    return str;
}
void MobileClient::setName(std::string name)
{
    _name = name;
}
bool MobileClient::Register(std::string number)
{
    _number = number;
    std::string temp;
    if (_netConfAgent->fetchData(makePath(number, numberPath), temp))

    {
        std::cout << " Client with this number already exists, try another number \n";
        return false;
    }
    else
    {
        _netConfAgent->changeData(makePath(_number, numberPath), _number);
        _netConfAgent->subscribeForModelChanges(makePath(_number, subscriberPath), *this);
        return true;
    }
}
bool MobileClient::call(std::string number)
{
    std::string tempStr;
    if (_netConfAgent->fetchData(makePath(_number, numberPath), tempStr))
    {
        if (_netConfAgent->fetchData(makePath(number, numberPath), tempStr))
        {
            if (_netConfAgent->fetchData(makePath(number, statePath), tempStr))
            {
                if (tempStr == "idle")
                {
                    _netConfAgent->changeData(makePath(number, statePath), "active");
                    _netConfAgent->changeData(makePath(_number, statePath), "active");
                    _netConfAgent->changeData(makePath(number, incomingnumberPath), _number);
                    return true;
                }
                else
                    std::cout << "Number " << number << " is not free " << std::endl;
            }
            else
                std::cout << "State of callNumber is not defined\n";
        }
        else
            std::cout << "CallNumber is not exist\n";
    }
    else
        std::cout << "Caller is not exist\n";
    return false;
}
void MobileClient::handleModuleChange(std::string path, std::string value)
{
    if (path == makePath(_number, incomingnumberPath))
    {
        std::cout << ">> incoming call from " << value << std::endl;
    }
    else if (path == makePath(_number, statePath) && value == "buzy")
    {
        std::cout << ">> The call is in progress \n";
    }
    else if (path == makePath(_number, statePath) && value == "idle")
    {
        std::cout << ">> The call is ended \n";
    }
}
void MobileClient::answer()
{
    std::string temp1, temp2;
    if (_netConfAgent->fetchData(makePath(_number, statePath), temp1) &&
        _netConfAgent->fetchData(makePath(_incomingNumber, statePath), temp2) &&
        temp1 == "active" && temp2 == "active")
    {
        _netConfAgent->changeData(makePath(_number, statePath), "busy");
        _netConfAgent->changeData(makePath(_incomingNumber, statePath), "busy");
    }
}
void MobileClient::callEnd()
{
    std::string temp1, temp2;
    if (_netConfAgent->fetchData(makePath(_number, statePath), temp1) &&
        _netConfAgent->fetchData(makePath(_incomingNumber, statePath), temp2) &&
        temp1 == "busy" && temp2 == "busy")
    {
        _netConfAgent->changeData(makePath(_number, statePath), "idle");
        _netConfAgent->changeData(makePath(_incomingNumber, statePath), "idle");
        _netConfAgent->changeData(makePath(_number, incomingnumberPath), nullptr);
    }
}
void MobileClient::reject()
{
    std::string temp1, temp2;
    if (_netConfAgent->fetchData(makePath(_number, statePath), temp1) &&
        _netConfAgent->fetchData(makePath(_incomingNumber, statePath), temp2) &&
        temp1 == "active" && temp2 == "active")
    {
        _netConfAgent->changeData(makePath(_number, statePath), "idle");
        _netConfAgent->changeData(makePath(_incomingNumber, statePath), "idle");
        _netConfAgent->changeData(makePath(_number, incomingnumberPath), nullptr);
    }
}
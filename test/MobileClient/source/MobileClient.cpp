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
                    _incomingNumber = number;
                    _state = state::outgoing;
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
    if (path == makePath(_number, statePath))
    {
        if (value == "busy")
        {
            _state = state::busy;
            std::cout << ">> The call is in progress " << std::endl;
        }

        else if (value == "idle")
        {
            _state = state::idle;
            _incomingNumber.erase();
            std::cout << ">> The call is ended " << std::endl;
        }
    }
    else if (path == makePath(_number, incomingnumberPath) && _state != state::idle && _state != state::busy)
    {
        _incomingNumber = value;
        std::cout << ">> incoming call from " << value << std::endl;
    }
}

void MobileClient::answer()
{
    std::string temp1, temp2;
    if (_netConfAgent->fetchData(makePath(_number, statePath), temp1) ==
            _netConfAgent->fetchData(makePath(_incomingNumber, statePath), temp2) &&
        temp1 == "active" && _state != state::outgoing)
    {
        _netConfAgent->changeData(makePath(_number, statePath), "busy");
        _netConfAgent->changeData(makePath(_incomingNumber, statePath), "busy");
    }
}
void MobileClient::callEnd()
{
    std::string temp1, temp2;
    if (_netConfAgent->fetchData(makePath(_number, statePath), temp1) ==
            _netConfAgent->fetchData(makePath(_incomingNumber, statePath), temp2) &&
        temp2 == "busy")
    {
        _netConfAgent->changeData(makePath(_incomingNumber, statePath), "idle");
        _netConfAgent->changeData(makePath(_number, statePath), "idle");

        //_netConfAgent->deleteData(makePath(_incomingNumber, incomingnumberPath));
        _netConfAgent->deleteData(makePath(_number, incomingnumberPath));
    }
}
void MobileClient::reject()
{
    std::string temp1, temp2;
    if (_netConfAgent->fetchData(makePath(_number, statePath), temp1) ==
            _netConfAgent->fetchData(makePath(_incomingNumber, statePath), temp2) &&
        temp2 == "active" && _state != state::outgoing)
    {
        _netConfAgent->changeData(makePath(_incomingNumber, statePath), "idle");
        _netConfAgent->changeData(makePath(_number, statePath), "idle");
        
        _netConfAgent->deleteData(makePath(_number, incomingnumberPath));
    }
}
#include "MobileClient.hpp"
#include <iostream>
#include "constants.hpp"

namespace comutator
{
    MobileClient::MobileClient() : MobileClient(std::make_unique<NetConfAgent>())
    {
    }

    MobileClient::MobileClient(std::unique_ptr<INetConfAgent> NetConf) : _netConfAgent{std::move(NetConf)}
    {
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
            _netConfAgent->subscribeForModelChanges(moduleNameCom, makePath(_number, subscriberPath), *this);
            _netConfAgent->registerOperData(moduleNameCom, makePath(_number, userNamePath), *this);

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
                        _out = number;
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

    std::string MobileClient::getName()
    {
        return _name;
    }

    void MobileClient::handleModuleChange(std::string path, std::string value)
    {
        if (path == makePath(_number, statePath))
        {
            if (value == "busy")
            {
                _state = state::busy;
                std::time(&_startTime);
                std::cout << ">> The call is in progress " << std::endl;
            }

            else if (value == "idle")
            {
                _state = state::idle;
                _out.erase();
                _incomingNumber.erase();
                std::cout << ">> The call is ended " << std::endl;
            }
            else if (value == "active")
            {
                _state = state::active;
            }
        }
        else if (path == makePath(_number, incomingnumberPath))
        {
            if (_state == state::active)
            {
                _incomingNumber = value;
                std::string str;
                if (_netConfAgent->fetchData(makePath(value, userNamePath), str))
                    std::cout << ">> incoming call from " << value << " " << str << std::endl;
            }
        }
    }

    bool MobileClient::answer()
    {
        if (_state == state::active && _out.empty())
        {
            _netConfAgent->changeData(makePath(_number, statePath), "busy");
            _netConfAgent->changeData(makePath(_incomingNumber, statePath), "busy");
            std::map<std::string, std::string> mp;
            mp["startTime"] = std::to_string(_startTime);
            mp["abonentA"] = _number;
            mp["abonentB"] = _incomingNumber;
            _netConfAgent->notifySysrepo(mp);
            return true;
        }
        else
            return false;
    }
    bool MobileClient::callEnd()
    {
        if (_out.empty())
        {
            if (_state == state::busy)
            { 
                std::map<std::string, std::string> mp;
                mp["startTime"] = std::ctime(&_startTime);
                mp["abonentA"] = _number;
                mp["abonentB"] = _incomingNumber;
                std::time_t endT;
                std::time(&endT);
                mp["duration"]=std::to_string((int)(std::difftime(endT,_startTime))/60);
                _netConfAgent->notifySysrepo(mp);
                _netConfAgent->deleteData(makePath(_number, incomingnumberPath));
                _netConfAgent->changeData(makePath(_incomingNumber, statePath), "idle");
                _netConfAgent->changeData(makePath(_number, statePath), "idle");
               
                return true;
            }
        }
        else if (!_out.empty())
        {
            if (_state == state::busy)

            {
                std::map<std::string, std::string> mp;
                mp["startTime"] = std::to_string(_startTime);
                mp["abonentA"] = _number;
                mp["abonentB"] = _out;
                std::time_t endT;
                std::time(&endT);
                mp["duration"]=std::to_string((int)(std::difftime(endT,_startTime))/60);
                _netConfAgent->notifySysrepo(mp);
                _netConfAgent->deleteData(makePath(_out, incomingnumberPath));
                _netConfAgent->changeData(makePath(_out, statePath), "idle");
                _netConfAgent->changeData(makePath(_number, statePath), "idle");
                
                return true;
            }
        }
        return false;
    }
    bool MobileClient::reject()
    {

        if (_state == state::active && _out.empty())
        {
            _netConfAgent->deleteData(makePath(_number, incomingnumberPath));
            _netConfAgent->changeData(makePath(_incomingNumber, statePath), "idle");
            _netConfAgent->changeData(makePath(_number, statePath), "idle");
            return true;
        }
        else
            return false;
    }
    bool MobileClient::unregister()
    {
        if (_incomingNumber.empty() && _out.empty())
        {
            _netConfAgent->deleteData(makePath(_number, subscriberPath));
            std::cout << "abonent is unregistered \n";
            return true;
        }
        else
        {
            std::cout << " abonent cant't be deleted, he has active call\n";
            return false;
        }
    }
    MobileClient::~MobileClient()
    {
        if (!_number.empty())
        {
            if (_incomingNumber.empty() && _out.empty())
            {
                _netConfAgent->deleteData(makePath(_number, subscriberPath));
            }
            else
            {
                if (!_out.empty())
                {
                    if (_state == state::busy)
                    {
                        callEnd();
                    }
                    if (_state == state::active)
                    {
                        _netConfAgent->deleteData(makePath(_out, incomingnumberPath));
                        _netConfAgent->changeData(makePath(_out, statePath), "idle");
                    }
                }
                else if (!_incomingNumber.empty())
                {
                    if (_state == state::busy)
                    {
                        callEnd();
                    }
                    if (_state == state::active)
                    {
                        reject();
                    }
                }
                _netConfAgent->deleteData(makePath(_number, subscriberPath));
            }
        }
    }
}
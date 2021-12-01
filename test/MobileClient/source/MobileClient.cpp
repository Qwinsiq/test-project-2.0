#include </home/qwinsiq/Desktop/test_project/test/MobileClient/include/MobileClient.hpp>
#include <iostream>
MobileClient::MobileClient()
{
    _netConfAgent = std::make_unique<NetConfAgent>();
}
const std::string MobileClient::makePath(std::string number, const std::string path)
{
    std::string str = path;
    str.replace(str.find("key"), str.rfind("key"), number);
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
        _netConfAgent->subscribeForModelChanges(makePath(_number, numberPath));
        return true;
    }
}
bool MobileClient::call(std::string name)
{
    std::string tempStr;
    if (_netConfAgent->fetchData(makePath(_number, numberPath), tempStr))
    {
        if (_netConfAgent->fetchData(makePath(name, numberPath), tempStr))
        {
            if (_netConfAgent->fetchData(makePath(name, incomingnumberPath), tempStr))
            {
                if (tempStr == "idle")
                {
                    _netConfAgent->changeData(makePath(name, statePath), "active");
                    _netConfAgent->changeData(makePath(_number, statePath), "active");
                    _netConfAgent->changeData(makePath(name, incomingnumberPath), _number);
                    return true;
                }
                else
                    std::cout << "Number is " << tempStr << std::endl;
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

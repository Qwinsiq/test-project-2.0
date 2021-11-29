#include </home/qwinsiq/Desktop/test_project/test/MobileClient/include/MobileClient.hpp>
#include <iostream>
MobileClient::MobileClient()
{
 _netConfAgent=std::make_unique<NetConfAgent>();
}
void MobileClient::setName(std::string name)
{
 _name=name;
}
bool MobileClient::Register(std::string number)
{
    _number=number;
    std::string temp;
    std::string path="/commutator:subscribers/subscriber[number='"+number+"']/number";
_netConfAgent->fetchData(path,temp);
if ( temp==_number)
{
    std::cout<<" Client with this number already exists, try another number \n";
    return false;
}
else
{
    _netConfAgent->changeData(path,_number);
    return true;
}
}
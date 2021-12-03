#include <iostream>
#include <string>
#include "MobileClient.hpp"
// at this moment i have done all function as void for the test
void Register(std::string str)
{
    std::cout << "The client " << str << " is registraited" << std::endl;
}
void unregister()
{
    std::cout << " function unregicter is called"<<std::endl;;
}
void call(std::string str)
{
    std::cout << "calling client " << str << std::endl;
}
void callEnd()
{
    std::cout << "function callEnd is called" << std::endl;
}
void answer()
{
    std::cout << "function answer is called" << std::endl;
}
void reject()
{
    std::cout << "function reject is called" << std::endl;
}
void exit()
{
    std::cout << "function exit is called" << std::endl;
}
void setName(std::string str)
{
    std::cout << "name " << str << " is setted" << std::endl;
    
}
int main()
{
    std::string str, command;
    bool cicle=true;
   // NetConfAgent r;
      MobileClient m;
     std::string str1, str2, str3, str7;
   // str1="/commutator:subscribers/subscriber[number='133']/incomingNumber";
   // getline(std::cin,str2);
   // m.Register(str2);
    //r.subscribeForModelChanges(str1);
   //   r.changeData(str1,str2);
  //  if(!r.fetchData(str1,str3))
   // std::cout<<str3;
   // std::string str4="/commutator:subscribers/subscriber[number='133']/userName";
    //str2="mike";
   // bool q=r.registerOperData(str4, str2);
   // if(!r.fetchData(str4,str7))
    //std::cout<<str7;
    
    
         while (cicle)
    {

        getline(std::cin,str);
            if(str.find(' ')==std::string::npos)
        {
            if (str == "unregister")
                unregister();
            else if (str == "callEnd")
                callEnd();
            else if (str == "reject")
                reject();
            else if (str == "answer")
                m.answer();
            else if (str == "exit")
                exit();
                else if(str=="end") cicle=false;
            else
                std::cout << "wrong command" << std::endl;
        }
        else if (str.find(' ')!=std::string::npos)
        {
            std::size_t start_pos=str.find_first_of(' ');
            command=str.substr(0,start_pos);
            str=str.substr(start_pos+1,str.length()-start_pos);
            if(command=="register") m.Register(str);
            else if(command=="call") m.call(str);
            else if(command=="setName") m.setName(str);
            else std::cout<<"dont write\n";
        }
        else std::cout<<" dont work\n";
    } 
    return 0;
}
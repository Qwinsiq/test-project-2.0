#include <iostream>
#include <string>
#include "MobileClient.hpp"

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
         comutator::MobileClient m;
         while (cicle)
    {

        getline(std::cin,str);
            if(str.find(' ')==std::string::npos)
        {
            if (str == "unregister") 
                m.unregister();
            else if (str == "callEnd")
                m.callEnd();
            else if (str == "reject")
                m.reject();
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
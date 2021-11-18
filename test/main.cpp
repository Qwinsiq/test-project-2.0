#include <iostream>
#include <string>
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
    std::cout << "calling client" << str << std::endl;
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
    int count_of_world;
    bool cicle=true;
    while (cicle)
    {
        std::cin.ignore();
        getline(std::cin,str);
        count_of_world = 1;
        for (int i = 1; i < str.size() - 1; i++)
        {
            if (str[i - 1] != ' ' && str[i] == ' ' || str[i + 1] == '\0')
            {
                count_of_world++;
            }
        }
        if (count_of_world == 1)
        {
            if (str == "unregister")
                unregister();
            else if (str == "callEnd")
                callEnd();
            else if (str == "reject")
                reject();
            else if (str == "answer")
                answer();
            else if (str == "exit")
                exit();
                else if(str=="end") cicle=false;
            else
                std::cout << "wrong command" << std::endl;
        }
        else if (count_of_world > 1)
        {
            int count_of_letter = 0, index_of = 0;
            for (int i = 0; i < str.size(); i++)
            {
                if (str[i] != ' ')
                {
                    count_of_letter++;
                    command.push_back(str[i]);
                }
                else if (str[i] == ' ')
                {
                    index_of = i;
                    break;
                }
            }
            str=str.substr(index_of+1,str.size()-index_of);
            if(command=="register") Register(str);
            else if(command=="call") call(str);
            else if(command=="setName") setName(str);
        }
    } 
    return 0;
}
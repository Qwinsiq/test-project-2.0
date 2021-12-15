#pragma once
namespace comutator
{
    class MobileClient;
    class INetConfAgent
    {
    public:
        virtual bool subscribeForModelChanges(std::string modelName, std::string path, MobileClient &client)=0;
        virtual bool fetchData(std::string path, std::string &str)=0;
        virtual bool registerOperData(std::string modelName, std::string path, MobileClient &client)=0;
        virtual void changeData(const std::string path, std::string value)=0;
        virtual void deleteData(const std::string path)=0;
        virtual ~INetConfAgent()=default;
    };
}
#pragma once
#include <map>
namespace comutator
{
    class MobileClient;
    class INetConfAgent
    {
    public:

        /*
    @Brief Makes subscription on concrete path on running Data
    @param modelName- name of model, where our subscription item is locate
    @param path- path to our item
    @param client- object of MobileClient that call metod subscribeForModelChange
    @return true- if subscription is succesfel created
            false-if subscription is not created
    */
        virtual bool subscribeForModelChanges(std::string modelName, std::string path, MobileClient &client)=0;

        /*
    @Brief copy Data, that locate by path into string
    @param  path- path to coping Data
    @param str- string, which will be recorded Data
    @return true-if Data succesful coped,
            false-if any Data wasn't coped ib any Datastore(Running,Operational)
    */
        virtual bool fetchData(std::string path, std::string &str)=0;

        /*
    @Brief Makes subscription on concrete path on operational Data
    @param modelName- name of model, where our subscription item is locate
    @param path- path to our item
    @param client- object of MobileClient that call metod registerOperData
    @return true- if subscription is succesfel created
            false-if subscription is not created
    */
        virtual bool registerOperData(std::string modelName, std::string path, MobileClient &client)=0;

        /*
    @Brief change Data in a specific path
    @param path- path in which is located changing Data
    @param value- new Data that have to be recorded
       */
        virtual void changeData(const std::string path, std::string value)=0;

        /*
    @Brief delete Data in specific path
    @param path- path in which is located Data needed to delete
    */
        virtual void deleteData(const std::string path)=0;
    /*
    @Brief default destructor
    */

    virtual void notifySysrepo (std::map<std::string,std::string> mp)=0;
        virtual ~INetConfAgent()=default;
    };
}
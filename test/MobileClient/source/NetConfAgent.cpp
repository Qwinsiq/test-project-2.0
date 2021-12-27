#include "NetConfAgent.hpp"
#include <iostream>
#include <optional>
#include <string>
#include <atomic>
#include "MobileClient.hpp"
#include "sysrepo-cpp/utils/exception.hpp"
namespace comutator
{
    NetConfAgent::NetConfAgent() : _connection(), _session(_connection.sessionStart())
    {
    }
    bool NetConfAgent::fetchData(std::string path, std::string &str)
    {
        auto data = _session.getData(path.c_str());
        if (data != std::nullopt)
        {
            str = data->findPath(path.c_str()).value().asTerm().valueStr();
            return true;
        }
        else
        {
            _session.switchDatastore(sysrepo::Datastore::Operational);
            data = _session.getData(path.c_str());
            _session.switchDatastore(sysrepo::Datastore::Running);
            if (data != std::nullopt)
            {
                str = data->findPath(path.c_str()).value().asTerm().valueStr();
                return true;
            }
            else
                return false;
        }
    }
    void NetConfAgent::deleteData(const std::string path)
    {
        _session.deleteItem(path.c_str());
        _session.applyChanges();
    }
    void NetConfAgent::changeData(const std::string path, std::string value)
    {
        const char *s = path.c_str();
        const char *r = value.c_str();
        _session.setItem(s, r);
        _session.applyChanges();
    }
    bool NetConfAgent::subscribeForModelChanges(std::string modelName, std::string path, MobileClient &client)
    {
        sysrepo::ModuleChangeCb moduleChangeCb = [&](sysrepo::Session session, auto, auto, auto, auto, auto) -> sysrepo::ErrorCode
        {
            auto change = session.getChanges();
            for (auto r : change)
            {
                if (r.node.schema().nodeType() == libyang::NodeType::Leaf)
                {
                    client.handleModuleChange(static_cast<std::string>(r.node.path()), static_cast<std::string>(r.node.asTerm().valueStr()));
                }
            }
            return sysrepo::ErrorCode::Ok;
        };
        _subscription = _session.onModuleChange(modelName.c_str(), moduleChangeCb, path.c_str(), 0, sysrepo::SubscribeOptions::DoneOnly);
        if (_subscription != std::nullopt)
            return true;
        else
            return false;
    }
    bool NetConfAgent::registerOperData(std::string modelName, std::string path, MobileClient &client)
    {
        sysrepo::OperGetItemsCb operGetCb = [path, &client](sysrepo::Session sess, auto, auto, auto, auto, auto, std::optional<libyang::DataNode> &parent)
        {
            parent = sess.getContext().newPath(path.c_str(), client.getName().c_str());
            return sysrepo::ErrorCode::Ok;
        };
        _operSub = _session.onOperGetItems(modelName.c_str(), operGetCb, path.c_str());
        if (_operSub != std::nullopt)
            return true;
        else
            return false;
    }
    void NetConfAgent::notifySysrepo(std::map<std::string, std::string> mp)
    {
        auto it = mp.begin();
        auto notification = _session.getContext().newPath("/commutator:statCall");
        for (int i = 0; it != mp.end(); i++, it++)
        {
            notification.newPath(it->first.c_str(), it->second.c_str());
        }
        _session.sendNotification(notification, sysrepo::Wait::Yes);
    }

}
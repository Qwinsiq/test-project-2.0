#pragma once
#include <gmock/gmock.h>
#include "INetConfAgent.hpp"


class NetConfAgentMock : public comutator::INetConfAgent
{
public:
    MOCK_METHOD(bool, subscribeForModelChanges, (std::string modelName, std::string path, comutator::MobileClient &client),(override));
    MOCK_METHOD(bool, fetchData,(std::string path, std::string &str), (override));
    MOCK_METHOD(bool, registerOperData,(std::string modelName, std::string path, comutator::MobileClient &client), (override));
    MOCK_METHOD(void, changeData, (const std::string path, std::string value),(override));
    MOCK_METHOD(void, deleteData, (const std::string path), (override));
};

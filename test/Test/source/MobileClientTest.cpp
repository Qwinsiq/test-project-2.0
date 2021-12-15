#include <gtest/gtest.h>
#include "MobileClient.hpp"
#include "NetConfAgentMock.hpp"

using testing::Return;
using testing::_;
using testing::StrictMock;
namespace test
{
class MobileClientTest:public testing::Test
{
    protected:
    void SetUp() override
    {
        auto tempMock= std::make_unique<StrictMock<NetConfAgentMock>>();
        _mock=tempMock.get();
        _client=std::make_unique<comutator::MobileClient>(std::move(tempMock));
    }
 StrictMock <NetConfAgentMock>* _mock;
 std::unique_ptr<comutator::MobileClient> _client;
 
};
TEST_F(MobileClientTest, TestSetName)
{
    _client->setName("Alex");
    std::string str = "Alex";
    EXPECT_EQ(_client->getName(), str);
}
TEST_F(MobileClientTest, TestRegisterReturnFalse)
{
    std::string path="/commutator:subscribers/subscriber[number='1234']/number";
    EXPECT_CALL(*_mock,fetchData(path,_)).WillOnce(Return (true));
    EXPECT_FALSE(_client->Register("1234"));
}
TEST_F(MobileClientTest, TestRegisterReturnTrue)
{
    EXPECT_CALL(*_mock, fetchData).WillOnce(Return (false));
    EXPECT_CALL(*_mock,changeData).Times(1);
    EXPECT_CALL(*_mock, subscribeForModelChanges).WillOnce(Return (true));
    EXPECT_CALL(*_mock, registerOperData).WillOnce(Return (true));
    EXPECT_TRUE(_client->Register("1234"));
}
TEST_F(MobileClientTest, TestCallTrue)
{
    EXPECT_CALL(*_mock, fetchData(_,_)).WillRepeatedly(Return (true));
    EXPECT_CALL(*_mock, changeData).Times(3);
    EXPECT_TRUE(_client->call("4321"));
}
TEST_F(MobileClientTest, TestCallFalse)
{
    EXPECT_CALL(*_mock, fetchData(_,_)).Times(3).WillOnce(Return(false)).WillRepeatedly(Return (true));
    EXPECT_CALL(*_mock,changeData).Times(3);
    EXPECT_FALSE(_client->call("4321"));
}

}
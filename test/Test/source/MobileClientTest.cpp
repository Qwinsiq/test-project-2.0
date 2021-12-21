#include <gtest/gtest.h>
#include "MobileClient.hpp"
#include "NetConfAgentMock.hpp"

#include <string>

using testing::_;
using testing::AtLeast;
using testing::DoAll;
using testing::Return;
using testing::SetArgReferee;
using testing::StrictMock;

namespace
{
    using std::string;
    const string user1numberPath = "/commutator:subscribers/subscriber[number='123']/number";
    const string user1incomingnumberPath = "/commutator:subscribers/subscriber[number='123']/incomingNumber";
    const string user1statePath = "/commutator:subscribers/subscriber[number='123']/state";
    const string user2numberPath = "/commutator:subscribers/subscriber[number='321']/number";
    const string user2incomingnumberPath = "/commutator:subscribers/subscriber[number='321']/incomingNumber";
    const string user2statePath = "/commutator:subscribers/subscriber[number='321']/state";
    const string user1NamePath = "/commutator:subscribers/subscriber[number='321']/userName";
    const string user1Path="/commutator:subscribers/subscriber[number='123']";
    const string number1 = "123";
    const string number2 = "321";
    const string active = "active";
    const string idle = "idle";
    const string busy = "busy";

}
namespace test
{
    class MobileClientTest : public testing::Test
    {
    protected:
        void SetUp() override
        {
            auto tempMock = std::make_unique<StrictMock<NetConfAgentMock>>();
            _mock = tempMock.get();
            _client = std::make_unique<comutator::MobileClient>(std::move(tempMock));
        }
        void registUser1()

        {
            EXPECT_CALL(*_mock, fetchData(user1numberPath, _))
                .WillOnce(Return(false));
            EXPECT_CALL(*_mock, changeData(user1numberPath, number1))
                .Times(1);
            EXPECT_CALL(*_mock, subscribeForModelChanges)
                .WillOnce(Return(true));
            EXPECT_CALL(*_mock, registerOperData)
                .WillOnce(Return(true));
            EXPECT_TRUE(_client->Register(number1));
        }
        void callUser2()
        {
            EXPECT_CALL(*_mock, fetchData(user1numberPath, _))
                .WillOnce(DoAll(SetArgReferee<1>(number1), Return(true)));
            EXPECT_CALL(*_mock, fetchData(user2numberPath, _))
                .WillOnce(DoAll(SetArgReferee<1>(number2), Return(true)));
            EXPECT_CALL(*_mock, fetchData(user2statePath, _))
                .WillOnce(DoAll(SetArgReferee<1>(idle), Return(true)));
            EXPECT_CALL(*_mock, changeData(user1statePath, active));
            EXPECT_CALL(*_mock, changeData(user2statePath, active));
            EXPECT_CALL(*_mock, changeData(user2incomingnumberPath, number1));
            EXPECT_TRUE(_client->call(number2));
        }

        StrictMock<NetConfAgentMock> *_mock;
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
        EXPECT_CALL(*_mock, fetchData(user1numberPath, _))
            .WillOnce(DoAll(SetArgReferee<1>(number1), Return(true)));
        EXPECT_FALSE(_client->Register(number1));
        EXPECT_CALL(*_mock, deleteData(user1Path));
    }
    TEST_F(MobileClientTest, TestRegisterReturnTrue)
    {
        registUser1();
        EXPECT_CALL(*_mock, deleteData(user1Path));
    }
     TEST_F(MobileClientTest, TestCallTrue)
    {
        registUser1();
        EXPECT_CALL(*_mock, fetchData(user1numberPath, _))
            .WillOnce(DoAll(SetArgReferee<1>(number1), Return(true)));
        EXPECT_CALL(*_mock, fetchData(user2numberPath, _))
            .WillOnce(DoAll(SetArgReferee<1>(number2), Return(true)));
        EXPECT_CALL(*_mock, fetchData(user2statePath, _))
            .WillOnce(DoAll(SetArgReferee<1>(idle), Return(true)));
        EXPECT_CALL(*_mock, changeData(user1statePath, active));
        EXPECT_CALL(*_mock, changeData(user2statePath, active));
        EXPECT_CALL(*_mock, changeData(user2incomingnumberPath, number1));
        EXPECT_TRUE(_client->call(number2));

        
        _client->handleModuleChange(user1statePath, idle);
        EXPECT_CALL(*_mock, deleteData(user1Path));
    } 
    TEST_F(MobileClientTest, TestCallFalse1)
    {
        registUser1();
        EXPECT_CALL(*_mock, fetchData(user1numberPath, _))
            .WillOnce(DoAll(SetArgReferee<1>(number1), Return(true)));
        EXPECT_CALL(*_mock, fetchData(user2numberPath, _))
            .WillOnce(DoAll(SetArgReferee<1>(number2), Return(true)));
        EXPECT_CALL(*_mock, fetchData(user2statePath, _))
            .WillOnce(DoAll(SetArgReferee<1>(idle), Return(false)));

        EXPECT_FALSE(_client->call(number2));

        EXPECT_CALL(*_mock, deleteData(user1Path));
    }
    TEST_F(MobileClientTest, TestCallFalse2)
    {
        registUser1();
        EXPECT_CALL(*_mock, fetchData(user1numberPath, _))
            .WillOnce(DoAll(SetArgReferee<1>(number1), Return(true)));
        EXPECT_CALL(*_mock, fetchData(user2numberPath, _))
            .WillOnce(DoAll(SetArgReferee<1>(number2), Return(false)));

        EXPECT_FALSE(_client->call(number2));
        EXPECT_CALL(*_mock, deleteData(user1Path));
    }

    TEST_F(MobileClientTest, TestCallFalse3)
    {
        registUser1();
        EXPECT_CALL(*_mock, fetchData(user1numberPath, _))
            .WillOnce(DoAll(SetArgReferee<1>(number1), Return(false)));

        EXPECT_FALSE(_client->call(number2));
        EXPECT_CALL(*_mock, deleteData(user1Path));
    }

     TEST_F(MobileClientTest, TestAnswerTrue)

    {
        registUser1();

        _client->handleModuleChange(user1statePath, active);

        EXPECT_CALL(*_mock, fetchData(user1NamePath, _))
            .WillOnce(DoAll(SetArgReferee<1>("Kate"), Return(true)));
        _client->handleModuleChange(user1incomingnumberPath, number2);

        EXPECT_CALL(*_mock, changeData(user1statePath, busy));
        EXPECT_CALL(*_mock, changeData(user2statePath, busy));
        EXPECT_TRUE(_client->answer());

         _client->handleModuleChange(user1statePath, idle);
        EXPECT_CALL(*_mock, deleteData(user1Path));
    } 
    TEST_F(MobileClientTest, TestAnswerFalse)

    {
        registUser1();

        _client->handleModuleChange(user1statePath, idle);

        EXPECT_FALSE(_client->answer());
        EXPECT_CALL(*_mock, deleteData(user1Path));
    }
     TEST_F(MobileClientTest, TestRejectTrue)
    {
        registUser1();

        _client->handleModuleChange(user1statePath, active);

        EXPECT_CALL(*_mock, fetchData(user1NamePath, _))
            .WillOnce(DoAll(SetArgReferee<1>("Kate"), Return(true)));
        _client->handleModuleChange(user1incomingnumberPath, number2);

        EXPECT_CALL(*_mock, deleteData(user1incomingnumberPath));
        EXPECT_CALL(*_mock, changeData(user2statePath, idle));
        EXPECT_CALL(*_mock, changeData(user1statePath, idle));

        EXPECT_TRUE(_client->reject());

        _client->handleModuleChange(user1statePath, idle);
        EXPECT_CALL(*_mock, deleteData(user1Path));
    } 
    TEST_F(MobileClientTest, TestRejectFalse)

    {
        registUser1();

        _client->handleModuleChange(user1statePath, busy);

        EXPECT_FALSE(_client->reject());
        EXPECT_CALL(*_mock, deleteData(user1Path));
   }
     TEST_F(MobileClientTest, TestCallEndTrueOut)

    {
        registUser1();
        callUser2();
        _client->handleModuleChange(user1statePath, busy);

        EXPECT_CALL(*_mock, deleteData(user2incomingnumberPath));
        EXPECT_CALL(*_mock, changeData(user2statePath, idle));
        EXPECT_CALL(*_mock, changeData(user1statePath, idle));
        EXPECT_TRUE(_client->callEnd());

        _client->handleModuleChange(user1statePath, idle);
        EXPECT_CALL(*_mock, deleteData(user1Path));
    }
    TEST_F(MobileClientTest, TestCallEndTrueIncoming)

    {
        registUser1();

        _client->handleModuleChange(user1statePath, active);

        EXPECT_CALL(*_mock, fetchData(user1NamePath, _))
            .WillOnce(DoAll(SetArgReferee<1>("Kate"), Return(true)));
        _client->handleModuleChange(user1incomingnumberPath, number2);

        EXPECT_CALL(*_mock, changeData(user1statePath, busy));
        EXPECT_CALL(*_mock, changeData(user2statePath, busy));
        EXPECT_TRUE(_client->answer());

        _client->handleModuleChange(user1statePath, busy);
        EXPECT_CALL(*_mock, deleteData(user1incomingnumberPath));
        EXPECT_CALL(*_mock, changeData(user2statePath, idle));
        EXPECT_CALL(*_mock, changeData(user1statePath, idle));
        EXPECT_TRUE(_client->callEnd());

        _client->handleModuleChange(user1statePath, idle);
        EXPECT_CALL(*_mock, deleteData(user1Path));
    } 
     TEST_F(MobileClientTest, TestCallEndFalseOut)

    {
        registUser1();
        callUser2();
        _client->handleModuleChange(user1statePath, active);
        EXPECT_FALSE(_client->callEnd());


        _client->handleModuleChange(user1statePath, idle);
        EXPECT_CALL(*_mock, deleteData(user1Path));
    } 
    TEST_F(MobileClientTest, TestCallEndFalseIncoming)

    {
        registUser1();

        _client->handleModuleChange(user1statePath, active);

        EXPECT_CALL(*_mock, fetchData(user1NamePath, _))
            .WillOnce(DoAll(SetArgReferee<1>("Kate"), Return(true)));
        _client->handleModuleChange(user1incomingnumberPath, number2);

        EXPECT_CALL(*_mock, changeData(user1statePath, busy));
        EXPECT_CALL(*_mock, changeData(user2statePath, busy));
        EXPECT_TRUE(_client->answer());

        _client->handleModuleChange(user1statePath, idle);
        EXPECT_FALSE(_client->callEnd());
        EXPECT_CALL(*_mock, deleteData(user1Path));
    }
    TEST_F(MobileClientTest, TestUnregisterTrue)
    {
        registUser1();
        _client->handleModuleChange(user1statePath, idle);
        EXPECT_CALL(*_mock, deleteData(user1Path));
        EXPECT_TRUE(_client->unregister());
        EXPECT_CALL(*_mock, deleteData(user1Path));
    }
    TEST_F(MobileClientTest, TestUnregisterFalse)
    {
        registUser1();
        callUser2();
        EXPECT_FALSE(_client->unregister());
        
        EXPECT_CALL(*_mock,deleteData(user1Path));
    }

}
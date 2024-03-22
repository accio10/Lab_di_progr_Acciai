//
// Created by Nathan on 17/03/2024.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../User.h"
#include <mutex>

using testing:: Eq;
enum CausaTransazione;
class TesterUser :public ::testing::Test{
public:
    std::unique_ptr<User> tested;
    std::tm* date;

    TesterUser(){
        date = nullptr;
    }

    void SetUp () override {
        date = new std:: tm;
        date->tm_year = 100;
        date-> tm_mon = 1;
        date -> tm_mday = 1;
        date -> tm_hour = 10;
        date -> tm_min = 10;
        date -> tm_sec = 10;
        std::string address="TestAddress";
        std::string name="Test";
        tested = std::make_unique<User>(name,address ,date,false);
    }

};

TEST_F(TesterUser,transferValidationUSer){

    tested->Operation(200,TEST);
    ASSERT_EQ(200,tested->getAccount()->getBalance());
}
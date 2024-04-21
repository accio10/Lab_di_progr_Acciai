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
    std::unique_ptr<User>tested2;
    std::tm* date2;

    TesterUser(){
        date = nullptr;
        date2= nullptr;
    }

    void SetUp () override {
        date = new std:: tm;
        date->tm_year = 100;
        date-> tm_mon = 1;
        date -> tm_mday = 1;
        date -> tm_hour = 10;
        date -> tm_min = 10;
        date -> tm_sec = 10;
        date2 = new std:: tm;
        date2->tm_year = 90;
        date2-> tm_mon = 4;
        date2-> tm_mday = 3;
        date2 -> tm_hour = 10;
        date2 -> tm_min = 10;
        date2 -> tm_sec = 10;

        std::string address="TestAddress";
        std::string adderss2="Test2Address";
        std::string name="Test";
        std::string name2="Test2";
        tested = std::make_unique<User>(name,address ,date,false);
        tested2=std::make_unique<User>(name2,adderss2,date2,false);
    }

};

TEST_F(TesterUser,transferValidationUser){//Eseguo un test per vedere se effettivamente il versamento viene eseguito

    tested->Operation(200,TEST);
    ASSERT_EQ(200,tested->getAccount()->getBalance());
}

TEST_F(TesterUser, transferUnvalidUser){//eseguo test per verificare che il versamento non venga eseguito se supera una certa cifra
    tested->Operation(2000,TEST);
    ASSERT_EQ(0,tested->getAccount()->getBalance());
}

TEST_F(TesterUser,checkactiveaccount){//eseguo un test per verificare che l'attivazione dell' account sia stata eseguita
    bool active = tested->AccountisAlive();
    ASSERT_EQ(true, active);
}

TEST_F(TesterUser, transferValidationforUser){//eseguo test per verificare che ci sia stato il corretto versamento
    tested->OperationtoUser(200,TEST,tested2->getAccount());
    ASSERT_EQ(tested->getAccount()->getBalance(),-200);
    ASSERT_EQ(tested2->getAccount()->getBalance(),200);
}

TEST_F(TesterUser, checkaddaccount){ //eseguo test per verificare che il nuovo contatto sia salvato nella rubrica
    tested->AddAccount(tested2->getAccount());
    ASSERT_EQ(tested->Sizeofrubrica(),2);
}

TEST_F(TesterUser,checkAddTransaction) //eseguo test per verificare che una transazione venga aggiunta correttamente
{
    std::string n=tested->getName();
    Transaction* t= new Transaction(20,Inflow,n,TEST);
    tested->addTransaction(*t);
    ASSERT_EQ(tested->getAccount()->getSizeofTransaction(),1);
}

TEST_F(TesterUser, checkDeletedAccount)//eseguo il test per verificare che l'account venga disabilitato
{
    tested->deleteAccount();
    ASSERT_EQ(tested->AccountisAlive(),false);
}



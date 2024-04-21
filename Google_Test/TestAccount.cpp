//
// Created by Nathan on 21/04/2024.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Account.h"
#include <mutex>

using testing::Eq;
enum CausaTransazione;
class TesterAccount:public ::testing::Test{
public:
    std::unique_ptr<Account> tested;
    std::unique_ptr<Account> tested2;
    TesterAccount(){
        std::string name="test";
        std::string name2="test2";
        std::string namefile="test.txt";
        std::string namefile2="test2.txt";
        tested=std::make_unique<Account>(name,namefile,-1000);
        tested2=std::make_unique<Account>(name2,namefile2,-1000);
    }
};
TEST_F(TesterAccount,depositTest){ //eseguo test per la corretta verifica che il deposito sia effettuato
    std::string name=tested->getName();
    tested->Operation(name,20,TEST);
    ASSERT_EQ(20,tested->getBalance());
}

TEST_F(TesterAccount,TransferTest) //eseguo test per la corretta verifica che il versamento sia effettuato
{
    EXPECT_EQ(tested->getBalance(),0);
    std::string name=tested->getName();
    tested->OperationforUser(name,20,TEST,tested2);
    ASSERT_EQ(tested2->getBalance(),20);
    ASSERT_EQ(tested->getBalance(),-20);
}

TEST_F(TesterAccount,depositTestUnvalid) //eseguo un test per verificare che dopo un deposito fallito il conto non abbia avuto modifiche
{
    std::string name=tested->getName();
    try {
        tested->Operation(name, 1001, TEST);
    }
    catch(std::runtime_error &e) {
        ASSERT_EQ(tested->getBalance(), 0);
    }
}

TEST_F(TesterAccount, checkRemoveTransaction){ //eseguo test per la verifica della rimozione di una transazione
    std::string name=tested->getName();
    Transaction* t= new Transaction(20,Inflow,name,TEST);
    Transaction* t1= new Transaction(20,Inflow,name,TEST);
    Transaction* t2= new Transaction(20,Inflow,name,TEST);
    tested->AddTransaction(*t);
    tested->AddTransaction(*t1);
    tested->AddTransaction(*t2);
    ASSERT_EQ(tested->getSizeofTransaction(),3);
    tested->removeTransaction(0);
    ASSERT_EQ(tested->getSizeofTransaction(),2);
}


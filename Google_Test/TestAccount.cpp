//
// Created by Nathan on 21/04/2024.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Account.h"
#include <mutex>

using testing::Eq;
enum CausaTransazione;

class TesterAccount : public ::testing::Test {
public:
    std::unique_ptr<Account> tested;
    std::unique_ptr<Account> tested2;
    std::unique_ptr<Account> accountnull = std::unique_ptr<Account>(nullptr);

    TesterAccount() {
        std::string name = "test";
        std::string name2 = "test2";
        std::string namefile = "test.txt";
        std::string namefile2 = "test2.txt";
        tested = std::make_unique<Account>(name, namefile, -1000);
        tested2 = std::make_unique<Account>(name2, namefile2, -1000);
    }

    tm *CreateDate() {
        tm *date = new tm();
        date->tm_year = 100;
        date->tm_mon = 1;
        date->tm_mday = 1;
        date->tm_hour = 10;
        date->tm_min = 10;
        date->tm_sec = 10;
        return date;
    }
};

TEST_F(TesterAccount, depositTest) { //eseguo test per la corretta verifica che il deposito sia effettuato
    std::string name = tested->getName();
    tested->Operation(name, 20, TEST, accountnull);
    ASSERT_EQ(20, tested->getBalance());
}

TEST_F(TesterAccount, TransferTest) {
    EXPECT_EQ(tested->getBalance(), 0);
    std::string name = tested->getName();
    tested->Operation(name, 20, TEST, tested2);
    ASSERT_EQ(tested2->getBalance(), 20);
    ASSERT_EQ(tested->getBalance(), -20);
}

TEST_F(TesterAccount,
       depositTestUnvalid) {
    std::string name = tested->getName();
    try {
        tested->Operation(name, 1001, TEST, accountnull);
    }
    catch (std::runtime_error &e) {
        ASSERT_EQ(tested->getBalance(), 0);
    }
}

TEST_F(TesterAccount, checkRemoveTransaction) {
    std::string name = tested->getName();
    Transaction *t = new Transaction(20, Inflow, name, TEST);
    Transaction *t1 = new Transaction(20, Inflow, name, TEST);
    Transaction *t2 = new Transaction(20, Inflow, name, TEST);
    tested->AddTransaction(*t);
    tested->AddTransaction(*t1);
    tested->AddTransaction(*t2);
    ASSERT_EQ(tested->getSizeofTransaction(), 3);
    tested->removeTransaction(0);
    ASSERT_EQ(tested->getSizeofTransaction(), 2);
}

TEST_F(TesterAccount, checkAddTransaction) {
    std::string name = tested->getName();
    Transaction *t = new Transaction(20, Inflow, name, TEST);
    Transaction *t1 = new Transaction(20, Inflow, name, TEST);
    tested->AddTransaction(*t);
    tested->AddTransaction(*t1);
    ASSERT_EQ(tested->getSizeofTransaction(), 2);
}

TEST_F(TesterAccount, checkGetAllOperation) {
    std::string name = tested->getName();
    Transaction *t = new Transaction(20, Inflow, name, TEST);
    tested->AddTransaction(*t);
    ASSERT_EQ(tested->getSizeofTransaction(), 1);
    ASSERT_EQ(tested->getAllOperation().size(), 1);
}

TEST_F(TesterAccount, checkGetOperation) {
    std::string name = tested->getName();
    Transaction *t = new Transaction(20, Inflow, name, TEST);
    tested->AddTransaction(*t);
    Transaction *t1 = new Transaction(20, Outflow, name, TEST);
    tested->AddTransaction(*t1);
    ASSERT_EQ(tested->getSizeofTransaction(), 2);
    ASSERT_EQ(tested->getOperation(Inflow).size(), 1);
}

TEST_F(TesterAccount, checkGetTransactionForDate) {
    tm *date = CreateDate();
    std::string name = tested->getName();
    Transaction *t = new Transaction(20, Inflow, name, TEST, date);
    tested->AddTransaction(*t);
    Transaction *t1 = new Transaction(20, Inflow, name, TEST, date);
    tested->AddTransaction(*t1);
    ASSERT_EQ(tested->getSizeofTransaction(), 2);
    ASSERT_EQ(tested->getTransactionforDate(date).size(), 2);
}
//aggiungere test ricerca transazioni
// formattazione codice
//operation for user da eliminare
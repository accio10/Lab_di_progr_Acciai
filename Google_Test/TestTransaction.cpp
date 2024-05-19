//
// Created by Nathan on 21/04/2024.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Account.h"
#include <mutex>

using testing::Eq;
enum CausaTransazione;
enum TipoTransazioni;

class TesterTransaction : public ::testing::Test {
public:
    //int v, TipoTransazioni tpt, std::string& sender,CausaTransazione cause
    std::unique_ptr<Transaction> tested;

    TesterTransaction() {
        std::string name = "test";
        tested = std::make_unique<Transaction>(2, Inflow, name, TEST);
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

TEST_F(TesterTransaction, checkTimeAndDate) {
    tm *date = CreateDate();
    std::string name = tested->getSender();
    std::unique_ptr<Transaction> tested = std::make_unique<Transaction>(2, Inflow, name, TEST, date);
    ASSERT_EQ(std::asctime(date), std::asctime(tested->getDate()));
}

TEST_F(TesterTransaction, checkSetTimeAndDate) {//eseguo test per la verfica di inserimento manuale della data
    tm *date = CreateDate();
    tested->setDate(date);
    ASSERT_EQ(asctime(date), asctime(tested->getDate()));
}

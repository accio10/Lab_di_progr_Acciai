//
// Created by Nathan on 12/02/2024.
//
#include "Account.h"
#include <vector>
#include <time.h>
#include <ctime>
#include <ios>
#include <strstream>
#include <fstream>

void Account::Operation(std::string &n, int value, CausaTransazione cause, std::unique_ptr<Account> &account1) {
    if (value < minversamento) {
        if (balance + value > minbalance) {
            balance = balance + value;
            if (value >= 0) {
                historytransaction.push_back(std::make_unique<Transaction>(value, Inflow, n, cause));
                writeReport(new Transaction(value, Inflow, n, cause));
            } else {
                historytransaction.push_back(std::make_unique<Transaction>(value, Outflow, n, cause));
                writeReport(new Transaction(value, Outflow, n, cause));
            }
            if (account1 != nullptr) {
                int tmp = value;
                std::unique_ptr<Account> acc = std::unique_ptr<Account>(nullptr);
                account1->Operation(n, -tmp, cause, acc);
            }
        } else
            throw (std::runtime_error("Error, you have exceeded your maximum withdrawal " + getBalance()));
    } else
        throw (std::runtime_error("Error you want pay a user or put too much money in your account!!"));
}

int Account::getBalance() const {
    return balance;
}

const std::string Account::getName() const {
    return name;
}

int const Account::getminBalance() const {
    return minbalance;
}

const std::string Account::getNameFile() const {
    return namefile;
}

const int Account::getSizeofTransaction() const {
    return historytransaction.size();
}

std::vector<Transaction> Account::getOperation(TipoTransazioni type) const {
    std::vector<Transaction> result;
    for (auto &item: historytransaction) {
        if (item->getTypeof() == type)
            result.push_back(*(item));
    }
    return result;
}

std::vector<Transaction> Account::getTransactionforDate(tm *dateTime) const {
    std::vector<Transaction> result;
    for (auto &item: historytransaction) {
        tm *tmp = item->getDate();
        if (item->EqualDate(tmp, dateTime))
            result.push_back(*(item));
    }
    return result;
}

std::vector<Transaction> Account::getAllOperation() const {
    std::vector<Transaction> result;
    for (auto &item: historytransaction)
        result.push_back(*(item));
    return result;
}

Transaction Account::removeTransaction(int index) {
    std::unique_ptr<Transaction> temp;
    temp.swap(historytransaction.at(index));
    historytransaction.erase(historytransaction.begin() + index);
    return *temp;
}

void Account::AddTransaction(const Transaction &transaction) {
    historytransaction.push_back(std::make_unique<Transaction>(transaction));
}

void Account::writeReport(Transaction *transaction) const {
    std::ofstream outfile(namefile, std::ios::app);
    outfile << "Type: " << transaction->getTypeof() << std::endl;
    outfile << "Value: " << transaction->getValue() << std::endl;
    outfile << "Sender: " << transaction->getSender() << std::endl;
    outfile << "Cause: " << transaction->getCause() << std::endl;
    outfile << "Date: " << transaction->getDate() << std::endl;
    outfile.close();
}






//
// Created by Nathan on 12/02/2024.
//
#include "Account.h"
#include <vector>
void Account::Operation(std::string n, int value, std::string cause) {
    if(balance+value>minbalance){
        balance=balance +value;
        if(value>=0)
            historytransaction.push_back(std::make_unique<Transaction>(value,"Inflow",n,cause));
        else
            historytransaction.push_back(std::make_unique<Transaction>(value,"Ouflow",n,cause));
    }
    else
        throw (std::runtime_error("Error, you have exceeded your maximum withdrawal "+ getBalance()+$));
}
int Account::getBalance() const {
    return balance;
}
std::string Account::getName() const {
    return name;
}
int const Account::getminBalance() const {
    return minbalance;
}

std::vector<Transaction> Account::getOperation(std::string type) {
    std::vector<Transaction> result;
    for(auto & item: historytransaction)
    {
        if(item->gettypeof()=="Inflow")
            result.push_back(*(item));
        else
            result.push_back(*(item));
    }
    return result;
}
std::vector<Transaction> Account::getTransactionforDate(tm *dateTime) {
    std::vector<Transaction>result ;
    for (auto & item: historytransaction) {
        if(asctime(dateTime)==item->getDateTime())
            result.push_back(*(it));
    }
}

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

void Account::Operation(std::string n, int value, std::string cause) {
    if(balance+value>minbalance){
        balance=balance +value;
        if(value>=0) {
            historytransaction.push_back(std::make_unique<Transaction>(value, "Inflow", n, cause));
            writeReport(new Transaction(value,"Inflow",n,cause));
        }
        else {
            historytransaction.push_back(std::make_unique<Transaction>(value, "Outflow", n, cause));
            writeReport(new Transaction(value,"Outflow",n,cause));
        }
    }
    else
        throw (std::runtime_error("Error, you have exceeded your maximum withdrawal "+ getBalance()));
}
void Account::OperationforUser(std::string n, int value, std::string cause, std::unique_ptr<Account>& account) {
    this->Operation(n,value,cause);
    int tmp=-value;
    account->Operation(n,tmp,cause);
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

std::vector<Transaction> Account::getOperation(std::string type) const {
    std::vector<Transaction> result;
    for(auto & item: historytransaction)
    {
        if(item->getTypeof()==type)
            result.push_back(*(item));
    }
    return result;
}
std::vector<Transaction> Account::getTransactionforDate(tm *dateTime) const{
    std::vector<Transaction>result ;
    for (auto & item: historytransaction) {
        tm *tmp= item->getDate();
        if(item->EqualDate(tmp,dateTime))
            result.push_back(*(item));
    }
    return result;
}
std::vector<Transaction> Account::getAllOperation() const {
    std::vector<Transaction> result;
    for(auto &item: historytransaction)
        result.push_back(*(item));
    return result;
}

Transaction Account::removeTransaction(int index) {
    std::unique_ptr<Transaction> temp;
    temp.swap(historytransaction.at(index));
    historytransaction.erase(historytransaction.begin()+index);
    return *temp;
}
void Account::AddTransaction(const Transaction &transaction) {
    historytransaction.push_back(std::make_unique<Transaction>(transaction));
}

void Account::writeReport(Transaction *transaction) {
    std::ofstream outfile (namefile,std::ios::app);
    outfile <<"Type: "<<transaction->getTypeof()<<std::endl;
    outfile <<"Value: "<< transaction->getValue() <<std::endl;
    outfile <<"Sender: "<<transaction->getSender()<<std::endl;
    outfile <<"Cause: "<<transaction->getCause()<<std::endl;
    outfile <<"Date: "<<transaction->getDate()<<std::endl;
    outfile.close();
}
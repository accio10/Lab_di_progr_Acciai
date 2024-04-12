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

void Account::Operation(std::string& n, int value, CausaTransazione cause) {
if(value<minversamento) {
    if (balance + value > minbalance) {
        balance = balance + value;
        if (value >= 0) {
            historytransaction.push_back(std::make_unique<Transaction>(value, Inflow, n, cause));
            writeReport(new Transaction(value, Inflow, n, cause));
        } else {
            historytransaction.push_back(std::make_unique<Transaction>(value, Outflow, n, cause));
            writeReport(new Transaction(value, Outflow, n, cause));
        }
    } else
        throw (std::runtime_error("Error, you have exceeded your maximum withdrawal " + getBalance()));
}else
    throw (std::runtime_error("Error you want pay a user or put too much money in your account!!"));
}
void Account::OperationforUser(std::string& n, int value, CausaTransazione cause, User& user) {
    AddAccount(user);
    this->Operation(n,value,cause);
    int tmp=-value;
    user.getAccount()->Operation(n,tmp,cause);

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

std::vector<Transaction> Account::getOperation(TipoTransazioni type) const {
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

void Account::AddAccount(User &user) {
    std::string name1= user.getName();
    std::string address= user.getAddress();
    rubrica.push_back(std::make_unique<User>(name1,address,user.getDateofBirthday(),false));
}

void Account::getNameOfUser() const {
    std::cout<<"Gli utenti presenti in rubrica sono"<<std::endl;
    for(auto &item: rubrica){
        std::string n= item->getName();
        std::cout<<n<<std::endl;
    }
}

int Account::getSizeofRubrica() const {
    return rubrica.size();
}

//
// Created by Nathan on 12/02/2024.
//
#include "User.h"

std::string User::getName() const {
    return name;
}
std::string User::getAddress() const {
    return address;
}
std::string User::getDateofBirthday() const {
    return dateofBirthday;
}
bool User::AccountisAlive() const {
    return accountalive;
}

bool User::Operation(int value, std::string cause) {
    if(accountalive) {
        try {
            account->Operation(this->name, value, cause);
        }
        catch (std::runtime_error &e) {
            std::printf(e.what());
            return false;
        }
        return true;

    }
    return false;
}

bool User::OperationtoUser(int value, User & user,std::string cause,Account & account1) {

    if (accountalive) {
        try {
            account->OperationforUser(name, value, cause, account1);
        }
        catch (std::runtime_error &e) {
            std::printf(e.what());
            return false;
        }
        return true;

    }
    return false;
}
void User::addTransaction(Transaction &transaction) {
    if(accountalive) {
        account->AddTransaction(transaction);
    }
}
bool User::removeTransaction(int index) {
    if(accountalive)
        try{
            account->removeTransaction(index);
        }
        catch(std::out_of_range & e){
            std::cout << e.what()<< std::endl;
            return false;
        }
        return true;
}
bool User::deleteAccount() {
    if(!accountalive) {
        accountalive = false;
        clearReport();
    }
}
void User::readReport() const {
    char c;
    std::ifstream read(namefile);
    while(read.get(c))
        std::cout <<c;
    read.close();
}
void User::clearReport() {
    std::ofstream del(namefile);
    del<<"";
    del.close();
}
void User::printUser() const {
    std::cout<< this->getName()<<std::endl;
    std::cout<< this->getAddress()<<std::endl;
    std::cout<< this->getDateofBirthday()<<std::endl;
    std::cout<< this->AccountisAlive()<<std::endl;
}

void User::printInflowHistory() const {
    std::vector<Transaction> transactions;
    transactions=this->account->getOperation("Inflow");
    for (auto & item:transactions) {
        printTransaction(item);
    }
}
void User::printOutflowHistory() const {
    std::vector<Transaction> transactions;
    transactions=this->account->getOperation("Outflow");
    for (auto & item:transactions) {
        printTransaction(item);
    }
}
void User::printTransaction(Transaction &transaction) const {
    std::cout<<"Type: "<<transaction.getTypeof()<<std::endl;
    std::cout<<"Sender: "<<transaction.getSender()<<std::endl;
    std::cout<<"Importo: "<<transaction.getValue()<<std::endl;
    std::cout<<"Causa: "<<transaction.getCause()<<std::endl;
}

void User::printforDate(tm *Datetransaction) const {
    std::vector<Transaction> transaction=account->getTransactionforDate(Datetransaction);
    for (auto & item: transaction) {
        printTransaction(item);
    }
}
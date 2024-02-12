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
            account->Operation(this.name, value, cause);
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
    if(accountalive)
        account->AddTransaction(transaction);
}
bool User::removeTransaction(int index) {
    if(accountalive)
        account->removeTransaction(index);
}
bool User::deleteAccount() {
    if(!accountalive)
        accountalive=false;
}
void User::writeReport(Transaction & transaction) {
    namefile="report"+name+".txt";
    std::ofstream outfile (namefile);
    outfile<< "Details" <<std::endl;
    outfile << name << std::endl;
    outfile << address << std::endl;
    outfile << dateofbirthday <<std::endl;

    outfile <<transaction.getTypeof()<<std::endl;
    outfile << transaction.getValue() <<std::endl;
    outfile <<transaction.getSender()<<std::endl;
    outfile <<transaction.getCause()<<std::endl;
    outfile <<transaction.getDate()<<std::endl;
    outfile.close();
}


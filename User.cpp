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
    try{
        account->Operation(this.name,value,cause);
    }
    catch (std::runtime_error & e){
        std::printf(e.what());
        return false;
    }
    return true;
}

bool User::OperationtoUser(int value, User & user,std::string cause,Account & account1) {
    try{
        account->OperationforUser(name,value,cause,account1);
    }
    catch (std::runtime_error & e) {
        std::printf(e.what());
        return false;
    }
    return true;
}



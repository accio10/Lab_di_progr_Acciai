//
// Created by Nathan on 12/02/2024.
//

#ifndef LAB_DI_PROGR_ACCIAI_USER_H
#define LAB_DI_PROGR_ACCIAI_USER_H

#include <vector>
#include "Account.h"

class User{
public:
    explicit User(std::string name,std::string address, std::string dateofbirthday){
        this->name=name;
        this->address=address;
        this->DateofBirthday=dateofbirthday;
        accountalive=true;
    }

    std::string getName() const;
    std::string getAddress() const;
    std::string getDateofBirthday() const;
    bool AccountisAlive() const;

    void Operation(int value,std::string cause);




private:
    std::string name;
    std::string address;
    std::string DateofBirthday;
    bool accountalive;
};
#endif //LAB_DI_PROGR_ACCIAI_USER_H

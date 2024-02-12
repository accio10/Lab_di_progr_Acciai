//
// Created by Nathan on 12/02/2024.
//

#ifndef LAB_DI_PROGR_ACCIAI_ACCOUNT_H
#define LAB_DI_PROGR_ACCIAI_ACCOUNT_H

class Account{
public:
    Account(int b){
        this->balance=b;
    }
    int getAccount(){
        return balance;
    }
    void setAccount(int v){
        this->balance=v;
    }

private:
    int balance;
};

#endif //LAB_DI_PROGR_ACCIAI_ACCOUNT_H

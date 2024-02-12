//
// Created by Nathan on 12/02/2024.
//

#ifndef LAB_DI_PROGR_ACCIAI_ACCOUNT_H
#define LAB_DI_PROGR_ACCIAI_ACCOUNT_H
#include <vector>
#include <memory>
#include <time.h>
#include "Transaction.h"
class Account{
public:
    explicit Account(std::string nam,int bal=0):name(std::move(nam)), balance(bal){}

    void Operation(std::string n,int value,std::string cause); //Eseguire un operazione
    void AddTransaction(const Transaction & transaction);
    Transaction removeTransaction(int index);

    int getBalance() const;
    const std::string getName() const;

    std::vector<Transaction> getInflow();
    std::vector<Transaction> getOutflow();
    std::vector<Transaction> getTransactionforDate(tm * dateTime);


private:
    std::string name;
    int balance;
    std::vector<std::unique_ptr<Transaction>> historytransaction; // è uno storico delle transazioni effettuate

};

#endif //LAB_DI_PROGR_ACCIAI_ACCOUNT_H

//
// Created by Nathan on 12/02/2024.
//

#ifndef LAB_DI_PROGR_ACCIAI_ACCOUNT_H
#define LAB_DI_PROGR_ACCIAI_ACCOUNT_H
#include <vector>
#include <memory>
#include <time.h>
#include "Transaction.h"

enum TipoTransazioni;
class Account{
public:
    Account(std::string& nam,std::string& nf,int mbal,int bal=0)
    {
        this->name=nam;
        this->namefile=nf;
        balance=bal;
        minbalance=mbal;
    }

    void Operation(std::string& n,int value,CausaTransazione); //Eseguire un operazione
    void OperationforUser(std::string& n,int value,CausaTransazione,std::unique_ptr<Account> &account);
    void AddTransaction(const Transaction & transaction);
    Transaction removeTransaction(int index);

    int getBalance() const;
    const std::string getName() const;
    const int getminBalance() const;


    std::vector<Transaction> getAllOperation() const;//Transaction da mettere
    std::vector<Transaction> getOperation(TipoTransazioni type) const;//transaction
    std::vector<Transaction> getTransactionforDate(tm * dateTime) const;//transaction

    void writeReport(Transaction *transaction);

private:
    std::string name;
    int balance;
    int minbalance;
    std::vector<std::unique_ptr<Transaction>> historytransaction; // è uno storico delle transazioni effettuate
    std::string namefile;
};

#endif //LAB_DI_PROGR_ACCIAI_ACCOUNT_H

//
// Created by Nathan on 12/02/2024.
//

#ifndef LAB_DI_PROGR_ACCIAI_ACCOUNT_H
#define LAB_DI_PROGR_ACCIAI_ACCOUNT_H
#include <vector>
#include <memory>
#include <time.h>
#include "Transaction.h"
#include "User.h"

enum TipoTransazioni;
class Account{
public:
    Account(std::string& nam,std::string& nf,int mbal,int bal=0, int minv=1000)
    {
        this->name=nam;
        this->namefile=nf;
        balance=bal;
        minbalance=mbal;
        minversamento=minv;
    }

    void Operation(std::string& n,int value,CausaTransazione); //Eseguire un operazione sul proprio account
    void OperationforUser(std::string& n,int value,CausaTransazione,User& user);//Eseguire operazioni tra due account di utenti diversi
    void AddTransaction(const Transaction & transaction);//Inserire una transazione in una determinata data
    Transaction removeTransaction(int index);
    void AddAccount(User & user);

    int getBalance() const;
    const std::string getName() const;
    const int getminBalance() const;
    void getNameOfUser() const;


    std::vector<Transaction> getAllOperation() const;//Transaction da mettere
    std::vector<Transaction> getOperation(TipoTransazioni type) const;//transaction
    std::vector<Transaction> getTransactionforDate(tm * dateTime) const;//transaction
    int getSizeofRubrica() const;

    void writeReport(Transaction *transaction);

private:
    std::string name;
    int balance;
    int minbalance;
    int minversamento;
    std::vector<std::unique_ptr<Transaction>> historytransaction; // è uno storico delle transazioni effettuate
    std::string namefile;
    std::vector<std::unique_ptr<User>> rubrica;
};

#endif //LAB_DI_PROGR_ACCIAI_ACCOUNT_H

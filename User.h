//
// Created by Nathan on 12/02/2024.
//

#ifndef LAB_DI_PROGR_ACCIAI_USER_H
#define LAB_DI_PROGR_ACCIAI_USER_H

#include <vector>
#include <memory>
#include <time.h>

#include "Account.h"
#include <iostream>
#include <fstream>
class User{
public:
    explicit User(std::string name,std::string address, tm* dateofbirthday,bool crea){
        this->name=name;
        this->address=address;
        this->dateofBirthday=dateofbirthday;
        accountalive=true;
        GenerateReport(crea);
    }
//getter e metodo per alive
    std::string getName() const;
    std::string getAddress() const;
    tm* getDateofBirthday() const;
    bool AccountisAlive() const;
    std::unique_ptr<Account>& getAccount();
    std::string getNamefile()const ;
    void GenerateReport(bool crea);

    //metodi per operazioni sul conto proprio o sul conto di alrti user
    bool Operation(int value,std::string cause);
    bool  OperationtoUser(int value, std::string cause, std::unique_ptr<Account>& account);
    void addTransaction(Transaction & transaction);
    bool removeTransaction(int index);
    void deleteAccount();
    void AddAccount(Account &a);
    //metodi per la visualizzazzione di informazioni

    void printUser() const;
    void printInflowHistory() const;
    void printOutflowHistory() const;
    void printforDate(tm *Datetransaction) const;
    void printTransaction(Transaction &transaction) const;
    void printAllTransaction() const;

    //metodi leggere e scrivere le transazioni su file

    void readReport() const;
    void clearReport();


private:
    std::string name;
    std::string address;
    tm* dateofBirthday;
    bool accountalive;
    std::unique_ptr<Account> account;
    std::string namefile;
};


#endif //LAB_DI_PROGR_ACCIAI_USER_H

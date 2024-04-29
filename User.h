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
enum TipoTransazioni;
class User{
public:
     User(std::string& name,std::string& address, tm* dateofbirthday,bool crea){
        this->name=name;
        this->address=address;
        this->dateofBirthday=dateofbirthday;
        accountalive=true;
        GenerateReport(crea);
        CreateAccount(this);
    }
//getter e metodo per alive
    std::string getName() const;
    std::string getAddress() const;
    tm* getDateofBirthday() const;
    bool AccountisAlive() const;
    std::unique_ptr<Account>& getAccount();
    std::string getNamefile()const ;
    void GenerateReport(bool crea); //Funzione per la generazione del report
    void CreateAccount(User *user); //Funzione per la generazione dell' account per l'user
    int Sizeofrubrica();
    std::unique_ptr<Account> findUser(User & user1,std::string &name) ; //Funzione per ricercare un utente nella rubrica


    //metodi per operazioni sul conto proprio o sul conto di alrti user
    bool Operation(int value,CausaTransazione cause,std::unique_ptr<Account>& account1);//funzione per operazione sul conto proprio
    bool  OperationtoUser(int value, CausaTransazione cause);//operazione verso utenti
    void addTransaction(Transaction & transaction);//funzione per aggiungere transazione
    bool removeTransaction(int index);//funzione per rimuovere transazione
    void deleteAccount();
    void AddAccount(std::unique_ptr<Account> &a);//funzione per aggiungere nuovi account

    //metodi per la visualizzazzione di informazioni

    void printUser() const;
    void printRubrica();
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
    std::vector<std::unique_ptr<Account>> rubrica;
};


#endif //LAB_DI_PROGR_ACCIAI_USER_H

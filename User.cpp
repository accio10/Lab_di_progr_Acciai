//
// Created by Nathan on 12/02/2024.
//
#include "User.h"
#include <iomanip>
#include <iostream>
#include <vector>


std::string User::getName() const {

    return name;
}

std::string User::getAddress() const {

    return address;
}

tm *User::getDateofBirthday() const {
    return dateofBirthday;
}

bool User::AccountisAlive() const {
    return accountalive;
}

std::string User::getNamefile() const {

    return namefile;
}

std::unique_ptr<Account> &User::getAccount() {
    return this->account;
}

void User::CreateAccount(User *user) {
    std::string n = user->getName();
    std::string nf = user->getNamefile();
    std::unique_ptr<Account> a = std::make_unique<Account>(n, nf, -10000);
    AddAccount(a);
}

void User::AddAccount(std::unique_ptr<Account> &a) {
    std::string nf = namefile;
    std::string n = a->getName();
    this->account = std::make_unique<Account>(n, nf, a->getminBalance());
    rubrica.push_back(std::make_unique<Account>(n, nf, 1000));
}

int User::Sizeofrubrica() const {
    return rubrica.size();
}

bool User::Operation(int value, CausaTransazione cause, std::unique_ptr<Account> &account1) {
    std::unique_ptr<Account> acc = std::unique_ptr<Account>(nullptr);
    if (accountalive) {
        if (account1 == nullptr) {
            try {
                account->Operation(this->name, value, cause, acc);
            }
            catch (std::runtime_error &e) {
                std::printf(e.what());
                return false;
            }
            return true;
        } else {
            try {
                account->Operation(name, value, cause, account1);
            }
            catch (std::runtime_error &e) {
                std::printf(e.what());
                return false;
            }
            return true;
        }

    }
    return false;

}

void User::addTransaction(Transaction &transaction) {
    if (accountalive) {
        account->AddTransaction(transaction);
    }
}

bool User::removeTransaction(int index) {
    if (accountalive)
        try {
            account->removeTransaction(index);
        }
        catch (std::out_of_range &e) {
            std::cout << e.what() << std::endl;
            return false;
        }
    return true;
}

void User::deleteAccount() {
    accountalive = false;
    clearReport();
}


void User::readReport() const {
    char c;
    std::ifstream read(namefile);
    while (read.get(c))
        std::cout << c;
    read.close();
}

void User::clearReport() {
    std::ofstream toClear;
    toClear.open(namefile, std::fstream::out | std::fstream::trunc);
    toClear.close();
}

void User::printUser() const {
    std::cout << this->getName() << std::endl;
    std::cout << this->getAddress() << std::endl;
    std::cout << this->getDateofBirthday() << std::endl;
    std::cout << this->AccountisAlive() << std::endl;
}

void User::printRubrica() const{
    std::cout << "i nomi salvati in rubrica sono:" << std::endl;
    for (auto &i: rubrica) {
        std::cout << i->getName() << std::endl;
    }

}

void User::printInflowHistory() const {
    if (accountalive) {
        std::vector<Transaction> transactions;
        transactions = this->account->getOperation(Inflow);
        bool find = false;
        for (auto &item: transactions) {
            printTransaction(item);
            find = true;
        }
        if (!find)
            std::cout << "Nessuna operazione in entrata trovata!" << std::endl;
    }

}

void User::printOutflowHistory() const {
    if (accountalive) {
        std::vector<Transaction> transactions;
        transactions = this->account->getOperation(Outflow);
        bool find = false;
        for (auto &item: transactions) {
            printTransaction(item);
            find = true;
        }
        if (!find)
            std::cout << "Nessuna operazione in uscita trovata!" << std::endl;
    }
}

void User::printTransaction(Transaction &transaction) const {
    if (accountalive) {
        std::cout << "Type: " << transaction.getTypeof() << std::endl;
        std::cout << "Sender: " << transaction.getSender() << std::endl;
        std::cout << "Importo: " << transaction.getValue() << std::endl;
        std::cout << "Causa: " << transaction.getCause() << std::endl;
        std::cout << "Date: " << asctime(transaction.getDate()) << std::endl;
    }
}

void User::printforDate(tm *Datetransaction) const {
    if (accountalive) {
        std::vector<Transaction> transaction = account->getTransactionforDate(Datetransaction);
        for (auto &item: transaction) {
            printTransaction(item);
        }
    }
}

void User::printAllTransaction() const {
    if (accountalive) {
        std::vector<Transaction> res = account->getAllOperation();
        for (auto &item: res)
            printTransaction(item);
    }
}


void User::GenerateReport(bool creato) {
    namefile = "report" + name + ".txt";
    std::fstream outfile1(namefile);
    if (outfile1.is_open())
        if (creato)
            namefile = "report" + name + "1.txt";
    std::ofstream outfile(namefile);
    outfile << "Details" << std::endl;
    outfile << name << std::endl;
    outfile << address << std::endl;
    outfile << dateofBirthday->tm_year << std::endl;
    outfile << dateofBirthday->tm_mon << std::endl;
    outfile << dateofBirthday->tm_mday << std::endl;
    outfile.close();
}

std::unique_ptr<Account> User::findUser(User &user1, std::string &name) {
    for (auto &i: rubrica) {
        if (i->getName() == name) {
            std::string n = i->getName();
            std::string nf = i->getNameFile();
            return std::make_unique<Account>(n, nf, i->getminBalance());

        }
    }
    return nullptr;
}


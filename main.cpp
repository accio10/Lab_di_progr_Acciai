#include <iostream>
#include "Transaction.h"
#include "User.h"
#include "Account.h"
#include <time.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

User *GenerateAccount(bool creato);

tm *CreateDate();

bool Checkinput(int i, int i1, int i2);

bool CheckDate(tm *pTm);

void Operazioni();

void CreateAccount(User *pUser);

void Payment(User *user);

void PrintTransaction(User *user, int i);

int main() {

    // testing::InitGoogleTest();
    //return RUN_ALL_TESTS();

    int sel = 0;
    User *user;
    std::string n;
    std::cout << "Benvenuto premere 1 per creare un account oppure 2 per uscire " << std::endl;
    do {
        std::cin >> sel;
    } while (!Checkinput(sel, 1, 2));
    switch (sel) {
        case 1: {
            user = GenerateAccount(false);
            break;
        }
        case 2: {
            std::cout << "Exit";
            return 0;
        }
    }
    while (true) {
        std::unique_ptr<Account> null = std::unique_ptr<Account>(nullptr);
        int scelta = 0;
        Operazioni();
        do {
            std::cin >> scelta;
        } while (!Checkinput(scelta, 0, 10));
        switch (scelta) {
            case 1: {
                int importo;
                std::cout << "Digitare l'importo da prelevare" << std::endl;
                do {
                    std::cin >> importo;
                } while (!Checkinput(importo, 1, 650));
                user->Operation(-importo, Prelievo, null);
                std::cout << "Prelievo effettuato!" << std::endl;
                break;
            }
            case 2: {
                int importo;
                std::cout << "Digitare la somma da versare" << std::endl;
                std::cin >> importo;
                user->Operation(importo, Versamento, null);
                std::cout << "Versamento effettuato!" << std::endl;
                break;
            }
            case 3: {
                std::cout << "Prego andare a inserire la data della transazione da effettuare" << std::endl;
                int importo;
                tm *date = CreateDate();
                std::cout << "Prego inserire l'importo della transazione" << std::endl;
                do {
                    std::cin >> importo;
                } while (!Checkinput(importo, 0, 1000));
                std::string n = user->getName();
                Transaction *t = new Transaction(importo, Outflow, n, Pagamento, date);
                user->addTransaction(*t);
                std::cout << "Transazione aggiunta con successo" << std::endl;
                break;
            }
            case 4: {
                int balance = user->getAccount()->getBalance();
                std::cout << "Il saldo attuale è: " << std::endl;
                std::cout << balance << std::endl;
                break;
            }
            case 5: {
                Payment(user);
                break;
            }
            case 6: {
                user->printUser();
                break;
            }
            case 7: {
                int sel;
                std::cout << "Digitare 1 se si vuole visualizzare tutte le operazioni" << std::endl;
                std::cout << "Digitare 2 se si vuole vedere le operazioni in uscita" << std::endl;
                std::cout << "Digitare 3 se si vuole vedere le operazioni in entrata" << std::endl;
                std::cin >> sel;
                PrintTransaction(user, sel);
                break;
            }
            case 8: {
                tm *Date = CreateDate();
                user->printforDate(Date);
                break;
            }
            case 9: {
                std::cout << "Il report è questo:" << std::endl;
                user->readReport();
                break;
            }
            case 10: {
                user->deleteAccount();
                std::cout << "eliminazione completata" << std::endl;
                std::cout << "Quitting....." << std::endl;
                std::cout << " Grazie per averci scelto buona serata" << std::endl;
                return 0;
            }
            case 0: {
                std::cout << "Quitting...";
                return 0;
            }
        }


    }

}

void PrintTransaction(User *user, int i) {
    switch (i) {
        case 1: {
            user->printAllTransaction();
            break;
        }
        case 2: {
            user->printOutflowHistory();
            break;
        }
        case 3: {
            user->printInflowHistory();
            break;
        }

    }
}

void Payment(User *user) {
    int scelta = 0;
    std::cout << "Premi 1 per i contatti in rubrica, premi 2 per un nuovo contatto " << std::endl;
    do {
        std::cin >> scelta;
    } while (!Checkinput(scelta, 1, 2));
    switch (scelta) {
        case 1: {
            user->printRubrica();
            std::string nome;
            std::cout << "Inserire il nome" << std::endl;
            std::cin >> nome;
            std::unique_ptr<Account> utente = user->findUser(*user, nome);
            if (utente == nullptr) {
                throw std::runtime_error("Utente non trovato");
                break;
            }
            std::cout << "Inserire l'importo da versare" << std::endl;
            int value;
            std::cin >> value;
            if (user->Operation(-value, Pagamento, utente))
                std::cout << "Pagamento effettuato!" << std::endl;
            else
                std::cout << "Errore pagamento non effettuato" << std::endl;
            break;
        }
        case 2: {
            User *tmp = GenerateAccount(true);
            CreateAccount(tmp);
            int value;
            std::cout << "Inserire l'importo da versare" << std::endl;
            std::cin >> value;
            if (user->Operation(-value, Pagamento, tmp->getAccount())) {
                user->AddAccount(tmp->getAccount());
                std::cout << "Pagamento effettuato!" << std::endl;
            } else
                std::cout << "Errore pagamneto non effettuato" << std::endl;
            break;
        }
    }

}

void CreateAccount(User *pUser) {

    std::string n = pUser->getName();
    std::string nf = pUser->getNamefile();
    std::unique_ptr<Account> account = std::make_unique<Account>(n, nf, -10000);
    pUser->AddAccount(account);
}

void Operazioni() {
    std::cout << "Premere 1 per Prelevare" << std::endl;
    std::cout << "Premere 2 per Versare" << std::endl;
    std::cout << "Premere 3 per aggiungere una transazione " << std::endl;
    std::cout << "Premere 4 per vedere il saldo" << std::endl;
    std::cout << "Premere 5 per fare un versamento" << std::endl;
    std::cout << "Premere 6 per vedere le informazioni relative all'account" << std::endl;
    std::cout << "Premere 7 per vedere le transazioni eseguite" << std::endl;
    std::cout << "Premere 8 per cercare una transazione per data" << std::endl;
    std::cout << "Premere 9 per leggere il proprio report" << std::endl;
    std::cout << "Premere 10 per cancellare l'account " << std::endl;
    std::cout << "Premere 0 per uscire " << std::endl;

}

User *GenerateAccount(bool creato) {
    std::string nome;
    tm *datadinascita = new tm;
    std::string indirizzo;

    std::cout << "inserire il nome utente" << std::endl;
    ws(std::cin);
    getline(std::cin, nome);
    std::cout << "Inserire l'indiirizzo di residenza " << std::endl;
    ws(std::cin);
    getline(std::cin, indirizzo);
    int c = 0;
    do {
        if (c != 0)
            std::cout << "Data invalida, prego riprovare l'inserimento: " << std::endl;
        std::cout << "Inserire i dati relativi alla data di nascita" << std::endl;
        datadinascita = CreateDate();
        c++;

    } while (!CheckDate(datadinascita));
    User *user;
    user = new User(nome, indirizzo, datadinascita, creato);
    return user;
}

tm *CreateDate() {
    tm *res = new tm;
    int day;

    do {
        std::cout << "Prego inserire il giorno : " << std::endl;
        std::cin >> day;
    } while (!Checkinput(day, 1, 31));
    int month;
    std::cout << "Prego inserire il mese : " << std::endl;
    do {
        std::cin >> month;
    } while (!Checkinput(month, 1, 12));
    int year;
    std::cout << "Prego inserire l'anno : " << std::endl;
    std::cin >> year;
    res->tm_mday = day;
    res->tm_mon = month;
    res->tm_year = year;
    return res;
}

bool CheckDate(tm *ptm) {
    time_t data;
    tm *Data;
    data = time(NULL);
    Data = localtime(&data);
    int trentagiorni[] = {4, 6, 9, 11};
    int trentunogiorni[] = {1, 3, 5, 7, 8, 10, 12};
    if (1900 <= ptm->tm_year && (Data->tm_year + 1900) - ptm->tm_year >= 18) {
        for (int i: trentunogiorni) {
            if (ptm->tm_mon == i)
                if (ptm->tm_mday >= 1 && ptm->tm_mday <= 31)
                    return true;
        }
        for (int i: trentagiorni) {
            if (ptm->tm_mon == i)
                if (ptm->tm_mday >= 1 && ptm->tm_mday <= 30)
                    return true;
        }
        if (ptm->tm_mon == 2)
            if (ptm->tm_mday >= 1 && ptm->tm_mday <= 28)
                return true;
        return false;
    } else
        return false;
}

bool Checkinput(int input, int minvalue, int maxvalue) {
    try {
        if (std::cin.good()) {
            if (input < minvalue)
                throw std::out_of_range(
                        "Il valore che hai inserito non è corretto, è più piccolo del valore minimo accettato");
            if (input > maxvalue)
                throw std::out_of_range(
                        "Il valore che hai inserito non è corretto, è più grande del valore minimo accettato");

        } else
            throw std::out_of_range("Il valore che hai inserito non è corretto");
    } catch (std::out_of_range &e) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << e.what() << std::endl;
        std::cout << "Inserire nuovamente il dato:" << std::endl;
        return false;
    }
    return true;
}

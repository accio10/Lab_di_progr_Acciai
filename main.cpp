#include <iostream>
#include "Transaction.h"
#include "User.h"
#include "Account.h"
#include <time.h>

User * GenerateAccount();

tm* CreateDate();

bool Checkinput(int i, int i1, int i2);

bool CheckDate(tm *pTm);

void Operazioni();

void CreateAccount(User *pUser);

void Payment(User *user, std::vector<std::unique_ptr<User>> *vector);

void PrintTransaction(User *user ,int i);

int main() {

    int sel=0;
    User* user;
    std::vector<std::unique_ptr<User>> contacts;
    std::cout<< "Benvenuto premere 1 per creare un account oppure 2 per uscire "<<std::endl;
    do {
        std::cin >> sel;
    } while (!Checkinput(sel, 1 ,2));
    switch (sel) {
        case 1: {
            user = GenerateAccount();
            CreateAccount(user);
            break;
        }
        case 2:{
            std::cout<< "Exit";
            return 0;
        }
    }
    while(true)
    {
        int scelta=0;
        Operazioni();
        do{
         std::cin>>scelta;
        }while(!Checkinput(scelta,0,9));
        switch(scelta){
            case 1: {
                int importo;
                std::cout<<"Digitare l'importo da prelevare"<<std::endl;
                do {
                    std::cin >> importo;
                }while(!Checkinput(importo,1,650));
                user->Operation(-importo,"Prelievo");
                std::cout<<"Prelievo effettuato!"<<std::endl;
                break;
            }
            case 2:
            {
                int importo;
                std::cout<< "Digitare la somma da versare"<<std::endl;
                do {
                    std::cin >> importo;
                }while(!Checkinput(importo,0,1000));
                user->Operation(importo,"Versamento");
                std::cout<<"Versamento effettuato!"<<std::endl;
                break;
            }
            case 3:
            {
                int balance=user->getAccount()->getBalance();
                std::cout<<"Il saldo attuale è: " <<std::endl;
                std::cout<<balance <<std::endl;
                break;
            }
            case 4:
            {
                Payment(user,& contacts);
                std::cout<<"Pagamento effettuato!"<<std::endl;
                break;
            }
            case 5:
            {
                user->printUser();
                break;
            }
            case 6:
            {
                int sel;
                std::cout<<"Digitare 1 se si vuole visualizzare tutte le operazioni"<<std::endl;
                std::cout<<"Digitare 2 se si vuole vedere le operazioni in uscita"<<std::endl;
                std::cout<<"Digitare 3 se si vuole vedere le operazioni in entrata"<<std::endl;
                std::cin>> sel;
                PrintTransaction(user,sel);
                break;
            }
            case 7:
            {
                tm* Date= CreateDate();
                user->printforDate(Date);
                break;
            }
            case 8:
            {
                std::cout<<"Il report è questo:"<<std::endl;
                user->readReport();
                break;
            }
            case 9:
            {
                user->deleteAccount();
                std::cout<<"eliminazione completata"<<std::endl;
                break;
            }
            case 0:
            {
                std::cout<<"Quitting...";
                return 0;
            }
        }


    }

}

void PrintTransaction(User * user,int i) {
    switch (i) {
        case 1: {
            user->printAllTransaction();
            break;
        }
        case  2: {
            user->printInflowHistory();
            break;
        }
        case 3: {
            user->printOutflowHistory();
            break;
        }

    }
}

void Payment(User *user ,std::vector<std::unique_ptr<User>> *vector) {
    int scelta=0;
    std::unique_ptr<User> tmp;
    std::cout<<"Premi 1 per i contatti in rubrica, premi 2 per un nuovo contatto "<<std::endl;
    do {
        std::cin >> scelta;
    }while(!Checkinput(scelta,1,2));
    switch(scelta){
        case 1:{
            std::string nome;
            std::cout<<"Inserire il nome"<<std::endl;
            std::cin>>nome;
            for(auto &item: *vector)
                if(nome==item->getName())
                    tmp=std::make_unique<User>(item->getName(),item->getAddress(),item->getDateofBirthday());
            std::cout<<"Inserire l'importo da versare"<<std::endl;
            int value;
            std::cin>>value;
            user->OperationtoUser(-value,"Payment", tmp->getAccount());
            break;
        }
        case 2:
        {
            User* tmp= GenerateAccount();
            CreateAccount(tmp);
            int value;
            std::cout<<"Inserire l'importo da versare"<<std::endl;
            std::cin>>value;
            user->OperationtoUser(-value,"Payment",tmp->getAccount());
            break;
        }
    }

}

void CreateAccount(User *pUser) {
        Account* account=new Account(pUser->getName(),pUser->getNamefile(),-10000) ;
        pUser->AddAccount(*account);
}

void Operazioni() {
    std::cout<< "Premere 1 per Prelevare"<<std::endl;
    std::cout<< "Premere 2 per Versare"<<std::endl;
    std::cout<<"Premere 3 per vedere il saldo"<<std::endl;
    std::cout <<"Premere 4 per fare un versamento"<<std::endl;
    std::cout <<"Premere 5 per vedere le informazioni relative all'account" <<std::endl;
    std::cout<< "Premere 6 per vedere le transazioni eseguite"<<std::endl;
    std::cout<<"Premere 7 per cercare una transazione per data"<<std::endl;
    std::cout<< "Premere 8 per leggere il proprio report"<< std::endl;
    std::cout<< "Premere 9 per cancellare l'account "<<std::endl;
    std::cout<< "Premere 0 per uscire "<<std::endl;

}

User * GenerateAccount() {
    std::string nome;
    tm*  datadinascita=new tm;
    std::string indirizzo;

    std::cout<<"inserire il nome utente"<<std::endl;
    std::cin >> nome;
    std::cout<< "Inserire l'indiirizzo di residenza "<<std::endl;
    ws(std::cin);
    getline(std::cin,indirizzo);
    int c=0;
    do{
        if(c!=0)
            std::cout<< "Data invalida, prego riprovare l'inserimento: "<<std::endl;
        std::cout<<"Inserire i dati relativi alla data di nascita"<<std::endl;
        datadinascita=CreateDate();
        c++;

    }while(!CheckDate(datadinascita));
    User * user= new User(nome,indirizzo,datadinascita);
    return user;
}
tm* CreateDate()
{
    tm* res;
    int day;
    std::cout<< "Prego inserire il giorno : "<<std::endl;
    do {
        std::cin >> day;
    }while(!Checkinput(day, 1, 31));
    int month;
    std::cout<<"Prego inserire il mese : "<<std::endl;
    do {
        std::cin >> month;
    }while(!Checkinput(month,1,12));
    int year;
    std::cout<<"Prego inserire l'anno : "<<std::endl;
    std::cin >> year;
    res->tm_mday=day;
    res->tm_mon=month;
    res->tm_year=year;
    return res;
}

bool CheckDate(tm *ptm) {
    time_t data;
    tm* Data;
    data= time(NULL);
    Data= localtime(&data);
    int trentagiorni[]={4,6,9,11};
    int trentunogiorni[] ={1,3,5,7,8,10,12};
    if(1900<=ptm->tm_year && (Data->tm_year+1900)-ptm->tm_year>=18 ) {
        for(int i :trentunogiorni)
        {
            if(ptm->tm_mon==i)
                if(ptm->tm_mday>=1 && ptm->tm_mday<=31)
                    return true;
        }
        for( int i: trentagiorni)
        {
            if(ptm->tm_mon==i)
                if(ptm->tm_mday>=1 && ptm->tm_mday<=30)
                    return true;
        }
        if(ptm->tm_mon==2)
            if(ptm->tm_mday>=1 && ptm->tm_mday<=28)
                return true;
        return false;
    }
    else
        return false;
}

bool Checkinput(int input,int minvalue,int maxvalue) {
    try{
        if(std::cin.good())
        {
            if(input< minvalue)
                throw std::out_of_range("Il valore che hai inserito non è corretto, è più piccolo del valore minimo accettato");
            if(input>maxvalue)
                throw std::out_of_range("Il valore che hai inserito non è corretto, è più grande del valore minimo accettato");

        }
        else
            throw std::out_of_range("Il valore che hai inserito non è corretto");
    }catch(std::out_of_range &e)
    {
        std::cout<< e.what()<<std::endl;
        std::cout<<"Inserire nuovamente il dato:"<<std::endl;
        std::cin.clear();
        return false;
    }
    return true;
}


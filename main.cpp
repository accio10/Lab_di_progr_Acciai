#include <iostream>
#include "Transaction.h"
#include "User.h"
#include "Account.h"
#include <time.h>

User * GenerateAccount();

bool Checkinput(int i, int i1, int i2);

bool CheckDate(tm *pTm);

void Operazioni();

void CreateAccount(User *pUser);

void Payment(User *user, std::vector<std::unique_ptr<User>> *vector);

int main() {

    int scelta=0;
    User* user;
    std::vector<std::unique_ptr<User>> contacts;
    std::cout<< "Benvenuto premere 1 per creare un account oppure 2 per uscire "<<std::endl;
    std::cin >>scelta;
    switch (scelta) {
        case 1: {
            user = GenerateAccount();
            CreateAccount(user);
        }
        case 2:{
            std::cout<< "Exit";
            return 0;
        }
    }
    while(true)
    {
        int scelta;
        Operazioni();
        while(!Checkinput(scelta,0,7));
        switch(scelta){
            case 1: {
                int importo;
                std::cout<<"Digitare l'importo da prelevare"<<std::endl;
                std::cin>>importo;
                while(!Checkinput(importo,1,650));
                user->Operation(-importo,"Prelievo");
            }
            case 2:
            {
                int importo;
                std::cout<< "Digitare la somma da versare"<<std::endl;
                std::cin>>importo;
                while(!Checkinput(importo,0,1000));
                user->Operation(importo,"Versamento");
            }
            case 3:
            {
                Payment(user,& contacts);
            }
        }


    }

}

void Payment(User *user ,std::vector<std::unique_ptr<User>> *vector) {
    int scelta=0;
    std::unique_ptr<User> tmp;
    std::cout<<"Premi 1 per i contatti in rubrica, premi 2 per un nuovo contatto "<<std::endl;
    std::cin>>scelta;
    while(!Checkinput(scelta,1,2));
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
        }
        case 2:
        {

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
    std::cout <<"Premere 3 per fare un versamento"<<std::endl;
    std::cout <<"Premere 4 per vedere le informazioni relative all'account" <<std::endl;
    std::cout<< "Premere 5 per vedere le transazioni eseguite"<<std::endl;
    std::cout<< "Premere 6 per leggere il proprio report"<< std::endl;
    std::cout<< "Premere 7 per cancellare l'account "<<std::endl;
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
        int day;
        std::cout<< "Prego inserire il giorno di naschita: "<<std::endl;
        std::cin>> day;
        while(!Checkinput(day, 1, 31));
        int month;
        std::cout<<"Prego inserire il mese di nascita: "<<std::endl;
        std::cin>>month;
        while(!Checkinput(month,1,12));
        int year;
        std::cout<<"Prego inserire l'anno di nascita: "<<std::endl;
        std::cin >> year;
        datadinascita->tm_mday=day;
        datadinascita->tm_mon=month;
        datadinascita->tm_year=year;
        c++;

    }while(CheckDate(datadinascita));
    User * user= new User(nome,indirizzo,datadinascita);
    return user;
}

bool CheckDate(tm *ptm) {
    tm* Data;
    int trentagiorni[]={4,6,9,11};
    int trentunogiorni[] ={1,3,5,7,8,10,12};
    if(1900<=ptm->tm_year && ptm->tm_year-Data->tm_year>=18 ) {
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
            if(input==0)
                throw std::out_of_range("0 è un valore illegale");
        }
        else
            throw std::out_of_range("Il valore che hai inserito non è corretto");
    }catch(std::out_of_range &e)
    {
        std::cout<< e.what()<<std::endl;
        std::cin.clear();
        return false;
    }
    return true;
}


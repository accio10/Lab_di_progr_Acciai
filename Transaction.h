//
// Created by Nathan on 12/02/2024.
//

#ifndef LAB_DI_PROGR_ACCIAI_TRANSACTION_H
#define LAB_DI_PROGR_ACCIAI_TRANSACTION_H
#include <time.h>

class Transaction{
public:
    Transaction( int v, std::string tpt, std::string sender,std::string causa){
        this->valueoftransaction=v;
        this->sender=sender;
        this->typeoftransaction=tpt;
        this->cause=causa;
        time_t t;
        t=time(nullptr);
        dateTime= ctime(&t);

    }
    Transaction(int value, std::string tpt,std::string sender,std::string causa,tm* set)
    {
        this->valueoftransaction=value;
        this->sender=sender;
        this->typeoftransaction=tpt;
        dateTime= asctime(set);
        this->cause=cause;

    }

    std::string getTypeof() const
    {
        return typeoftransaction;
    }
    std::string getDate()const{
        return dateTime;
    }
    int getValue() const{
        return valueoftransaction;
    }
    std::string getCause()const{
        return cause;
    }
    std::string getSender() const
    {return sender;}

    bool EqualDate(tm *a, tm *b) {
        if(a->tm_year==b->tm_year && a->tm_mon==b->tm_mon &&a->tm_mday==b->tm_mday ) {
            return true;
        }
        else
            return false;
    }


private:
    std::string typeoftransaction;
    std::string dateTime;
    std::string cause;
    int valueoftransaction;
    std::string sender;

};



#endif //LAB_DI_PROGR_ACCIAI_TRANSACTION_H

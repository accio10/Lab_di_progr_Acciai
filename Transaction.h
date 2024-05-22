//
// Created by Nathan on 12/02/2024.
//

#ifndef LAB_DI_PROGR_ACCIAI_TRANSACTION_H
#define LAB_DI_PROGR_ACCIAI_TRANSACTION_H

#include <time.h>
#include <string>

enum TipoTransazioni {
    Inflow, Outflow
};
enum CausaTransazione {
    Prelievo, Versamento, Pagamento, TEST
};

class Transaction {
public:
    Transaction(int v, TipoTransazioni tpt, std::string &sender, CausaTransazione cause) {//booleano oppure enum meglio
        valueoftransaction = v;
        this->sender = sender;
        this->cause = cause;
        this->tpt = tpt;
        time_t now = time(0);
        dateTime = localtime(&now);
        dateTime->tm_mon=dateTime->tm_mon+1;
        dateTime->tm_year=dateTime->tm_year+1900;
    }

    Transaction(int value, TipoTransazioni tpt, std::string &sender, CausaTransazione causa, tm *set) {
        this->valueoftransaction = value;
        this->sender = sender;
        this->tpt = tpt;
        dateTime = set;
        this->cause = cause;

    }

    TipoTransazioni getTypeof() const {
        return tpt;
    }

    tm *getDate() const {
        return dateTime;
    }

    int getValue() const {
        return valueoftransaction;
    }

    CausaTransazione getCause() const {
        return cause;
    }

    std::string getSender() const { return sender; }

    void setDate(tm *date) {
        this->dateTime = date;
    }

    bool EqualDate(tm *a, tm *b) const {
        if (a->tm_year == b->tm_year && a->tm_mon == b->tm_mon && a->tm_mday == b->tm_mday) {
            return true;
        } else
            return false;
    }


private:

    tm *dateTime;
    CausaTransazione cause;
    int valueoftransaction;
    std::string sender;
    TipoTransazioni tpt;
};


#endif //LAB_DI_PROGR_ACCIAI_TRANSACTION_H

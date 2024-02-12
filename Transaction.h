//
// Created by Nathan on 12/02/2024.
//

#ifndef LAB_DI_PROGR_ACCIAI_TRANSACTION_H
#define LAB_DI_PROGR_ACCIAI_TRANSACTION_H
class Transaction{
public:
    explicit Transaction( int v, std::string cause, std::string tpt,std::string Date){
        this->valueoftransaction=v;
        this->typeoftransaction=tpt;
        this->dateTime=Date;
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

private:
    std::string typeoftransaction;
    std::string dateTime;
    std::string cause;
    int valueoftransaction;


};
#endif //LAB_DI_PROGR_ACCIAI_TRANSACTION_H

//
// Created by Nathan on 12/02/2024.
//

#ifndef LAB_DI_PROGR_ACCIAI_TRANSACTION_H
#define LAB_DI_PROGR_ACCIAI_TRANSACTION_H
class Transaction{
public:
    explicit Transaction( int v, std::string tpt, std::string sender,std::string causa,std::string Date){
        this->valueoftransaction=v;
        this->sender=sender;
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
    std::string getSender() const
    {return sender;}

private:
    std::string typeoftransaction;
    std::string dateTime;
    std::string cause;
    int valueoftransaction;
    std::string sender;


};
#endif //LAB_DI_PROGR_ACCIAI_TRANSACTION_H

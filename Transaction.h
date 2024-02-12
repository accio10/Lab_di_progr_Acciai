//
// Created by Nathan on 12/02/2024.
//

#ifndef LAB_DI_PROGR_ACCIAI_TRANSACTION_H
#define LAB_DI_PROGR_ACCIAI_TRANSACTION_H
class Transaction{
public:
    Transaction( int tyf, int v);

    std::string gettypeof()
    {
        return typeoftransaction;
    }
    void settipeof(int tyf){
        this->typeoftransaction=tyf;
    }
    int getvalue()
    {
        return valueoftransaction;
    }
    void setvalue(int v){
        this->valueoftransaction=v;
    }
    std::string getDateTime() const
    {
        return DateTime;
    }

private:
    std::string typeoftransaction;
    std::string DateTime;
    int valueoftransaction;

};
#endif //LAB_DI_PROGR_ACCIAI_TRANSACTION_H

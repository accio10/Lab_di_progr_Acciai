//
// Created by Nathan on 12/02/2024.
//

#ifndef LAB_DI_PROGR_ACCIAI_TRANSACTION_H
#define LAB_DI_PROGR_ACCIAI_TRANSACTION_H
class Transaction{
public:
    Transaction( int tyf, int v);

    int gettypeof()
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

private:
    int typeoftransaction;
    int valueoftransaction;

};
#endif //LAB_DI_PROGR_ACCIAI_TRANSACTION_H

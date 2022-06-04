#ifndef CashIn_h
#define CashIn_h

#include "base.h"

class CashIn : public base {
    int currIncome = 0;
    //сколько денег вносится во время нескольких пополнений. буфер хранилища короче
public:
    CashIn(base *head = nullptr, string name = "", int state = 0,int num = 4) : base(head,name,state,num) {};
    void pointerHandler(base* obj, string& text) {
        if (getState()) {
            base* root = getRoot(this);
            if (root->curStatus=="access") {
                if (text=="return") {
                    currIncome = 0;
                }
                else if (text=="to the card") { //отправляем сигнал с итогой суммой currIncome и зануляем её
                    emit(SIGNAL_DEF(base, pointerSignal),this,root,text="DEP"+to_string(currIncome));//,findObjectByCoord("//Printer", root->pointers), text="DEP"+to_string(currIncome)); //Вывод сообщения о полученной сумме денег
                    currIncome=0;
                }
                else {
                    string summ = text;
                    if (summ=="5000" || summ=="2000" || summ=="1000" || summ=="500" || summ=="100") {
                        currIncome += stoi(summ);
                        string got = "The amount: "+to_string(currIncome);
                        root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord("//Printer", root->pointers), got); //Отправляем сигнал с количеством внесенных на данный момент денег
                    }
                }

            }
        }
    }
};

#endif
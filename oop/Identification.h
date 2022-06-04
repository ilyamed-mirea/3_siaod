#ifndef Identification_h
#define Identification_h

#include "base.h"

class Identification : public base {
public:
    Identification(base *head = nullptr, string name = "", int state = 0,int num = 4) : base(head,name,state,num) {};
    void pointerHandler(base* obj, string& text) {
        if (getState()) {
            string res = "CARDnotok";
            base* root = getRoot(this);
            if (root->curStatus=="ready") {
                for (int i=0;i<root->persons.size();i++) {
                    if (root->persons[i].status == 0 && text == root->persons[i].cardNum) {
                        root->persons[i].status = 1; //карта подтверждена
                        root->curStatus="card_checked";
                        res="CARDok";
                    }
                }
            }
            else if (root->curStatus=="card_checked") {
                res = "PINnotok";
                for (int i = 0; i < root->persons.size(); i++) {
                    if (root->persons[i].status == 1 && text == root->persons[i].PIN) {
                        root->persons[i].status = 2; //пин подтвержден
                        root->curStatus="access"; //теперь можно вводить команды
                        res = "PINok"; //пинок хаха
                        //emit(SIGNAL_DEF(base, pointerSignal),this,root,text = "PINok");
                    }
                }
            }
            emit(SIGNAL_DEF(base, pointerSignal),this,root,res);
        }
    }
};

#endif
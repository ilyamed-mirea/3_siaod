#ifndef Commander_h
#define Commander_h

#include "base.h"

class Commander : public base {
public:
    Commander(base *head = nullptr, string name = "", int state = 0,int num = 2) : base(head,name,state,num) {};
    void pointerHandler(base* obj, string& text) {
        if (!getState()) return;
        if (text == "LOAD_CARDS") {
            string line;
            getline(cin,line);
            if (line=="End card loading") {
                this->emit(SIGNAL_DEF(base, pointerSignal),obj->findObjectByCoord_b("/", obj->objectsB[0]), msg = "LOAD_CARDS"); //загрузка карт
            }
        }
    }
};

#endif
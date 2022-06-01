#ifndef Printer_h
#define Printer_h

#include "base.h"

class Printer : public base {
public:
    Printer(base *head = nullptr, string name = "", int state = 0,int num = 3) : base(head,name,state,num) {};
    void pointerHandler(base* obj, string& text) {
        if (getState())
            cout << endl << "Signal got3333 by " << this->getName() << " Text: " + text + " (class: " + to_string(this->getClass()) + ")";
    }
};

#endif
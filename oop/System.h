#ifndef System_h
#define System_h
#include "base.h"
#include "bonus.h"

class System : public base {
private:
    bonus head;
public:
    System(base* head, string name = "") : base(head, name) {};
    void build_tree_objects() {head.build_tree_b();};
    int exec_app() {	head.configureConnections_b();
        base* root = head.getCurrentElement_b();
        while(root->state==1) { //пока банкомат работает
            string msg = "NEW_COMMAND";
            root->emit(SIGNAL_DEF(base, pointerSignal),root,head.findObject_b("Commander"), msg);
        }
        return 0;};
};

#endif 
#ifndef application_h
#define application_h
#include "base.h"
#include "bonus.h"

class application : public base {
private:
    bonus head;
public:
    application(base* head, string name = "") : base(head, name) {};
    void build_tree_objects() {
        head.build_tree_b();
    }
    int exec_app() {
        head.configureConnections_b();
        head.printTreeReady_b();
        //head.printTreeReady_b();
        return 0;
    }
};

#endif 
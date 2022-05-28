#ifndef application_h
#define application_h
#include "base.h"
#include "bonus.h"

class application : public base {
private:
    bonus head;
public:
    application(base* head, string name = "") : base(head, name) {};
    void build_tree_objects() {head.build_tree_b();};
    int exec_app() {
        head.printTree_b();
        if (head.isHeadNotFound_b() == "ok") {
            //head.getCommands_b();
        }
        head.configureConnections_b();
        //head.printTreeReady_b();
        system("pause");
        return 0;};
};

#endif 
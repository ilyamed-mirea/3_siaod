//
// Created by 0ilya on 27.05.2022.
//

#ifndef SIAOD_APPLICATION_H
#define SIAOD_APPLICATION_H

#include "base.h"
#include "bonus.h"
class application : public base {
private:
    bonus head;
public:
    application(base* head, string name = "") : base(head, name)
    {};
    void build_tree_objects() {
        head.build_tree_b();
    }
    int exec_app() {
        head.printTree_b();
        head.printTreeReady_b();
        cout << endl << endl << endl;
        system("pause"); //del
        return 0;
    }
};

#endif //SIAOD_APPLICATION_H

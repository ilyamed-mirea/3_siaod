//
// Created by 0ilya on 27.05.2022.
//

#ifndef SIAOD_BONUS_H
#define SIAOD_BONUS_H
#include "base.h"
class bonus : public base {
private:
    string fatherName;
    vector<base*> objectsB; // все объекты
    int classNum;
    base* currentEl;
public:
    bonus(bonus* head = nullptr, string name = "") :
            base(head,name) {};
    void build_tree_b();
    void printTree_b();
    base* findObject_b(string name);
    void printTreeReady_b();
};
#include "bonus.cpp"
#endif //SIAOD_BONUS_H

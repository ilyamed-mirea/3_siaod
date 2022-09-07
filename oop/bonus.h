#ifndef bonus_h
#define bonus_h
#include "base.h"

class bonus : public base {
private:
    string fatherName;
    vector<base*> objectsB; // все объекты
    vector<base*> persons; // все люди
    base* currentEl; //текущий элемент
public:
    bonus(bonus* head = nullptr, string name = "") : base(head,name) {};
    void build_tree_b();
    base* findObject_b(string name);
    //void printTreeReady_b();
    //base* findObjectByCoord_b(string coord, base* cur);
    base* getCurrentElement_b();
    void configureConnections_b();
};

#endif
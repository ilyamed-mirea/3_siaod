#ifndef bonus_h
#define bonus_h
#include "base.h"

class bonus : public base {
private:
    string fatherName;
    vector<base*> objectsB; // все объекты
    vector<base*> persons; // все люди
    int classNum;
    base* currentEl; //текущий элемент
    string headNotFound = "ok"; //статус построения дерева удачно/неудачно
public:
    bonus(bonus* head = nullptr, string name = "") : base(head,name) {};
    void build_tree_b();
    void printTree_b();
    base* findObject_b(string name);
    void printTreeReady_b();
    base* findObjectByCoord_b(string coord, base* cur);
    base* getCurrentElement_b();
    void setCurrentElement_b(base *cur);
    void getCommands_b();
    string isHeadNotFound_b();
    void configureConnections_b();
    void pointerHandler(base* obj, string& text);
    void pointerSignal(base* obj, string& text);
};

#endif
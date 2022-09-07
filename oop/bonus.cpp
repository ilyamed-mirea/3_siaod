#include "bonus.h"
#include "System.h"
#include "Commander.h"
#include "Printer.h"
#include "Identification.h"
#include "CashIn.h"
#include "CashOut.h"

void bonus::build_tree_b() {
    int index = 1; // кол-во объектов в objectsB, 1 так как корневой элемент вводится вне цикла
    base *root = new base(nullptr, "base");//создание корневого объекта
    //root->bonusEl = this;
    currentEl = root; //установка корневого объекта текущим (по умолчанию должно быть)
    objectsB.push_back(root); //корневой элемент = нулевой в векторе
    base *obj = nullptr;
    for (int i = 1; i <= 6; i++) {
        switch(i) {
            case 1:
                obj = new System(root, "System");
                break;
            case 2:
                obj = new Commander(root, "Commander");
                break;
            case 3:
                obj = new Printer(root, "Printer");
                break;
            case 4:
                obj = new Identification(root, "Identification");
                break;
            case 5:
                obj = new CashIn(root, "CashIn");
                break;
            case 6:
                obj = new CashOut(root, "CashOut");
                break;
        }
        objectsB.push_back(obj); //добавляем новый объект в иерархию
        objectsB[index]->changeHead(root); //установка головного элемента созданного объекта
        index++;
    }
}

base* bonus::findObject_b(string name) {
    return objectsB[0]->findObject(name,objectsB,objectsB[0]); //найти объект, начало от корневого
}
/*
base* bonus::findObjectByCoord_b(string coord, base* cur) {
	return cur->findObjectByCoord(coord,objectsB); //найти объект по координатам относительно cur
}
*/
base* bonus::getCurrentElement_b() {
    return currentEl;
}
void bonus::configureConnections_b() {
    for (int i = 0; i < objectsB.size(); i++) {
        objectsB[i]->setState(1); //привести все объекты в состояние готовности
    }
    string from,to,command,msg;
    base* root = objectsB[0];
    for (int i = 2; i < objectsB.size();i++) {
        base* objTo = findObject_b(objectsB[i]->getName());
        root->setConnection(SIGNAL_DEF(base, pointerSignal), root, objTo, HANDLER_DEF(base, pointerHandler));
    }
    //root->setConnection(SIGNAL_DEF(base, pointerSignal), findObjectByCoord_b("//Commander", root), findObjectByCoord_b("//Identification", root), HANDLER_DEF(base, pointerHandler));

    //findObjectByCoord_b("//Commander", objectsB[0])->setConnection(SIGNAL_DEF(base, pointerSignal), objFrom, HANDLER_DEF(base, pointerHandler));
    root->emit(SIGNAL_DEF(base, pointerSignal),root,findObject_b("Commander"), msg = "INIT_CARD"); //загрузка карт
    root->emit(SIGNAL_DEF(base, pointerSignal),root,findObject_b("Commander"), msg = "INIT_MONEY"); //загрузка денег
    root->curStatus = "ready"; //установка банкомата в состояние готовности!!

    /*while(root->state==1) { //пока банкомат работает
        root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord_b("//Commander", root), msg = "NEW_CLIENT");
    }*/


    /*
    cin >> command;
    while (command != "END") {
        cin >> from;
        objFrom = findObjectByCoord_b(from, objectsB[0]);
        if (objFrom == nullptr) { //если не найден объект по координате
            cout << endl << "Object " << from << " not found";
        }
        if (command=="SET_CONNECT" || command=="DELETE_CONNECT") {
            cin >> to;
            objTo = findObjectByCoord_b(to, objectsB[0]);
            if (objTo == nullptr) { //если не найден целевой объект
                cout << endl << "Handler object " << to << " not found";
            }
            else if (command=="SET_CONNECT" && objFrom!=nullptr)
                objFrom->setConnection(SIGNAL_DEF(base, pointerSignal), objTo, HANDLER_DEF(base, pointerHandler));
            else if (objFrom!=nullptr)
                objFrom->deleteConnection(SIGNAL_DEF(base, pointerSignal), objTo, HANDLER_DEF(base, pointerHandler));
        }
        else if (command == "EMIT")  {
            getline(cin, msg);
            if (objFrom!=nullptr) {
                objFrom->emit(SIGNAL_DEF(base, pointerSignal), msg);
            }
        }
        else if (command == "SET_CONDITION") {
            cin >> newCondition;
            if (objFrom!=nullptr) {
                objFrom->setState(newCondition);
            }
        }
        cin >> command;
    } */
}
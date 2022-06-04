#include "bonus.h"
#include "Commander.h"
#include "Printer.h"
#include "Identification.h"
#include "CashIn.h"
#include "CashOut.h"

void bonus::build_tree_b() {
    int index = 1; // кол-во объектов в objectsB, 1 так как корневой элемент вводится вне цикла
    int i = 0; // просто итератор
    base *root = new base(nullptr, "base");//создание корневого объекта
    root->bonusEl = this;
    setCurrentElement_b(root); //установка корневого объекта текущим (по умолчанию должно быть)
    objectsB.push_back(root); //корневой элемент = нулевой
    base *obj = nullptr;
    for (classNum = 2; classNum <= 6; classNum++) {
        switch(classNum) {
            case 1: //
                obj = this;//new base(root, name);
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

void bonus::printTree_b() {
    cout << "Object tree" << endl;
    objectsB[0]->printTree(); //вывод дерева(рекурсивный)
    objectsB[0]->clearPrinted(); //поставить у всех элементов printed=false
    if (isHeadNotFound_b() != "ok") { //если при построении дерева произошла ошибка
        cout << endl << "The head object " << headNotFound << " is not found";
    }
}

void bonus::printTreeReady_b() {
    cout << endl << "The tree of objects and their readiness" << endl;
    objectsB[0]->printTreeReady(); //вывод дерева с состояниями(рекурсивный)
    objectsB[0]->clearPrinted();
}

base* bonus::findObject_b(string name) {
    return objectsB[0]->findObject(name,objectsB,objectsB[0]); //найти объект, начало от корневого
}

base* bonus::findObjectByCoord_b(string coord, base* cur) {
    return cur->findObjectByCoord(coord,objectsB); //найти объект по координатам относительно cur
}

base* bonus::getCurrentElement_b() {
    return currentEl;
}

void bonus::setCurrentElement_b(base *cur) {
    this->currentEl = cur;
}

void bonus::getCommands_b() {
    string command,coord,line;
    while (true) {
        command = "";
        coord = "";
        int i = 0;
        getline(cin,line);
        while (i<line.length() && line[i]!=' ') { //считывание комманды
            command += line[i];
            i++;
        }
        if (command == "END") //выход если было введено END
            break;
        i++; //пробуск пробела
        for (;i<line.length();i++) {
            coord += line[i];
        }
        cout << endl;
        base *found;
        if (command == "SET") {
            found = findObjectByCoord_b(coord, getCurrentElement_b()); //находим введенный объект, ища от корневого old:getRoot(getCurrentElement_b())
            if (found == nullptr) { //если объект не нашелся
                cout << "Object is not found: " << getCurrentElement_b()->getName() << " " << coord;
            }
            else {
                setCurrentElement_b(found); //установка нового текущего объекта
                cout << "Object is set: " << getCurrentElement_b()->getName(); //вывод нового
            }
        } else if (command == "FIND") {
            found = findObjectByCoord_b(coord, getCurrentElement_b()); //поиск объекта
            if (found == nullptr) { //если объект не нашелся
                cout << coord << "     Object is not found";
            }
            else {
                cout << coord << "     Object name: " << found->getName(); //вывод найденного объекта
            }
        }
    }
}
string bonus::isHeadNotFound_b() {
    return headNotFound;
}
void bonus::pointerHandler(base* obj, string& text) {
    cout << endl << "bonusback " << text << obj->getName() << endl;
}
void bonus::pointerSignal(base* obj, string& text) {
    cout << endl << "siganlbonusback " << text << obj->getName() << endl;
}
void bonus::configureConnections_b() {
    for (int i = 0; i < objectsB.size(); i++) {
        objectsB[i]->setState(1); //привести все объекты в состояние готовности
    }
    string from,to,command,msg;
    base* root = objectsB[0];
    for (int i = 1; i < objectsB.size();i++) {
        base* objTo = findObjectByCoord_b("//"+objectsB[i]->getName(), root);
        root->setConnection(SIGNAL_DEF(base, pointerSignal), root, objTo, HANDLER_DEF(base, pointerHandler));
    }
    //root->setConnection(SIGNAL_DEF(base, pointerSignal), findObjectByCoord_b("//Commander", root), findObjectByCoord_b("//Identification", root), HANDLER_DEF(base, pointerHandler));

    //findObjectByCoord_b("//Commander", objectsB[0])->setConnection(SIGNAL_DEF(base, pointerSignal), objFrom, HANDLER_DEF(base, pointerHandler));
    root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord_b("//Commander", root), msg = "INIT_CARD"); //загрузка карт
    root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord_b("//Commander", root), msg = "INIT_MONEY"); //загрузка денег
    root->curStatus = "ready"; //установка банкомата в состояние готовности!!

    /*while(root->state==1) { //пока банкомат работает
        root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord_b("//Commander", root), msg = "NEW_CLIENT");
    }*/



    //objFrom->emit(SIGNAL_DEF(base, pointerSignal),findObjectByCoord_b("//Printer", objectsB[0]), msg = "READY"); //вывод сообщения об удачной загрузке карт

    //objFrom->emit(SIGNAL_DEF(base, pointerSignal), msg);
    /*
    int newCondition;
    cin >> from;
    while (from != "end_of_connections") {
        cin >> to;
        objFrom = findObjectByCoord_b(from, objectsB[0]);
        objTo = findObjectByCoord_b(to, objectsB[0]);
        if (objFrom == nullptr) { //если не найден объект по координате
            cout << endl << "Object " << from << " not found";
        }
        if (objTo == nullptr) { //если не найден целевой объект
            cout << endl << "Handler object " << to << " not found";
        }
        if (objFrom == nullptr || objTo == nullptr) //если не найден какой-то объект, не выполнять операцию
            continue;
        else {
            objFrom->setConnection(SIGNAL_DEF(base, pointerSignal), objTo, HANDLER_DEF(base, pointerHandler));
        }
        cin >> from;
    }
    for (int i = 0; i < objectsB.size(); i++) {
        objectsB[i]->setState(1); //привести все объекты в состояние готовности
    }

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
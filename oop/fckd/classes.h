//
// Created by 0ilya on 27.05.2022.
//

#ifndef SIAOD_CLASSES_H
#define SIAOD_CLASSES_H
//#include "base.h"

#include <string>
#include <vector>
#include <iostream>
#include "base.h"

using namespace std;

class System; // Объект «система».
class Commander; //Объект для чтения команд и данных. Считывает данные для подготовки и настройки банкомата. После чтения очередной порции данных для настройки или данных команды, объект выдает сигнал с текстом полученных данных. Все данные настройки и данные команды синтаксический корректны.
class RemoteControl; //Объект пульта управления, для отработки нажатия кнопок (команд). Объект после нажатия кнопки анализирует возможность его выполнения и выдает соответствующий сигнал. Выдает сигнал если запрошенная для снятия сумма не кратна 100 или на карте нет достаточных средств.
class Identification; //Объект, моделирующий устройства идентификации банковской карты. Выдает сигнал, содержащий текст результата идентификации
class CashReceiver; //Объект, моделирующий устройства приема денег. После принятия очередной купюры сохраняет его. При внесении денег подряд производит суммирование. Выдает сигнал, содержащий сумму введенных денег для отображения на экран.
class CashGiver; //Объект, моделирующий устройства выдачи денег. Выдает сигнал, содержащий количество купюр возвращаемой суммы или информацию о невозможности получить необходимый состав купюр.
class Printer;//Объект для вывода состояния или результата операции банкомата на консоль
class Person;
/*
void base::setConnection(void (base::*pointerSignal)(string&), base* objHandler, void(base::*pointerHandler)(base*, string&)) {
    for (int i = 0; i < connections.size(); i++) {
        if (connections[i].pointerSignal == pointerSignal && connections[i].objConnection == objHandler && connections[i].pointerHandler == pointerHandler) {
            return;
        }
    }
    connections.push_back(connect{pointerSignal,objHandler,pointerHandler});
}*/



class Commander : public Base {
private:
    //string fatherName;
    //int classNum = 1;
    //base* currentEl; //текущий элемент
    int state = 0;
    string className = "commander";
public:
    Commander() : Base() {};
    void printTree_b();
    System* findObject_b(string name);
    void printTreeReady_b();
    System* findObjectByCoord_b(string coord, System* cur);
    System* getCurrentElement_b();
    void setCurrentElement_b(System *cur);
    void getCommands_b();
    string isHeadNotFound_b();
    void configureConnections_b();
    void setState(int newState) {
        state = newState;
    };
    int getState() {
        return state;
    };
    string getClass() {
        return className;
    };
    void handler(string x) {
        cout << "hand " << x << endl;
    }
};

//#include "bonus.cpp"

class RemoteControl : public Base {
private:
    int state = 0;
    string className = "controller";
public:
    RemoteControl() : Base() {};
    void setState(int newState) {
        state = newState;
    };
    int getState() {
        return state;
    };
    string getClass() {
        return className;
    };
};

class Identification : public Base {
private:
    int state = 0;
    string className = "ident";
public:
    Identification() : Base() {};
    void setState(int newState) {
        state = newState;
    };
    int getState() {
        return state;
    };
    string getClass() {
        return className;
    };
};

class CashReceiver: public Base {
private:
    int state = 0;
    string className = "cashget";
public:
    CashReceiver() : Base() {};
    void setState(int newState) {
        state = newState;
    };
    int getState() {
        return state;
    };
    string getClass() {
        return className;
    };
};

class CashGiver: public Base {
private:
    int state = 0;
    string className = "cashgive";
public:
    CashGiver() : Base() {};
    void setState(int newState) {
        state = newState;
    };
    int getState() {
        return state;
    };
    string getClass() {
        return className;
    };
};

class Printer: public Base {
private:
    int state = 0;
    string className = "printer";
public:
    Printer() : Base() {};
    void setState(int newState) {
        state = newState;
    };
    int getState() {
        return state;
    };
    string getClass() {
        return className;
    };
};
class Person: public Base {
private:
    int cardNum;
    int PIN;
    int amount;
public:
    Person() : Base() {};
};

class System : public Base {
private:
    Base base;
    Commander commander;
    RemoteControl controller;
    Identification ident;
    CashReceiver cashget;
    CashGiver cashgive;
    Printer printer;
    vector<Person*> users; // все объекты
    string headNotFound = "ok"; //статус построения дерева удачно/неудачно
    int state = 1;
    string className = "system";
public:
    System() : Base() {};

    void on() {
        commander.setState(1);
        controller.setState(1);
        ident.setState(1);
        cashget.setState(1);
        cashgive.setState(1);
        printer.setState(1);
    }
    void off() {
        commander.setState(0);
        controller.setState(0);
        ident.setState(0);
        cashget.setState(0);
        cashgive.setState(0);
        printer.setState(0);
    }
    void build_tree_objects() {
        //построение дерева
        base.tree.push_back(&base); //root
        base.tree.push_back(this);
        base.tree.push_back(&commander);
        base.tree.push_back(&controller);
        base.tree.push_back(&ident);
        base.tree.push_back(&cashget);
        base.tree.push_back(&cashgive);
        on();
        base.setConnection(SIGNAL_DEF(Base, pointerSignal), &commander, HANDLER_DEF(Base, pointerHandler));
        base.setConnection(SIGNAL_DEF(Base, pointerSignal), &controller, HANDLER_DEF(Base, pointerHandler));
        base.setConnection(SIGNAL_DEF(Base, pointerSignal), &ident, HANDLER_DEF(Base, pointerHandler));
        base.setConnection(SIGNAL_DEF(Base, pointerSignal), &cashget, HANDLER_DEF(Base, pointerHandler));
        base.setConnection(SIGNAL_DEF(Base, pointerSignal), &cashgive, HANDLER_DEF(Base, pointerHandler));
        //string msg = "mmeessaaggee";
        //this->emit(SIGNAL_DEF(Base, pointerSignal), msg);
        //connections.push_back(connect{SIGNAL_DEF(Base, pointerSignal),obj, HANDLER_DEF(Base, pointerHandler)});
        //connections.push_back(connect{});
    };
    void printTree() { //вывод дерева
        string otstup = "    ";
        cout << base.getClass() << base.getState();
        for (int i = 1;i<tree.size();i++) {
            cout << otstup << tree[i]->getClass() << tree[i]->getState();
        }
    }
    int exec_app() {
        //head.printTree_b();
        //if (commander.isHeadNotFound_b() == "ok") {
        //head.getCommands_b();
        //}
        //head.printTreeReady_b();
        system("pause");
        return 0;
    };
    int getState() {
        return state;
    };
    string getClass() {
        return className;
    };
};

#endif //SIAOD_CLASSES_H

//
// Created by 0ilya on 27.05.2022.
//

#ifndef SIAOD_BASE_H
#define SIAOD_BASE_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;
class base;
//using structSignal = void(base::*)(string&);
//using structHandler = void(base::*)(string);
typedef void(base::*structSignal)(string&);
typedef void(base::*structHandler)(string);
//параметризованные макроопределения предпроцессора:
#define SIGNAL_D(signal_f) ((structSignal)(signal_f)) //
#define HANDLER_D(handler_f) ((structHandler)(handler_f)) //
/*
// structSignal = (void(S::*) (string&))
#define SIGNAL_D(S, signal_f) ( (void(S::*) (string&)) (&S::signal_f)) //дляполучения указателя на метод сигнала
#define HANDLER_D(H, hendler_f) ((void(H::*) (base*, string&))(&H::hendler_f)) //для получения указателя на метод обработчика
*/
class base {
public:
    string name; //имя объекта
    base *father; //указатель на родителя
    vector<base*> pointers; //дети
    bool printed; //индикатор того, что элемент был выведен
    int state; //состояние
    int classNum; //номер класса, с помощью которого создан
    struct connect {
        structSignal signalConnection;
        base* objConnection;
        structHandler handlerConnection;
    };
    vector<connect> connections;
    bool readyToConnect = 1;

    base(base *head = nullptr, string name = "", int state = 0,
         int newClassNum = 0) {
        setName(name);
        setHead(head);
        setState(state);
        setClass(newClassNum);
    };
    void setName(string name);
    string getName();
    void printTree(int otstupColv = 0);
    void setHead(base *head);
    void changeHead(base *head);
    base* findObject(string name);
    void printTreeReady(int otstupColv = 0);
    int getState();
    void setState(int newState);
    void setClass(int num);
    int getClass();
    void clearPrinted();
    base* findObjectByCoord(string coord);
    base* getRoot(base *obj);
    void handler(string signStr) {
        cout << endl << "Signal to " << getName() <<" Text: " << signStr << endl;
    }
    void signal(string *signStr) {
        *signStr += " (class: " + to_string(getClass()) + ")";
        cout << "\nSignal from " << getName() << endl;
    }
    void setConnection(structSignal newStructSignal, base* newObjConnection, structHandler newStructHandler);
    void deleteConnection(structSignal newStructSignal, base* newObjConnection, structHandler newStructHandler);
    void emitSignal(structSignal emitter, string command);
    base* getHead(base *head);
    void setCondition(int newCondition);
    structSignal recognitionSignal(){
        return SIGNAL_D(base::signal);
    }
    structHandler recognitionHandler(){
        return HANDLER_D(base::handler);
    }
};

#include "base.cpp"
#endif //SIAOD_BASE_H

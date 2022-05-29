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
#define SIGNAL_DEF(S, signalFunc) ((void(S::*) (string&))(&S::signalFunc)) //получение указателя на метод сигнала
#define HANDLER_DEF(H, handlerFunc) ((void(H::*) (base*, string&))(&H::handlerFunc)) // получение уакзателя на метод обработчика

class base {
public:
    string name; //имя объекта
    base *father; //указатель на родителя
    vector<base*> pointers; //дети
    bool printed; //индикатор того, что элемент был выведен
    int state; //состояние
    int classNum; //номер класса, с помощью которого создан
    struct connect {
        void (base::*pointerSignal)(string&);
        base* objConnection;
        void (base::*pointerHandler)(base* pointerObj, string&);
    };
    vector<connect> connections;

    base(base *head = nullptr, string name = "", int state = 0, int newClassNum = 1) {
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
    string getObjectCoord();
    void setConnection(void (base::*pointerSignal)(string&), base* objHandler, void(base::*pointerHandler)(base*, string&));
    void deleteConnection(void (base::*pointerSignal)(string&), base* objHandler, void(base::*pointerHandler)(base*, string&));
    void emit(void(base::*pointerSignal)(string&), string& command);
    void pointerSignal(string& text);
    void pointerHandler(base* obj, string& text);
};

#include "base.cpp"
#endif //SIAOD_BASE_H

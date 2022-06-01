#ifndef SIAOD_BASE_H
#define SIAOD_BASE_H

#define SIGNAL_DEF(S, signalFunc) ( (void(S::*) (string&)) (&S::signalFunc) ) //получение указателя на метод сигнала
#define HANDLER_DEF(H, handlerFunc) ( (void(H::*) (Base*, string&)) (&H::handlerFunc) ) // получение уакзателя на метод обработчика
//#define SIGNAL_DEF(S, signalFunc) ( (void(S::*) (string&)) (signalFunc) ) //получение указателя на метод сигнала
//#define HANDLER_DEF(H, handlerFunc) ( (void(H::*) (Base*, string&)) (handlerFunc) ) // получение уакзателя на метод обработчика
#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Base {
public:
    int state; //состояние
    string className = "base";
    struct connect {
        void (Base::*pointerSignal)(string&);
        Base* objConnection;
        void (Base::*pointerHandler)(Base* pointerObj, string&);
    };
    vector<Base*> tree; // иерархия
    vector<connect> connections;

    Base(Base *head = nullptr, string name = "", int state = 0) {
        //this->name = name;
        //setName(name);
        //setHead(head);
        //setState(state);
    };
    void pointerSignal(string& text) {
        cout << endl << "Signal from " << text;
    };
    void pointerHandler(Base* obj, string& text) {
        //if (getState())
            cout << endl << "Signal pointerhandler; Text: " + text + " (class: "; //+ to_string(obj->getClass()) + ")";
        string msg = "mmeessaaggee 2";
        obj->emit(SIGNAL_DEF(Base, pointerSignal), msg); //recursion
    };
    void setConnection(void (Base::*pointerSignal)(string&), Base* objHandler, void(Base::*pointerHandler)(Base*, string&)) {
        for (int i = 0; i < connections.size(); i++) {
            if (connections[i].pointerSignal == pointerSignal && connections[i].objConnection == objHandler && connections[i].pointerHandler == pointerHandler) {
                return;
            }
        }
        connections.push_back(connect{pointerSignal,objHandler,pointerHandler});
    };
    void emit(void(Base::*pointerSignal)(string&), string& command) {
        if (!getState())
            return;
        (this->*pointerSignal)(command);
        for (int i = 0; i < connections.size(); i++) {
            if (connections[i].pointerSignal == pointerSignal) {
                void (Base::*pointerHandler)(Base*, string&);
                pointerHandler = connections[i].pointerHandler;
                (connections[i].objConnection->*pointerHandler)(this,command);
            }
        }
    }
    void printTreeReady(int otstupColv = 0);
    Base* findObjectByCoord(string coord);
    Base* getRoot(Base *obj);
    string getObjectCoord();
    virtual void setState(int newState) {
        this->state = newState;
    };
    virtual int getState() {
        return state;
    };
    virtual string getClass() {
        return className;
    };
    virtual void handler(string x);
};

//#include "base.cpp"
#endif //SIAOD_BASE_H

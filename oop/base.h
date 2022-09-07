#ifndef base_h
#define base_h

#include <string>
#include <vector>
#include <iostream>

using namespace std;

#define SIGNAL_DEF(S, signalFunc) ((void(S::*) (string&))(&S::signalFunc)) //получение указателя на метод сигнала
#define HANDLER_DEF(H, handlerFunc) ((void(H::*) (base*, string&))(&H::handlerFunc)) // получение уакзателя на метод обработчика

struct Person {
    string cardNum;
    string PIN;
    int amount;
    int status;
    Person(string cardNum, string PIN ,int amount) {
        this->cardNum=cardNum;
        this->PIN=PIN;
        this->amount=amount;
        status=0; //0-не идентифицрован, 1 - подтвержден номер карты, 2 - подтвержден пин
    }
};

class base {
private:
    string name; //имя объекта
    base *father; //указатель на родителя
    int depositing = 0; //производится ли внесение средств
public:
    string curStatus = "off"; //текущий статус работы банкомата, в головном элементе
    vector<Person> persons; // зарегистрированные люди, в головном
    vector<int> money; //количество денег [0]=5000,[1]=2000,[2]=1000,[3]=500,[4]=100
    //off - ready - card_checked - access - ready...
    vector<base*> pointers; //дети
    int state; //состояние

    struct connect {
        void (base::*pointerSignal)(string&);
        base* objFrom;
        base* objTo;
        void (base::*pointerHandler)(base* pointerObj, string&);
    };
    vector<connect> connections;

    base(base *head = nullptr, string name = "", int state = 0) {
        setName(name);
        father=head;
        setState(state);
    };
    void setName(string name);
    string getName();
    void changeHead(base *head);
    base* findObject(string name, vector<base*> objectsB, base* parent);
    void printTreeReady();
    int getState();
    void setState(int newState);
    //virtual base* findObjectByCoord(string coord, vector<base*> objectsB);
    base* getRoot(base *obj);
    void setConnection(void (base::*pointerSignal)(string&), base* objFrom, base* objTo, void(base::*pointerHandler)(base*, string&));
    virtual void emit(void(base::*pointerSignal)(string&), base *objFrom, base *objTo, string& command);
    virtual void pointerSignal(base* obj, string& text);
    virtual void pointerHandler(base* obj, string& text) {};
};

#endif
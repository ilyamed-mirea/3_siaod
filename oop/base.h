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
public:
    string name; //имя объекта
    base *father; //указатель на родителя
    base *bonusEl; //указатель на бонус.... что бы из классов был доступ
    vector<base*> pointers; //дети
    bool printed; //индикатор того, что элемент был выведен
    int state; //состояние
    int classNum; //номер класса, с помощью которого создан
    vector<base*> objectsB; //чисто для bonus
    vector<Person> persons; // зарегистрированные люди, в головном
    vector<int> money; //количество [0]=5000,[1]=2000,[2]=1000,[3]=500,[4]=100
    string curStatus = "off"; //текущий статус банкомата, в головном элементе
    //off - ready - card_checked - access - ready...
    int depositing = 0; //производится ли внесение средств
    struct connect {
        void (base::*pointerSignal)(string&);
        //base* objConnection;
        base* objFrom;
        base* objTo;
        void (base::*pointerHandler)(base* pointerObj, string&);
    };
    vector<connect> connections;

    base(base *head = nullptr, string name = "", int state = 0, int newClassNum = 1) {
        setName(name);
        setHead(head);
        setState(state);
        setClass(newClassNum);
    }; //! CHEWCK GETSTATE у каждого свой л стейт
    void setName(string name);
    string getName();
    void printTree(int otstupColv = 0);
    void setHead(base *head);
    void changeHead(base *head);
    base* findObject(string name, vector<base*> objectsB, base* parent);
    void printTreeReady(int otstupColv = 0);
    int getState();
    void setState(int newState);
    void setClass(int num);
    int getClass();
    void clearPrinted();
    virtual base* findObjectByCoord(string coord, vector<base*> objectsB);
    base* getRoot(base *obj);
    string getObjectCoord();
    void setConnection(void (base::*pointerSignal)(string&), base* objFrom, base* objTo, void(base::*pointerHandler)(base*, string&));
    void deleteConnection(void (base::*pointerSignal)(string&), base* objFrom, base* objTo, void(base::*pointerHandler)(base*, string&));
    //void emit(void(base::*pointerSignal)(string&), string& command);
    void emit(void(base::*pointerSignal)(string&), base *objFrom, base *objTo, string& command);
    void pointerSignal(base* obj, string& text);
    void pointerHandler(base* obj, string& text);

    //virtual base* findObjectByCoord_b(string coord, base* cur);
};

#endif
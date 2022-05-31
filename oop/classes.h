//
// Created by 0ilya on 27.05.2022.
//

#ifndef SIAOD_CLASSES_H
#define SIAOD_CLASSES_H
#include "base.h"
#include "bonus.h"
class System; // Объект «система».
class Commander; //Объект для чтения команд и данных. Считывает данные для подготовки и настройки банкомата. После чтения очередной порции данных для настройки или данных команды, объект выдает сигнал с текстом полученных данных. Все данные настройки и данные команды синтаксический корректны.
class RemoteControl; //Объект пульта управления, для отработки нажатия кнопок (команд). Объект после нажатия кнопки анализирует возможность его выполнения и выдает соответствующий сигнал. Выдает сигнал если запрошенная для снятия сумма не кратна 100 или на карте нет достаточных средств.
class Identification; //Объект, моделирующий устройства идентификации банковской карты. Выдает сигнал, содержащий текст результата идентификации
class CashReceiver; //Объект, моделирующий устройства приема денег. После принятия очередной купюры сохраняет его. При внесении денег подряд производит суммирование. Выдает сигнал, содержащий сумму введенных денег для отображения на экран.
class CashGiver; //Объект, моделирующий устройства выдачи денег. Выдает сигнал, содержащий количество купюр возвращаемой суммы или информацию о невозможности получить необходимый состав купюр.
class Printer;//Объект для вывода состояния или результата операции банкомата на консоль
/*
void base::setConnection(void (base::*pointerSignal)(string&), base* objHandler, void(base::*pointerHandler)(base*, string&)) {
    for (int i = 0; i < connections.size(); i++) {
        if (connections[i].pointerSignal == pointerSignal && connections[i].objConnection == objHandler && connections[i].pointerHandler == pointerHandler) {
            return;
        }
    }
    connections.push_back(connect{pointerSignal,objHandler,pointerHandler});
}*/

class System : public base {
private:
    Commander commander;
    RemoteControl controller;
    Identification ident;
    CashReceiver cashget;
    CashGiver cashgive;
    vector<base*> users; // все объекты
    struct connect {
        void (System::*pointerSignal)(string&);
        base* objConnection;
        void (System::*pointerHandler)(System* pointerObj, string&);
    };
    vector<connect> connections;
public:
    System(base* head = nullptr, string name = "") : base(head, name) {};
    void build_tree_objects() {
        commander.build_tree_b();

        void (base::*pointerSignal)(string&), base* objHandler, void(base::*pointerHandler)(base*, string&)
        connections.push_back(connect{pointerSignal,objHandler,pointerHandler});
    };
    int exec_app() {
        //head.printTree_b();
        commander.configureConnections_b();
        if (commander.isHeadNotFound_b() == "ok") {
            //head.getCommands_b();
        }
        //head.printTreeReady_b();
        system("pause");
        return 0;
    };
};


class Commander : public base {
private:
    string fatherName;
    int classNum;
    base* currentEl; //текущий элемент
    string headNotFound = "ok"; //статус построения дерева удачно/неудачно
public:
    Commander(Commander* head = nullptr, string name = "") : base(head,name) {};
    void build_tree_b() {
            int i = 0; // просто итератор
            string cardNum, str; //line - полученная строка, coord - координата/путь
            int cardPin, summ;
            while (true) { //ввод дерева
                cardNum = "";
                for (int i = 0; i < 3; i++) {
                    cin >> str;
                    cardNum += str;
                }
                if (cardNum == "End card loading")
                    break;
                cin >> str; cardNum+=str;
                cin >> cardPin >> summ;
                base *client = new base(cardNum, cardPin, summ);
                i = 0;
                base *foundParent = findObjectByCoord_b(coord, getCurrentElement_b());
                if (foundParent == nullptr) { //если произошла ошибка определения головного объекта
                    headNotFound = coord; //сохранение ошибочной координаты
                    break;
                }
                i++; // пропуск пробела
                while(line[i] != ' ') { //считывание имени нового объекта
                    name+=line[i];
                    i++;
                }
                i++; // пропуск пробела
                classNum = int(line[i]-'0'); //считывание номера класса
                switch(classNum) {
                    case 1:
                        obj = new base(foundParent, name);
                        break;
                    case 2:
                        obj = new cl_2(foundParent, name); //objectsB[k]
                        break;
                    case 3:
                        obj = new cl_3(foundParent, name);
                        break;
                    case 4:
                        obj = new cl_4(foundParent, name);
                        break;
                    case 5:
                        obj = new cl_5(foundParent, name);
                        break;
                    case 6:
                        obj = new cl_6(foundParent, name);
                        break;
                    default:
                        //obj = new base(foundParent, name);
                        cout << "error classNum" << endl;
                        break;
                }
                objectsB.push_back(obj); //добавляем новый объект в иерархию
                objectsB[index]->changeHead(foundParent); //установка головного элемента созданного объекта
                index++;
            }
            /*while (cin >> name >> state) { //ввод состояний
                base* obj = findObject_b(name); //находим объект
                if (obj!=nullptr) {
                    obj->setState(state); //устанавливаем ему состояние
                }
            }*/

    };
    void printTree_b();
    base* findObject_b(string name);
    void printTreeReady_b();
    base* findObjectByCoord_b(string coord, base* cur);
    base* getCurrentElement_b();
    void setCurrentElement_b(base *cur);
    void getCommands_b();
    string isHeadNotFound_b();
    void configureConnections_b();
};

#include "bonus.cpp"

class RemoteControl : public base {
public:
    RemoteControl(base *head = nullptr, string name = "", int state = 0,int num =
    2) : base(head,name,state,num) {};
};
class Identification : public base {
public:
    Identification(base *head = nullptr, string name = "", int state = 0,int num =
    3) : base(head,name,state,num) {};
};
class CashReceiver: public base {
public:
    CashReceiver(base *head = nullptr, string name = "", int state = 0,int num =
    4) : base(head,name,state,num) {};
};
class CashGiver: public base {
public:
    CashGiver(base *head = nullptr, string name = "", int state = 0,int num =
    5) : base(head,name,state,num) {};
};
class Printer: public base {
public:
    CashGiver(base *head = nullptr, string name = "", int state = 0,int num =
    5) : base(head,name,state,num) {};
};
#endif //SIAOD_CLASSES_H

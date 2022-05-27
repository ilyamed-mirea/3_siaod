//
// Created by 0ilya on 27.05.2022.
//

#ifndef SIAOD_BASE_H
#define SIAOD_BASE_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class base {
public:
    string name; //имя объекта
    base *father; //указатель на родителя
    vector<base*> pointers; //дети
    bool printed; //индикатор того, что элемент был выведен
    int state; //состояние
    int classNum; //номер класса, с помощью которого создан
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
};

#include "base.cpp"
#endif //SIAOD_BASE_H

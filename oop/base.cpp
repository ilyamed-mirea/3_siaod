#include "base.h"
void base::setName(string name) {
    this->name = name;
}
string base::getName() {
    return name;
}
void base::printTree(int otstupColv) { //вывод дерева
    if (!printed) { //если элемент еще не выводился
        if (otstupColv!=0) {
            cout << endl; // перенос строки от предыдущей
        }
        string otstup = " ";
        for (int i = 0; i < otstupColv; i++) {
            cout << otstup; // вывод нужного количества отступов
        }
        cout << name;// << " " << getClass() вывод имени текущего объекта
                printed = true; // помечаем что уже выводили этот объект
        if (pointers.size()>0) {
            for (int i = 0; i < pointers.size(); i++) { //вывод его детей с увелич. отступом
                pointers[i]->printTree(otstupColv+1);
            }
        }
    }
}
void base::printTreeReady(int otstupColv) { //вывод дерева готовности
    if (!printed) {
        if (otstupColv!=0) {
            cout << endl;
        }
        string otstup = " ";
        for (int i = 0; i < otstupColv; i++) {
            cout << otstup;
        }
        cout << name << ((getState() != 0) ? " is ready" : " is not ready");// если состояние не нулевое = готов
        printed = true;
        if (pointers.size()>0) {
            for (int i = 0; i < pointers.size(); i++) {
                pointers[i]->printTreeReady(otstupColv+1);
            }
        }
    }
}
void base::setHead(base *head) {
    father=head;
}
void base::changeHead(base *head) { //смена головного объекта (например перенос к другому родительскому)
    for (int i=0;i<father->pointers.size();i++) {
        if ((father->pointers[i])->getName() == getName()) {
            father->pointers.erase(father->pointers.begin()
                                   +i); //удаляем из родительского
        }
    }
    setHead(head);//устанавливаем родителя новый элемент
    father->pointers.push_back(this);//добавляем объект в список детей..родителя
}
base* base::findObject(string name) { //найти объект
    if (getName() == name) // если искомый объекь - текущий = вернуть ег
        return this;
    else if (pointers.size()>0) { //если есть дети - идем по ним
        for (int i=0; i<pointers.size();i++) {
            base* found = pointers[i]->findObject(name); //запуск поиска от лица ребенка
            if (found!=nullptr) //если ребенок нашел искомый, возвращаем его
                return found;
        }
    }
    return nullptr; //ничего не нашлось
};
int base::getState() {
    return state;
}
void base::setState(int newState) { // установка состояния
    base *f = this;
    while (f!=nullptr && newState!=0) { // проверка, не выключены ли родители
                f = f->father;
        if (f!=nullptr && father->getState()==0) { // проход по родителям вверх, при нахождении выключенного выход
            return;
        }
    }
    state = newState; //сама установка нового состояния
    if (newState==0) { // если выключили объект
        for (int i = 0; i < pointers.size(); i++) { //выключение детей
            pointers[i]->setState(0);
        }
    }
}
void base::setClass(int num) {
    this->classNum = num;
}
int base::getClass() {
    return classNum;
}
void base::clearPrinted() { //сделать у всех элементов printed=false, что бы их опять можно было вывести
    printed = false;
    if (pointers.size()>0) { //у всех детей тоже делаем printed=false
        for (int i = 0; i < pointers.size(); i++) { //вывод его детей
            pointers[i]->clearPrinted();
        }
    }
}
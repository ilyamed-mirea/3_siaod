#include "base.h"

void base::setName(string name) {
    this->name = name;
}
string base::getName() {
    return name;
}
void base::printTree(int otstupColv) { //вывод дерева
    if (!printed) { //если элемент еще не выводился
        if (otstupColv != 0) {
            cout << endl; // перенос строки от предыдущей
        }
        string otstup = "    ";
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
        string otstup = "    ";
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
            father->pointers.erase(father->pointers.begin()+i); //удаляем из родительского
        }
    }
    setHead(head);//устанавливаем родителя новый элемент
    father->pointers.push_back(this);//добавляем объект в список детей..родителя
}
base* base::findObject(string name) { //найти объект
    if (getName() == name) // если искомый объекь - текущий = вернуть его
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
base* base::getRoot(base *obj) {
    base *p = obj;
    while (p->father!=nullptr) {
        p = p->father;	//идем вверх по иерархии до корневого
    }
    return p; //возврат корневого элемента
}
base* base::findObjectByCoord(string coord) {
    int i = 0;
    string name = "";
    base *p = getRoot(this); //корневой объект
    if (coord=="/") { // вернуть корень
        return p;
    }
    else if (coord[i]=='/' && coord[i+1]=='/') { //если поиск от корневого
        i+=2; //пропуск //
        for (;i<coord.length();i++) {
            name+=coord[i]; // считываем имя объекта, который нужно найти
        }
        return p->findObjectByCoord(name); //находим и возвращаем
    }
    else if (coord==".") { //если текущий объект
        return this;
    }
    else if (coord[i]=='/') { //абсолютная координата от корневого
        i+=1; //пропуск /
        string newCoord = "";
        while (i<coord.length() && coord[i]!='/') { //считываем имя ребенка, которого будем искать от головного
            name+=coord[i];
            i++;
        }
        if (i<coord.length()) { //если есть еще вложенные объекты
            for (;i<coord.length();i++) {
                newCoord+=coord[i];
            }
        }
        else { //если нет вложенных
            newCoord='.'; //установка теукщего элемента как координаты поиска
        }
        base *found = p->findObject(name);
        if (found==nullptr) { //если не нашел у родительского
            return nullptr;
        }
        else {
            return p->findObject(name)->findObjectByCoord(newCoord); //вызов от ребенка метода поиска по координатам
        }
    }
    else if(coord.length() == 0) {
        return nullptr;
    }
    else { //относительная координата от текущего объекта
        string newCoord="";
        /*if (coord[i] == '.' && coord[i+1]=='/') { //если начинается с точки и есть еще что то
            i+=1; //пропуск .
            for (;i<coord.length();i++) {
                newCoord+=coord;
            }
            return p->findObjectByCoord(newCoord);
        }*/
        while (i<coord.length() && coord[i]!='/') { //считываем имя первого объекта
            name+=coord[i];
            i++;
        }
        base *child = findObject(name); //ищем ребенка по имени
        if (child == nullptr) //если ребенок не найден
            return nullptr;
        if (i<coord.length()) {
            i++; //пропуск /
            for (;i<coord.length();i++) { //считываем координаты оставшихся объектов
                newCoord+=coord[i];
            }
        }
        else { //если это последний объект в координатах, возвращаем его
            newCoord='.';
        }
        return child->findObjectByCoord(newCoord); //ищем по координатам относительно текущего ребенка
    }
}

string base::getObjectCoord() {
    string objCoord = "";
    base* obj = this;
    if (obj->father == nullptr) return "/";
    while (obj->father != nullptr) {
        objCoord = "/" + obj->getName() + objCoord;
        obj = obj->father;
    }
    return objCoord;
}
void base::setConnection(void (base::*pointerSignal)(string&), base* objHandler, void(base::*pointerHandler)(base*, string&)) {
    for (int i = 0; i < connections.size(); i++) {
        if (connections[i].pointerSignal == pointerSignal && connections[i].objConnection == objHandler && connections[i].pointerHandler == pointerHandler) {
            return;
        }
    }
    connections.push_back(connect{pointerSignal,objHandler,pointerHandler});
}

void base::deleteConnection(void (base::*pointerSignal)(string&), base* objHandler, void(base::*pointerHandler)(base*, string&)) {
    for (int i = 0; i < connections.size(); i++) {
        if (connections[i].pointerSignal == pointerSignal && connections[i].objConnection == objHandler && connections[i].pointerHandler == pointerHandler) {
            connections.erase(connections.begin() + i);
            return;
        }
    }
}
void base::pointerSignal(string& text) {
    cout << endl << "Signal from " << getObjectCoord();
}
void base::pointerHandler(base* obj, string& text) {
    if (getState())
        cout << endl << "Signal to " << getObjectCoord() << " Text: " + text + " (class: " + to_string(obj->getClass()) + ")";
}
void base::emit(void(base::*pointerSignal)(string&), string& command) {
    if (!getState())
        return;
    (this->*pointerSignal)(command);
    for (int i = 0; i < connections.size(); i++) {
        if (connections[i].pointerSignal == pointerSignal) {
            void (base::*pointerHandler)(base*, string&);
            pointerHandler = connections[i].pointerHandler;
            (connections[i].objConnection->*pointerHandler)(this,command);
        }
    }
}

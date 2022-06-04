#include "base.h"

void base::setName(string name) {
    this->name = name;
}
string base::getName() {
    return this->name;
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
base* base::findObject(string name, vector<base*> objectsB, base* parent) { //найти объект
    for (int i = 0; i < objectsB.size(); i++) {
        if (objectsB[i]->getName() == name && objectsB[i]->father == parent)
            return objectsB[i];
    }
    /*if (getName() == name && father == parent) // если искомый объекь - текущий = вернуть его
        return this;
    else if (pointers.size()>0) { //если есть дети - идем по ним
        for (int i=0; i<pointers.size();i++) {
            base* found = pointers[i]->findObject(name); //запуск поиска от лица ребенка
            if (found!=nullptr) //если ребенок нашел искомый, возвращаем его
                return found;
        }
    }*/
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
base* base::findObjectByCoord(string coord, vector<base*> objectsB) {
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
        return p->findObjectByCoord(name, objectsB); //находим и возвращаем
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
        base *found = p->findObject(name, objectsB, this);
        if (found==nullptr) { //если не нашел у родительского
            return nullptr;
        }
        else {
            return p->findObject(name,objectsB,this)->findObjectByCoord(newCoord, objectsB); //вызов от ребенка метода поиска по координатам
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
        base *child = findObject(name,objectsB, this); //ищем ребенка по имени
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
        return child->findObjectByCoord(newCoord, objectsB); //ищем по координатам относительно текущего ребенка
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
void base::setConnection(void (base::*pointerSignal)(string&), base* objFrom, base* objTo, void(base::*pointerHandler)(base*, string&)) {

    for (int i = 0; i < connections.size(); i++) {
        if (connections[i].pointerSignal == pointerSignal && connections[i].objTo == objTo && connections[i].objFrom == objFrom && connections[i].pointerHandler == pointerHandler) {
            return;
        }
    }
    getRoot(this)->connections.push_back(connect{pointerSignal,objFrom,objTo,pointerHandler});
}

void base::deleteConnection(void (base::*pointerSignal)(string&), base* objFrom, base* objTo, void(base::*pointerHandler)(base*, string&)) {
    for (int i = 0; i < connections.size(); i++) {
        if (connections[i].pointerSignal == pointerSignal && connections[i].objTo == objTo && connections[i].objFrom == objFrom && connections[i].pointerHandler == pointerHandler) {
            connections.erase(connections.begin() + i);
            return;
        }
    }
}
void base::pointerSignal(base* obj, string& text) { //obj = this
    base *root = getRoot(this);
    if (this->getName()=="Commander") {
        if (text=="logout") { //завершение сессии
            for (int i = 0; i < root->persons.size();i++) {
                root->persons[i].status = 0; //выходим из аккаунта/отходит от банкомата
            }
            root->depositing = 0;
            root->curStatus="ready"; //банкомат готов к работе
            root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord("//CashIn", root->pointers), text="return"); //отправляем комманду возврата денег

            root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord("//Printer", root->pointers), text = "Ready to work"); //и сообщает об этом
        }
        else if (text=="off") { //выключение
            root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord("//Printer", root->pointers), text = "Turn off the ATM"); //
            root->setState(0);
            root->depositing = 0;
            root->curStatus="off";
        }
        else if (root->depositing == 1 && text.substr(0,3)!="ADD") { //левая комманда во время внесения
            root->depositing = 0; //закончилось внесение средств
            root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord("//CashIn", root->pointers), text="return"); //отправляем комманду возврата денег
        }
        else if (text.substr(0,3)=="ADD") { //положить деньги
            root->depositing = 1; //началось внесение средств
            root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord("//CashIn", root->pointers), text=text.substr(3)); //отправляем комманду ADD100 где 100 - сумма внесения в CashIn
        }
        else if (text.substr(0,2)=="ID") { //commander вызывает indentification для проверки карты
            text=text.substr(2);
            //cout << "xsxsxs" << obj->name;
            root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord("//Identification", root->pointers), text); //проверка номера карты
        }
        else if (text.substr(0,3)=="PIN") { //commander вызывает indentification для проверки пин кода
            text=text.substr(3);
            root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord("//Identification", root->pointers), text); //проверка пинкода
        }
        else if (text.substr(0,8)=="WITHDRAW") { //снять деньги
            root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord("//CashOut", root->pointers), text=text.substr(8)); //отправляем сигнал обработки вывода в CashOut
        }
        else if (text=="End card loading") { //завезли денег или карт, инициализация банкомата завершена
            root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord("//Printer", root->pointers), text = "Ready to work");
        }
        else if (root->curStatus=="off") {//if (text!="End card loading" && text!="End money loading") { //загрузка в банкомат денег и карт
            //cout << endl << " gg " << text << endl;
            if (text.substr(0,4)=="Card") {
                text=text.substr(text.find(" ")+1);  // пропуск Card
                string cardNumN = text.substr(0,19);//(text.substr(0,4)+text.substr(5,4)+text.substr(10,4)+text.substr(15,4));
                //cout << cardNumN << endl;
                string pinN = text.substr(20,4);
                int amountN = stoi(text.substr(25));
                Person *pers;
                pers = new Person(cardNumN,pinN,amountN);
                root->persons.push_back(*pers);
            }
            else if (text.substr(0,5)=="Money") {
                text = text.substr(text.find(" ")+1); // пропуск Money
                //root->money.reserve(5);
                //cout << text << endl;
                /*while(text.find(" ")!=string::npos) {
                    string curSum = text.substr(0,text.find(" "));
                    int colv = stoi(curSum);
                    root->money.push_back(colv);
                    text = text.substr(text.find(" ")+1);
                }*/
                string buff;
                for (int i = 0; i <= text.length(); i++) {
                    if (text[i] == ' ' || i==text.length()) {
                        root->money.push_back(stoi(buff));
                        buff = "";
                    }
                    else
                        buff += text[i];

                }
                //cout << (root->money[0])<<" "<<(root->money[1])<<" "<<(root->money[2])<<" "<<(root->money[3])<<" "<<(root->money[4]) << endl;

            }
        } else {//if (root->money.size()!=0 && root->persons.size()!=0){// && root->) { //если поступает левая команда не во время готовности
            root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord("//Printer", root->pointers), text = "Ready to work");
            //root->pointerSignal(findObjectByCoord("//Commander", root->pointers),text = "logout");
        }

    }

    else if (this->getName()=="Identification") {
        if (text.substr(0,6)=="CARDok") { // получение данных о проверке номера карты
            root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord("//Printer", root->pointers), text = "Enter the PIN code"); //Вывод сообщения с просьбой ввести пин
        }
        else if (text.substr(0,5)=="PINok") { //|| text.substr(0,5)=="PINnotok" получение данных о проверке пин кода
            root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord("//Printer", root->pointers), text = "Select the command"); //Вывод сообщения о готовности принимать комманды
        }
        else { //проверка не успешна, карта/пин не подошли
            //root->pointerSignal(root,text="logout");
            //root->emit(SIGNAL_DEF(base, pointerSignal),this,root,text="Ready to work");
        }
    }

    else if (this->getName()=="CashIn") {
        if (text.substr(0,3)=="DEP") { //завершился внос средств
            root->depositing = 0; //ввод завершен
            int sum = stoi(text.substr(3)); //обрезаем DEP
            for (int i = 0; i < root->persons.size(); i++) {
                if (root->persons[i].status == 2) { //ищем человека, который сейчас у банкомата
                    root->persons[i].amount+=sum;
                    root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord("//Printer", root->pointers), text = "Card balance "+to_string(root->persons[i].amount)); //отправка сигнала для вывода текущего баланса
                    break;
                }
            }
        }
    }

    else if (this->getName()=="CashOut") {
        if (text=="poorMan") { //у человека недостаточно средств
            root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord("//Printer", root->pointers), text = "There is not enough money on the card");
        }
        else if (text=="poorATM") { //у банкомата недостаточно средств
            root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord("//Printer", root->pointers), text = "There is not enough money in the ATM");
        }
        else if (text=="not100") { //сумма не кратна 100
            root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord("//Printer", root->pointers), text = "The amount is not a multiple of 100");
        }
        else { //все норм
            root->emit(SIGNAL_DEF(base, pointerSignal),root,findObjectByCoord("//Printer", root->pointers), text); //отправка сигнала для вывода сколько денег сняли
        }
    }

}
void base::pointerHandler(base* obj, string& command) {
    //if (getState())
    cout << endl << obj->getName() << " handler \n" << command << endl; //this->getName() << " Text: " + text + " (class: " + to_string(this->getClass()) + ")";
}
//void base::emit(void(base::*pointerSignal)(string&), string& command) {
void base::emit(void(base::*pointerSignal)(string&), base *objFrom, base *objTo, string& command) {
    if (!getState())
        return;
    connections=getRoot(this)->connections; //все соединения хранятся в головном элементе
    //(this->*pointerSignal)(command); //вызов метода у отправщика
    for (int i = 0; i < connections.size(); i++) {
        //if (connections[i].pointerSignal == pointerSignal) {
        if (objFrom == connections[i].objFrom && objTo == connections[i].objTo || objFrom == connections[i].objTo && objTo == connections[i].objFrom) {
            //cout << endl << "emitted from " << objFrom->getName() << " to " << objTo->getName() << endl;
            //cout << this->getName() << connections[i].objConnection->getName();
            if (objFrom==connections[i].objFrom) { //если from-to
                void (base::*pointerHandler)(base*, string&);
                pointerHandler = connections[i].pointerHandler;
                (objTo->*pointerHandler)(objFrom,command); //this,command вызов handler у принимающего
            }
            else { //возврат to-from
                //void (base::*pointerHandler)(base*, string&);
                //pointerHandler = connections[i].pointerHandler;
                (objFrom->*pointerSignal)(command);
            }
        }
    }
}

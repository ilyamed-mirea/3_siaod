#include "bonus.h"
#include "classes.h"
#include "base.h"
void bonus::build_tree_b() {
    int index = 1; // кол-во объектов в objectsB, 1 так как корневой элемент вводится вне цикла
    int i = 0; // просто итератор
    string line, coord; //line - полученная строка, coord - координата/путь
    cin >> name;
    base *root = new base(nullptr, name); //создание корневого объекта
    setCurrentElement_b(root); //установка корневого объекта текущим (по умолчанию должно быть)
    objectsB.push_back(root); //корневой элемент = нулевой
    getline(cin, line); //прогрев
    while (true) { //ввод дерева
        base *obj = nullptr;
        name = "";
        coord = "";
        i = 0;
        getline(cin, line);
        if (line == "endtree") //если был введен индикатор завершения ввода
            break;
        while (line[i] != ' ') { //считывание координат
            coord+=line[i];
            i++;
        }
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
}

void bonus::printTree_b() {
    cout << "Object tree" << endl;
    objectsB[0]->printTree(); //вывод дерева(рекурсивный)
    objectsB[0]->clearPrinted(); //поставить у всех элементов printed=false
    if (isHeadNotFound_b() != "ok") { //если при построении дерева произошла ошибка
        cout << endl << "The head object " << headNotFound << " is not found";
    }
}

void bonus::printTreeReady_b() {
    cout << endl << "The tree of objects and their readiness" << endl;
    objectsB[0]->printTreeReady(); //вывод дерева с состояниями(рекурсивный)
    objectsB[0]->clearPrinted();
}

base* bonus::findObject_b(string name) {
    return objectsB[0]->findObject(name); //найти объект, начало от корневого
}

base* bonus::findObjectByCoord_b(string coord, base* cur) {
    return cur->findObjectByCoord(coord); //найти объект по координатам относительно cur
}

base* bonus::getCurrentElement_b() {
    return currentEl;
}

void bonus::setCurrentElement_b(base *cur) {
    this->currentEl = cur;
}

void bonus::getCommands_b() {
    string command,coord,line;
    while (true) {
        command = "";
        coord = "";
        int i = 0;
        getline(cin,line);
        while (i<line.length() && line[i]!=' ') { //считывание комманды
            command += line[i];
            i++;
        }
        if (command == "END") //выход если было введено END
            break;
        i++; //пробуск пробела
        for (;i<line.length();i++) {
            coord += line[i];
        }
        cout << endl;
        base *found;
        if (command == "SET") {
            found = findObjectByCoord_b(coord, getCurrentElement_b()); //находим введенный объект, ища от корневого old:getRoot(getCurrentElement_b())
            if (found == nullptr) { //если объект не нашелся
                cout << "Object is not found: " << getCurrentElement_b()->getName() << " " << coord;
            }
            else {
                setCurrentElement_b(found); //установка нового текущего объекта
                cout << "Object is set: " << getCurrentElement_b()->getName(); //вывод нового
            }
        } else if (command == "FIND") {
            found = findObjectByCoord_b(coord, getCurrentElement_b()); //поиск объекта
            if (found == nullptr) { //если объект не нашелся
                cout << coord << "     Object is not found";
            }
            else {
                cout << coord << "     Object name: " << found->getName(); //вывод найденного объекта
            }
        }
    }
}
string bonus::isHeadNotFound_b() {
    return headNotFound;
}


void bonus::configureConnections_b() {
    string from,to,command,coord,msg;
    int newCondition;
    base* objFrom;
    base* objTo;
    cin >> coord;
    while (coord!="end_of_connections") {
        cin >> from >> to;
        objFrom = findObjectByCoord_b(from, objectsB[0]);
        objTo = findObjectByCoord_b(to, objectsB[0]);
        objFrom->setConnection(recognitionSignal(), objTo, recognitionHandler());
    }
    cin >> command;
    while (command!="END") {
        if (command == "EMIT") {
            cin >> from >> msg;
            objFrom = findObjectByCoord_b(from, objectsB[0]);
            for (int i =0;i<objFrom->connections.size();i++) {
                objFrom->emitSignal(objFrom->connections[i].signalConnection, msg); //command
            }
        }
        else if (command == "SET_CONNECT") {
            cin >> from >> to;
            objFrom = findObjectByCoord_b(from, objectsB[0]);
            objTo = findObjectByCoord_b(to, objectsB[0]);
            [](base* objFrom,base* objTo){objFrom->setConnection(SIGNAL_D(base::signal), objTo, HANDLER_D(base::handler)); }(objFrom, objTo);
            /*[](vector <base*> objectsB){ //лямбда-функция (анонимная функция), в [] можно отлавливать переменную (либо по значению без возможности редактирования, либо по ссылке с возможностью редактирования)
                (*(objectsB[1])).setConnection(recognitionSignal(), objectsB[2], recognitionHandler());
                //(*(objectsB[(objectsB).size() - 1])).setConnection(recognitionSignal(), objectsB[(objectsB).size() - 3], recognitionHandler());
                //(*(objectsB[(objectsB).size() - 1])).setConnection(recognitionSignal(), objectsB[(objectsB).size() - 4], recognitionHandler());
                (*(objectsB[1])).emitSignal(recognitionSignal(), "let's celebrate and...");
                (*(objectsB[1])).deleteConnection(recognitionSignal(), objectsB[2], recognitionHandler());
                //(*(objectsB[(objectsB).size() - 1])).emitSignal(recognitionSignal(), "let's celebrate and..."); //тревога и печаль... мне кажется сейчас...
            }(objectsB);*/
        }
        else if (command == "DELETE_CONNECT") {
            cin >> from >> to;
            objFrom = findObjectByCoord_b(from, objectsB[0]);
            objTo = findObjectByCoord_b(to, objectsB[0]);
            objFrom->deleteConnection(SIGNAL_D(base::signal), objTo, HANDLER_D(base::handler));
        }
        else if (command == "SET_CONDITION") {
            cin >> from >> newCondition;
            objFrom = findObjectByCoord_b(from, objectsB[0]);
            objFrom->setCondition(newCondition);
        }
        cin >> command;
    }
}
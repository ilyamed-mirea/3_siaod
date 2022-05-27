#include "classes.h"
#include "bonus.h"
#include "base.h"

void bonus::build_tree_b() {
    int index = 1; // корневой элемент вводится вне цикла
    cin >> name;
    base *root = new base(nullptr, name);
    objectsB.push_back(root); //корневой элемент = нулевой
    currentEl = root;
    while (fatherName != "endtree") { //ввод дерева
        base *obj = nullptr;
        base *foundParent;
        //cin >> name >> classNum;
        string line;
        name = "";
        getline(cin, line);
        int i = 0;
            if ((line[0]+line[1])=='/ ') { //добавление к корневому
                i=2; //пропускам '/ '
                foundParent = root;
            }
            else { // добавление к существующему объекту
                while (line[i]!=' ') { //нахождение объекта нужного
                    i+=1; //пропуск "/"
                    while (line[i] != ' ' || line[i] != '/') { //считывание имени объекта
                        name += line[i];
                        i++;
                    }
                    currentEl = findObject_b(name); //находим его и устанавливаем текущим
                }
                name = "";
                foundParent = currentEl;
            }
        while(line[i]!=' ') { //считывание имени нового объекта
            name+=line[i];
            i++;
        }
        classNum = int(line[i+1]); //и класса
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
    while (cin >> name >> state) { //ввод состояний
        base* obj = findObject_b(name); //находим объект
        if (obj!=nullptr) {
            obj->setState(state); //устанавливаем ему состояние
        }
    }
}
void bonus::printTree_b() {
    cout << "Object tree" << endl;
    objectsB[0]->printTree(); //вывод дерева(рекурсивный)
    objectsB[0]->clearPrinted(); //поставить у всех элементов printed=false;
}
void bonus::printTreeReady_b() {
    cout << endl << "The tree of objects and their readiness" << endl;
    objectsB[0]->printTreeReady(); //вывод дерева с состояниями(рекурсивный)
    objectsB[0]->clearPrinted();
}
base* bonus::findObject_b(string name) {
    return objectsB[0]->findObject(name); //найти объект, начало от корневого
}
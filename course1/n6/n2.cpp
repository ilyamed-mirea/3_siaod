#include <iostream>
#include <string>
#include <windows.h>

//var18

using namespace std;

struct list {
    int data;
    struct list *ptr;
};

struct list * createList() {
    cout << "Сколько элементов вы хотите добавить в список?" << endl;
    int len;
    cin >> len;
    int val;
    cin >> val;
    list *lst = new list[sizeof(struct list)];
    lst->data = val;
    lst->ptr = nullptr;
    for (int i = 0; i < len-1; i++) {
        cin >> val;
        struct list *newElem, *p, *prevElem;
        p = lst;
        newElem = new list[sizeof(struct list)];
        for (int j = 0; j < i; j++)
            p = p->ptr;
        prevElem = p;
        p = prevElem->ptr; // сохранение указателя на следующий узел
        prevElem->ptr = newElem; // предыдущий узел указывает на создаваемый
        newElem->data = val; // сохранение поля данных добавляемого узла
        newElem->ptr = p; // созданный узел указывает на следующий элемент
    }
    return lst;
}

int getColvNechet(struct list *lst, int colv) {
    struct list *p;
    p = lst;
    if (p->data % 2 != 0)
        colv++;
    if (p->ptr != nullptr)
        colv = getColvNechet(p->ptr, colv);
    return colv;
}

int main() {
    system("chcp 65001");

    list *list = createList();
    int colv = getColvNechet(list, 0);
    cout << "Количество нечетных чисел в списке: " << colv << endl;

    system("pause");

    return 0;
};
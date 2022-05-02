#include <iostream>
#include <Windows.h>

using namespace std;

struct list {
    char data;
    struct list *ptr;
};

struct list * init(char val) {
    struct list *lst;
    lst = new list[sizeof(struct list)];
    lst->data = val;
    lst->ptr = NULL; // это последний узел списка
    return lst;
}

void addElem(list *&lst, int index, char val) {
    struct list *newElem, *p, *prevElem;
    p = lst;
    newElem = new list[sizeof(struct list)];
    for (int i = 0; i < index; i++)
        p = p->ptr;

    prevElem = p;
    p = prevElem->ptr; // сохранение указателя на следующий узел
    prevElem->ptr = newElem; // предыдущий узел указывает на создаваемый
    newElem->data = val; // сохранение поля данных добавляемого узла
    newElem->ptr = p; // созданный узел указывает на следующий элемент
}

void deleteElem(list *lst, list *&root) {
    struct list *temp;
    temp = root;
    if (root == lst) { // если нужно удалить первый элемент
        root=root->ptr; //исправить ошибку если второй элемент тоже не цифра рекурсивным вызовом
        //deleteElem(root->ptr,root);
    }
    else {
        while (temp->ptr != lst) // просматриваем список начиная с корня
        { // пока не найдем узел, предшествующий lst
            temp = temp->ptr;
        }
        temp->ptr = lst->ptr; // переставляем указатель
        free(lst); // освобождаем память удаляемого узла
    }
}

bool isNum(char x) {
    char nums[10] = {'0','1','2','3','4','5','6','7','8','9'};
    return (find(begin(nums),end(nums),x) != end(nums));
}

struct list * createList() {
    cout << "Сколько элементов вы хотите добавить в список?" << endl;
    int len;
    cin >> len;
    char val;
    cin >> val;
    list *lst = init(val);
    for (int i = 0; i < len-1; i++) {
        cin >> val;
        addElem(lst, i, val);
    }
    return lst;
}

void printList(list *lst) {
    struct list *p;
    p = lst;
    do {
        cout << p->data << " "; // вывод значения элемента p
        p = p->ptr; // переход к следующему узлу
    } while (p != NULL);
    cout << endl;
}

void insertList(list *from, list *&to) {
    struct list *p, *p2;
    int i = 0;
    p = to;
    char x;
    cout << "Введите элемент, после которого осуществить вставку" << endl;
    cin >> x;
    bool fl = true;
    do {
        if (p->data == x) {
            p2 = from;
            do {
                addElem(to, i, p2->data);
                p2 = p2->ptr; // переход к следующему узлу
                i++;
            } while (p2 != NULL);
            fl = false;
            break;
        }
        p = p->ptr; // переход к следующему узлу
        i++;
    } while (p != NULL);
    if (fl)
        cout << "Элемент " << x << " не найден" << endl;
}

void deleteNumbers(list *&lst) {
    struct list *p;
    p = lst;
    char nums[10] = {'0','1','2','3','4','5','6','7','8','9'};
    do {
        if (!isNum(p->data)) {
            //cout << endl << "find " << p->data << endl;
            deleteElem(p, lst);
            p = lst;
        }
        else
            p = p->ptr; // переход к следующему узлу
    } while (p != NULL);
}

long long int createNum(list *lst) {
    int razr = 1;
    long long int res = 0;
    struct list *p;
    p = lst;
    do {
        if (isNum(p->data)) {
            if(res+((p->data-'0')*razr) > 9223372036854775807) break;
            res += (p->data-'0') * razr;
            razr*=10;
        }
        p = p->ptr; // переход к следующему узлу
    } while (p != NULL);
    return res;
}

int getCount(list *head)
{
    // Initialize count
    int count = 0;

    // Initialize current
    list* current = head;
    while (current != NULL)
    {
        count++;
        current = current->ptr;
    }
    return count;
}

int main() {
    system("chcp 65001");
    cout << "Лист 1:" << endl;
    list *L1 = createList();
    printList(L1);
    long long int num = createNum(L1);
    //deleteNumbers(L1);
    //printList(L1);
    cout << num << endl;
    cout << "Лист 2:" << endl;
    list *L2 = createList();
    //insertList(L2,L1);
    printList(L1);
    return 0;
};
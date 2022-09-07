#include <iostream>
using namespace std;

struct list;
bool isNum(char x);
void getCorrectInput(auto &x);
void addElem(list *lst, int index, char val);
void deleteElem(list *lst, list *&root);
void printList(list *lst, int index);
struct list * createList();
void deleteNotNumbers(list *&lst);
void insertList(list *from, list *&to);
long long int createNum(list *lst);

struct list {
    char data;
    struct list *ptr;
    list(char data, struct list *ptr) {
        this->data = data;
        this->ptr = ptr;
    }
};

bool isNum(char x) {
    char nums[10] = {'0','1','2','3','4','5','6','7','8','9'};
    return (find(begin(nums),end(nums),x) != end(nums));
}

void getCorrectInput(auto &x) {
    while (true) {
        cin >> x;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(32777, '\n');
            cout << "Ошибка! Повторите ввод..." << endl;
        }
        else
            break;
    }
}

void addElem(list *lst, int index, char val) {
    struct list *newElem, *p, *prevElem;
    p = lst;
    for (int i = 0; i < index; i++)
        p = p->ptr;

    prevElem = p;
    p = prevElem->ptr; // сохранение указателя на следующий узел
    newElem = new list(val,p);
    prevElem->ptr = newElem; // предыдущий узел указывает на новый
}

void deleteElem(list *lst, list *&root) {
    struct list *temp;
    temp = root;
    if (root == lst) { // если нужно удалить первый элемент
        if (root->ptr == nullptr) {
            cout << "В списке не было чисел и теперь он пуст. Пожалуйста, создайте его заново" << endl;
            root = createList();
        }
        else
            root=root->ptr;
    }
    else {
        while (temp->ptr != lst) {
            temp = temp->ptr;
        }
        temp->ptr = lst->ptr; // переставляем указатель
        free(lst); // освобождаем память удаляемого узла
    }
}

void printList(list *lst, int index) {
    cout << "<Вывод списка " << index << ">" << endl;
    struct list *p;
    p = lst;
    do {
        cout << p->data << " "; // вывод значения элемента p
        p = p->ptr; // переход к следующему узлу
    } while (p != nullptr);
    cout << endl;
}

struct list * createList() {
    cout << "<Создание списка>" << endl;
    cout << "Из скольких элементов будет состоять список?" << endl;
    int len = -1;
    while (len<=0) {
        getCorrectInput(len);
        if (len<=0)
            cout << "Ошибка! Введите число больше нуля" << endl;
    };
    char val;
    cout << "Введите элемент N 1" << endl;
    getCorrectInput(val);
    list *lst = new list(val, nullptr);
    for (int i = 0; i < len-1; i++) {
        cout << "Введите элемент N " << i+2 << endl;
        getCorrectInput(val);
        addElem(lst, i, val);
    }
    cout << "<Список создан>" << endl;
    return lst;
}

void deleteNotNumbers(list *&lst) {
    cout << endl << "<Удаление из списка нечисловых значений>" << endl;
    struct list *p;
    p = lst;
    do {
        if (!isNum(p->data)) {
            deleteElem(p, lst);
            p = lst;
        }
        else
            p = p->ptr; // переход к следующему узлу
    } while (p != nullptr);
    printList(lst, 2);
}

void insertList(list *from, list *&to) {
    cout << endl <<  "<Вставка второго списка в первый>" << endl;
    struct list *p, *p2;
    int i = 0;
    p = to;
    char x;
    cout << "Введите элемент первого списка, после которого осуществить вставку второго списка" << endl;
    getCorrectInput(x);
    bool fl = true;
    do {
        if (p->data == x) {
            p2 = from;
            do {
                addElem(to, i, p2->data);
                p2 = p2->ptr; // переход к следующему узлу
                i++;
            } while (p2 != nullptr);
            fl = false;
            break;
        }
        p = p->ptr; // переход к следующему узлу
        i++;
    } while (p != nullptr);
    if (fl)
        cout << "Элемент " << x << " не найден в 1 списке." << endl;
    else {
        cout << "Список 2 вставлен в список 1:" << endl;
        printList(to, 1);
    }
}

long long int createNum(list *lst) {
    cout << endl << "<Составление числа из целочисленных элементов списка>" << endl;
    int razr = 1;
    long long int res = 0;
    struct list *p;
    p = lst;
    do {
        if (isNum(p->data)) {
            if (res+((p->data-'0')*razr) > 9223372036854775807) break;
            res += (p->data-'0') * razr;
            razr*=10;
        }
        p = p->ptr; // переход к следующему узлу
    } while (p != nullptr);
    return res;
}

int main() {
    system("chcp 65001");

    cout << "Список 1:" << endl;
    list *L1 = createList();
    printList(L1, 1);

    cout << endl << "Список 2:" << endl;
    list *L2 = createList();
    printList(L2, 2);

    insertList(L2,L1);

    deleteNotNumbers(L2);

    long long int num = createNum(L2);
    cout << "Число, составленное из цифр списка 2: " << endl << num << endl;

    system("pause");
    return 0;
};
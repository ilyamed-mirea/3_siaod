#include <string>
#include <iostream>
#include <ctype.h>
using namespace std;

#define MAX 100

struct list {
    int data[MAX];
    int top;
};

int precedence(char); //приоритетность
void init(list *); //установка top=-1
int empty(list *); //проверка на пустоту
int full(list *); //проверка на полноту
int pop(list *); //удаление элемента
void push(list *, int); //добавление элемента
int top(list *); //значение головного элемента
string infix_to_postfix(string infix); //функция перевода из инф в постф

int main() {
    string infix, postfix;
    cout << "Enter an infix expression(eg: 5+2*4): ";
    cin >> infix;
    postfix = infix_to_postfix(infix);
    cout << endl << "Postfix expression: ";
    cout << postfix;
    system("pause");
    return 0;
}

string infix_to_postfix(string infix) {
    list s{};
    string postfix;
    char x, token;
    init(&s); //инициализация списка

    for (int i = 0; i < infix.length(); i++) {
        token = infix[i];
        if (isalnum(token)) //если буква или число
            postfix += token;
        else if (token == '(')
            push(&s, '(');
        else if (token == ')')
            while ((x = pop(&s)) != '(')
                postfix += x;
        else {
            while (precedence(token) <= precedence(top(&s)) && !empty(&s)) { //сравнение приоритетность текущего элемента и головного
                x = pop(&s);
                postfix += x;
            }
            push(&s, token);
        }
    }

    while (!empty(&s)) { //если в стеке что то осталось
        x = pop(&s);
        //cout << x << endl;
        postfix += x;
    }
    return postfix;
}

int precedence(char x) {
    if (x == '(')
        return (0);
    if (x == '+' || x == '-')
        return (1);
    if (x == '*' || x == '/' || x == '%')
        return (2);

    return (3);
}

void init(list *s) {
    s->top = -1;
}

int empty(list *s) {
    if (s->top == -1)
        return (1);

    return (0);
}

int full(list *s) {
    if (s->top == MAX - 1)
        return (1);

    return (0);
}

void push(list *s, int x) {
    s->top = s->top + 1;
    s->data[s->top] = x;
}

int pop(list *s) {
    int x;
    x = s->data[s->top];
    s->top = s->top - 1;
    return x;
}

int top(list *p) {
    return (p->data[p->top]);
}
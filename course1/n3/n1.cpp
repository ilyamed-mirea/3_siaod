#include <iostream>
#include <Windows.h>

using namespace std;

void copyStr(const char *from, char *to) { //копирование одной строки в другую
    for (char *p = to; (*p = *from) != '\0'; ++p, ++from);
}

void addWordToString(char *newString, char *slovo, char *razdel) { //добавление слова в строку
    int length = 0;
    int slovoLength = 0;
    bool fl = true;
    const char *glasn = "ајоќу”ыџи»е≈Є®эЁюё€я";
    for (; *slovo != '\0'; slovoLength++, slovo++);
    for (; *newString != '\0'; newString++, length++);
    slovo -= slovoLength;
    newString -= length;
    for (int j = 0; j < 20; j++) {
        if (slovo[0] == glasn[j]) {
            fl = false;
            break;
        }
    }
    if (fl) {
        int i = 0;
        for (; i < slovoLength; i++) {
            newString[length + i] = slovo[i];
        }
        newString[length + i] = *razdel;
        *razdel++;
        while (*razdel == ' ') {
            i++;
            newString[length + i] = *razdel;
            *razdel++;
        }
        i++;
        newString[length + i] = '\0';
    }
}

void toWords(char *s) { //разбиение строки на слова с последующей проверкой
    char slovo[20];
    char newString[1024] = "";
    int j;
    int i = 0;
    while (s[i] != '\0') {
        j = 0;
        while (s[i] != '\0' && (s[i]) != ' ' && (s[i]) != ',') {
            slovo[j] = s[i];
            i++;
            j++;
        }
        slovo[j] = '\0';
        if (j != 0) addWordToString(newString, slovo, &s[i]);
        while ((s[i]) == ' ' || (s[i]) == ',') {
            i++;
        }
    }
    copyStr(newString, s);
}

void capsLock(char *str) { //перевод букв в прописные
    int i = 0;
    while (*(str + i) != '\0') {
        if (*(str + i) + 256 > 223 && *(str + i) + 256 < 256) {
            *(str + i) -= 32;
        }
        i++;
    }
}

void add_(char *str) { //добавление разделител€
    char newString[1024];
    int gap = 0;
    char slovo1[1];
    char slovo2[1];
    int i = 0;
    while (str[i] != '\0') {
        int j = 0;
        while (str[i] != '\0' && (str[i]) != ' ' && (str[i]) != ',') {
            newString[i + gap] = str[i];
            i++;
            j++;
        }
        if (str[i] == '\0') break;
        slovo1[0] = str[i - 1];
        int dopgap = 0;
        while (str[i] == ' ' || str[i] == ',') {
            newString[i + gap] = str[i];
            i++;
            dopgap++;
        };
        slovo2[0] = str[i];
        if (slovo1[0] == slovo2[0]) {
            gap -= dopgap;
            newString[i + gap] = '-';
            gap++;
            newString[i + gap] = '*';
            gap++;
            newString[i + gap] = '-';
            gap++;
        }
    }
    newString[i + gap] = '\0';
    copyStr(newString, str);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char str[1024];
    cout << "¬ведите строку: " << endl;
    gets(str);
    toWords(str);
    capsLock(str);
    add_(str);
    puts(str);
    system("pause");
    return 0;
}
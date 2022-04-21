#include <iostream>
#include <Windows.h>

using namespace std;

void copyStr(const char *from, char *to) {
    for (char *p = to; (*p = *from) != '\0'; ++p, ++from);
}

void addStr(const char *add, char *base) {
    char newStr[1024];
    int i = 0;
    while (*base != '\0') {
        newStr[i] = *base;
        base++;
        i++;
    }
    while (*add != '\0') {
        newStr[i] = *add;
        add++;
        i++;
    }
    newStr[i] = '\0';
    copyStr(newStr, base);
}

void addWordToString(char *newString, char *slovo, char *razdel) {
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

void toWords(char *s) {
    char slovo[20];
    char newString[1024] = "";
    int j;
    int i = 0;
    while (s[i] != '\0')        //до конца текста
    {
        j = 0;
        while (s[i] != '\0' && (s[i]) != ' ' && (s[i]) != ',')    //до конца слова
        {
            slovo[j] = s[i];
            i++;
            j++;
        }
        slovo[j] = '\0';
        if (j != 0) addWordToString(newString, slovo, &s[i]);
        //puts(slovo);
        while ((s[i]) == ' ' || (s[i]) == ',') {
            i++;
        }
        /*if (s[i] != '\0') {
            i++;//уйти с разделител€ слова, если оно не последнее
        }*/
    }
    copyStr(newString, s);
}

void capsLock(char *str) {
    int i = 0;
    while (*(str + i) != '\0') {
        if (*(str + i) + 256 > 223 && *(str + i) + 256 < 256) {
            *(str + i) -= 32;
        }
        i++;
    }
}

void add_(char *str) {
    char newString[1024];
    int gap = 0;
    char slovo1[1];
    char slovo2[1];
    int i = 0;
    while (str[i] != '\0') {
        int j = 0;
        while (str[i] != '\0' && (str[i]) != ' ' && (str[i]) != ',')    //до конца слова
        {
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
            dopgap++; //много пробелов подр€д
        }; //много пробелов
        slovo2[0] = str[i];
        //cout << slovo1[0] << "    " << slovo2[0] << "   " << (slovo1[0] == slovo2[0]) << endl;
        if (slovo1[0] == slovo2[0]) {
            gap-=dopgap;
            newString[i + gap] = '-';
            gap++;
            newString[i + gap] = '*';
            gap++;
            newString[i + gap] = '-';
            gap++;
            /*char podstr[4] = "-*-";
            addStr(podstr,newString);*/
        }
       /* while (str[i] != '\0' && (str[i]) != ' ' && (str[i]) != ',')    //до конца слова
        {
            newString[i + gap] = str[i];
            i++;
        };
        while (str[i] != '\0' && (str[i] == ' ' || str[i] == ',')) {
            newString[i + gap] = str[i];
            i++;
        };*/
    }
    newString[i+gap]='\0';
    //cout << newString << endl;
    copyStr(newString, str);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char str[1024];// = "ѕривет мой друг, как у теб€ дела, парень икра акрил лампа";
    //int strLength = 0;
    //cout << "¬ведите строку: " << endl;
    gets(str);
    //for(int i=0;str[i] != '\0';i++,strLength++);
    toWords(str);
    capsLock(str);
    puts(str);
    system("pause");
    return 0;
}
#include <string>
#include <iostream>
#include <Windows.h>

using namespace std;

void toWords(string &s) {
    string slovo;
    string newString;
    int length = s.length();
    int j;
    int i = 0;
    while (i < length) {
        j = 0;
        while (i < length && (s[i]) != ' ' && (s[i]) != ',') {
            slovo += (s[i]);
            i++;
            j++;
        }
        slovo += (s[i]);

        if (j != 0) {
            bool fl = true;
            const string glasn = "ајоќу”ыџи»е≈Є®эЁюё€я";
            for (int k = 0; k < 20; k++) {
                if (slovo[0] == glasn[k]) {
                    fl = false;
                    break;
                }
            }

            if (fl) { newString += (slovo); }
        }
        while ((s[i]) == ' ' || (s[i]) == ',') {
            i++;
        }
        slovo = "";
    }
    s.assign(newString);
}

void capsLock(string &str) {
    for (char &i: str) {
        if (i + 256 > 223 && i + 256 < 256) {
            i -= 32;
        }
    }
}

void add_(string &str) {
    string newString;
    string slovo1;
    string slovo2;
    int i = 0;
    while (i<str.length()) {
        while (str[i] != '\n' && i<str.length() && str[i] != ' ' && str[i] != ',') {
            newString += str[i];
            i++;
        }
        slovo1 = str[i - 1];
        string razdel;
        while (str[i] == ' ' || str[i] == ',') {
            razdel+=str[i];
            i++;
        };
        slovo2 = str[i];
        if (slovo1[0] == slovo2[0] && int(slovo1[0])!=0)
            newString += "-*-";
        else
            newString += razdel;

        slovo1 = ""; slovo2 = "";
    }
    newString += '\n';
    str.assign(newString);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string str;// = "ѕривет, мой друг, однажды    € отправилс€ танцевать, р€дом мы стоим                   много
    cout << "¬ведите строку: " << endl;
    getline(cin, str);
    toWords(str);
    capsLock(str);
    add_(str);
    cout << str << endl;
    system("pause");
    return 0;
}
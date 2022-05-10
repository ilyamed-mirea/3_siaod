#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

struct disease {
    int code;
    string date;
};

struct patient {
    int policy;
    string surname;
    string name;
    string patronymic;
    vector<disease> diseaseList;

};

struct table {
    int size = 0;
    static const int maxSize = 100;
    patient *patientList[maxSize];
};


void printTable(table *tab) {
    for (int i=0;i<tab->size;i++) {
        cout << "patient " << i << ": " << endl;
        patient *curPatient = tab->patientList[i];
            cout << "Фамилия: " << curPatient->surname << endl;
            cout << "Имя: " << curPatient->name << endl;
            cout << "Отчество: " << curPatient->patronymic << endl;
            cout << "Список болезней: " << endl;
    }
}

void addDisease(patient *client, disease dis) {
    client.diseaseList.push_back(dis);
}

patient *addPatient(patient *emptyPatient) {
    cout << "Введите имя пациента" << endl;
    cin >> emptyPatient->name;
    cout << "Введите фамилию пациента" << endl;
    cin >> emptyPatient->surname;
    cout << "Введите отчество пациента" << endl;
    cin >> emptyPatient->patronymic;
    cout << "Введите номер полиса пациента" << endl;
    cin >> emptyPatient->policy;
    return emptyPatient;
}

int main() {
    system("chcp 65001");
    table table();


    system("pause");


    return 0;
};
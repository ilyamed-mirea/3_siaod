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
    patient *patientList[maxSize]{};
};

void printDiseaseList(vector<disease> list) {
    cout << "Список болезней: " << endl;
    for (int i=0;i<list.size();i++) {
        cout << "Болезнь " << i << endl;
        cout << "Код: " << list[i].code << endl;
        cout << "Дата: " << list[i].date << endl;
    }
}

void printTable(table *tab) {
    cout << "Вывод таблицы" << endl;
    for (int i=0;i<tab->size;i++) {
        cout << "Пациент " << i << ": " << endl;
        patient *curPatient = tab->patientList[i];
        cout << "Фамилия: " << curPatient->surname << endl;
        cout << "Имя: " << curPatient->name << endl;
        cout << "Отчество: " << curPatient->patronymic << endl;
        printDiseaseList(curPatient->diseaseList);
    }
}

void addDisease(patient *client, disease dis) {
    client->diseaseList.insert(client->diseaseList.begin(), dis);
}

patient *initPatient(patient *newPatient) {
    patient *emptyPatient = newPatient;
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

void addPatientInTable(table *t, patient *newPatient) {
    t->patientList[t->size] = newPatient;
    t->size++;
}

vector<patient> formListByCode(table *t, int code) {
    vector<patient> patientList;
    for (int i=0;i<t->size;i++) {
        patient *curPatient = t->patientList[i];
        int counter = 0; //счетчик количества заболеваний
        for (int j=0;j<curPatient->diseaseList.size();j++) {
            disease curDisease = curPatient->diseaseList[j];
            if (curDisease.code == code)
                counter++;
        }
        if (counter>1)
            patientList.push_back(*curPatient);
    }
}

void deleteDiseaseByCode(patient *pat, int code) {
    for (int i=0; i<pat->diseaseList.size();i++) {
        if (pat->diseaseList[i].code == code) {
            pat->diseaseList.erase(pat->diseaseList.begin()+i);
            i=0;
        }
    }
}

int main() {
    system("chcp 65001");
    table *table = new struct table;
    cout << "Сколько пациентов вы хотите создать?" << endl;
    int colv, pol, code;
    cin >> colv;
    for (int i=0;i<colv;i++) {
        cout << "Создание " << i << " пациента" << endl;
        patient *newPatient = new patient;
        newPatient = initPatient(newPatient);
        addPatientInTable(table, newPatient);
    }


    cout << "Сколько заболеваний вы хотите добавить?" << endl;
    cin >> colv;
    for (int i=0;i<colv;i++) {
        string date;
        cout << "Введите номер полиса пациента, которому хотите добавить заболевание";
        cin >> pol;
        patient *pat;
        for (int j=0;j<table->size;j++) { //поиск пациента по номеру полиса
            if (table->patientList[j]->policy==pol) {
                pat = table->patientList[j];
                break;
            }
        }
        cout << "Введите код болезни";
        cin >> code;
        cout << "Введите дату установки диагноза";
        cin >> date;
        disease dis;
        dis.code = code;
        dis.date = date;
        addDisease(pat, dis);
    }

    printTable(table);

    cout << "Введите код болезни для формирования списка людей с этой болезнью" << endl;
    cin >> code;
    vector<patient> patList = formListByCode(table, code);
    for (int i=0;i<patList.size();i++) {
        cout << "Список сформирован" << endl << "Пациент " << i+1 << endl;
        patient *curPatient = &patList[i];
        cout << "Фамилия: " << curPatient->surname << endl;
        cout << "Имя: " << curPatient->name << endl;
        cout << "Отчество: " << curPatient->patronymic << endl;
        printDiseaseList(curPatient->diseaseList);
    }

    cout << "Введите номер полиса пациента и код заболевания, которое необходимо удалить" << endl;
    cin >> pol >> code;
    patient *pat;
    for (int j=0;j<table->size;j++) { //поиск пациента по номеру полиса
        if (table->patientList[j]->policy==pol) {
            pat = table->patientList[j];
            break;
        }
    }
    deleteDiseaseByCode(pat, code);


    cout << "Болезнь удалена" << endl;
    printTable(table);

    system("pause");
    return 0;
};
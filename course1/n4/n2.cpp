#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

struct disease {
    int code;
    string date;
    disease(int code, string date) {
        this->code = code;
        this->date = date;
    }
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
    int maxSize = 0;
    patient *patientList = new patient[0];
    table(int maxSize) {
        patientList = new patient[maxSize];
        this->maxSize = maxSize;
    }
};

void printDiseaseList(vector<disease> list) {
    cout << "Список болезней: " << endl;
    for (int i=0;i<list.size();i++) {
        cout << "Болезнь " << i+1 << endl;
        cout << "Код: " << list[i].code << endl;
        cout << "Дата: " << list[i].date << endl;
    }
}

void printPatient(patient pat) {
    cout << "Номер полиса: " << pat.policy << endl;
    cout << "Фамилия: " << pat.surname << endl;
    cout << "Имя: " << pat.name << endl;
    cout << "Отчество: " << pat.patronymic << endl;
    if (pat.diseaseList.empty())
        cout << "Нет болезней";
    else
        printDiseaseList(pat.diseaseList);
}

void printTable(table *tab) {
    cout << "Вывод таблицы" << endl;
    for (int i=0;i<tab->size;i++) {
        cout << endl << "Пациент " << i+1 << ": " << endl;
        patient curPatient = tab->patientList[i];
        printPatient(curPatient);
        cout << endl;
    }
}

void addDisease(patient *pat, disease dis) {
    pat->diseaseList.insert(pat->diseaseList.begin(), dis);
}

patient *initPatient(patient *newPatient) {
    patient *emptyPatient = newPatient;
    cout << "Введите номер полиса пациента" << endl;
    cin >> emptyPatient->policy;
    cout << "Введите имя пациента" << endl;
    cin >> emptyPatient->name;
    cout << "Введите фамилию пациента" << endl;
    cin >> emptyPatient->surname;
    cout << "Введите отчество пациента" << endl;
    cin >> emptyPatient->patronymic;
    return emptyPatient;
}

void addPatientInTable(table *t, patient *newPatient) {
    if (t->size+1>t->maxSize) {
        cout << "Превышен максимальный размер массива. вставка не удалась" << endl;
        return;
    }
    t->patientList[t->size] = *newPatient;
    t->size++;
}

vector<patient> formListByCode(table *t, int code) {
    vector<patient> patientList;
    for (int i=0;i<t->size;i++) {
        patient curPatient = t->patientList[i];
        int counter = 0; //счетчик количества заболеваний
        for (int j=0;j<curPatient.diseaseList.size();j++) {
            if (curPatient.diseaseList[j].code == code)
                counter++;
        }
        if (counter>1)
            patientList.push_back(curPatient);
    }
    return patientList;
}

void deleteDiseaseByCode(patient *pat, int code) {
    bool fl = false;
    for (int i=0; i<pat->diseaseList.size();i++) {
        if (pat->diseaseList[i].code == code) {
            pat->diseaseList.erase(pat->diseaseList.begin()+i);
            i=0;
            fl=true;
        }
    }
    if (fl)
        cout << "Болезнь удалена" << endl;
    else
        cout << "Ошибка. болезнь не найдена" << endl;
}

int main() {
    system("chcp 65001");
    int colv, pol, code;
    cout << "Сколько пациентов вы хотите создать?" << endl;
    cin >> colv;
    table *table;
    table = new struct table(colv);
    for (int i=0;i<colv;i++) {
        cout << "Создание " << i+1 << " пациента" << endl;
        patient *newPatient = new patient;
        newPatient = initPatient(newPatient);
        addPatientInTable(table, newPatient);
    }

    printTable(table);

    cout << "Сколько заболеваний вы хотите добавить?" << endl;
    cin >> colv;
    for (int i=0;i<colv;i++) {
        string date;
        patient *pat;
        bool fl = true;
        cout << "Введите номер полиса пациента, которому хотите добавить заболевание" << endl;
        cin >> pol;
        for (int j=0;j<table->size;j++) { //поиск пациента по номеру полиса
            if (table->patientList[j].policy==pol) {
                pat = &(table->patientList[j]);
                fl=false;
                break;
            }
        }
        if (fl) {
            cout << "Пациент с данным номером полиса не найден. попробуйте еще раз" << endl;
            i--;
        }
        else {
            cout << "Введите код болезни" << endl;
            cin >> code;
            cout << "Введите дату установки диагноза" << endl;
            cin >> date;
            disease dis(code,date);
            addDisease(pat, dis);
        }
    }

    printTable(table);

    cout << "Введите код болезни для формирования списка людей с этой болезнью" << endl;
    cin >> code;
    vector<patient> patList = formListByCode(table, code);
    cout << "Список сформирован" << endl;
    for (int i=0;i<patList.size();i++)
        printPatient(patList[i]);

    cout << endl << "Введите номер полиса пациента и код заболевания, которое необходимо удалить" << endl;
    cin >> pol >> code;
    patient *pat;
    for (int j=0;j<table->size;j++) { //поиск пациента по номеру полиса
        if (table->patientList[j].policy==pol) {
            pat = &(table->patientList[j]);
            break;
        }
    }
    deleteDiseaseByCode(pat, code);

    printTable(table);

    system("pause");
    return 0;
};
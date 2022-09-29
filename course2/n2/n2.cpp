#include <iostream>
#include <fstream>
#include <vector>
#include "istream"
#include <string>

using namespace std;

const bool testMode = false;

struct scheduleRecord {
    int key;
    int groupId;
    char disciplineName[30];
    int paraNum;
    int weekNum;
    int weekDay;
    char typeOfClass[30];
    int roomNum;

    scheduleRecord(bool manualFill = false) {
        if (!manualFill) return;
        key = rand();
        cout << "write group id: ";
        cin >> groupId;
        cout << "write discipline name: ";
        cin >> disciplineName;
        cout << "write para number in schedule: ";
        cin >> paraNum;
        cout << "write week number: ";
        cin >> weekNum;
        cout << "write week day number: ";
        cin >> weekDay;
        cout << "write type of class (LECTURE/PRACTICE): ";
        cin >> typeOfClass;
        cout << "write room number: ";
        cin >> roomNum;
    }

    void print() {
        cout << "----record start----" << endl;
        cout << "key: " << key << endl;
        cout << "id: " << groupId << endl;
        cout << "disciplineName: " << disciplineName << endl;
        cout << "paraNum: " << paraNum << endl;
        cout << "weekNum: " << weekNum << endl;
        cout << "weekDay: " << weekDay << endl;
        cout << "typeOfClass: " << typeOfClass << endl;
        cout << "roomNum: " << roomNum << endl;
    }
};

template<class fileStream>
void openFile(fileStream &file, string FILE_NAME, const string &dir = "in", const string &type = "txt") {
    while (!file.is_open() || !file) {
        if (type == "binary") {
            if (dir == "in") file.open(FILE_NAME, ios::in | ios::binary);
            else file.open(FILE_NAME, ios::out | ios::binary);
        } else file.open(FILE_NAME);
        if (!file.is_open() || !file) {
            cout << "error occured while openning the file. write any number to try again or write 0 to exit." << endl;
            int r;
            cin >> r;
            if (r == 0)
                break;
        } else break;
    }
}

void createTxtFile(ofstream &file, const string &FILE_NAME) {
    openFile(file, FILE_NAME);
    cout << "write 0 for default values or 1 for manual input?" << endl;
    int ind;
    cin >> ind;

    if (testMode || ind == 0) {
        //int key; int groupId; char disciplineName[30]; int paraNum; int weekNum; int weekDay; char typeOfClass[30]; int roomNum;
        file << 2345 << endl << 12 << endl << "SIAOD" << endl << 2 << endl << 2 << endl << 2 << endl << "LECTURE"
             << endl << 4 << endl;
        file << 2323445 << endl << 12 << endl << "OCHM" << endl << 5 << endl << 3 << endl << 4 << endl << "PRACTICE"
             << endl << 2 << endl;
        file << 12345 << endl << 3 << endl << "MATH" << endl << 5 << endl << 3 << endl << 4 << endl << "PRACTICE"
             << endl << 2 << endl;
        file << 2908345 << endl << 3 << endl << "SIAOD" << endl << 3 << endl << 1 << endl << 3 << endl << "LECTURE"
             << endl << 17 << endl;
        file << 02323445 << endl << 3 << endl << "OCHM" << endl << 3 << endl << 2 << endl << 3 << endl << "LECTURE"
             << endl << 17 << endl;
    } else {
        cout << "how many records?" << endl;
        int colv;
        cin >> colv;
        for (int i = 0; i < colv; i++) {
            cout << endl << "------------------------------------" << endl;
            cout << "write " << i + 1 << " scheduleRecord: ";
            scheduleRecord *record = new scheduleRecord(true);
            file << record->key << endl << record->groupId << endl << record->disciplineName << endl << record->paraNum
                 << endl
                 << record->weekNum << endl << record->weekDay << endl << record->typeOfClass << endl << record->roomNum
                 << endl;
        }
    }
    file.close();
}

void createBinFromTxt(ifstream &readFile, ofstream &writeFile, const string &txtFileName, const string &binFileName) {
    openFile(readFile, txtFileName);
    openFile(writeFile, binFileName, "out", "binary");
    scheduleRecord rec;

    while (readFile >> rec.key >> rec.groupId >> rec.disciplineName >> rec.paraNum >> rec.weekNum >> rec.weekDay
                    >> rec.typeOfClass
                    >> rec.roomNum) {
        writeFile.write((char *) &rec, sizeof(scheduleRecord));
    }

    readFile.close();
    writeFile.close();
}

void createTxtFromBin(ifstream &readFile, ofstream &writeFile, const string &txtFileName, const string &binFileName) {
    openFile(readFile, binFileName, "in", "binary");
    openFile(writeFile, txtFileName);
    scheduleRecord rec;

    while (readFile.read((char *) &rec, sizeof(scheduleRecord)))
        writeFile << rec.key << endl << rec.groupId << endl << rec.disciplineName << endl << rec.paraNum << endl
                  << rec.weekNum << endl << rec.weekDay << endl << rec.typeOfClass << endl << rec.roomNum << endl;

    readFile.close();
    writeFile.close();
}

void printOutTxtFile(ifstream &file, const string &FILE_NAME) {
    openFile(file, FILE_NAME);

    string line;
    while (!file.eof()) {
        getline(file, line);
        cout << line << endl;
    }
    file.close();
}

void printOutBinFile(ifstream &readFile, const string &binFileName) {
    openFile(readFile, binFileName, "in", "binary");
    scheduleRecord record;

    for (int i = 1; readFile.read((char *) &record, sizeof(scheduleRecord)); i++) {
        cout << "item " << i << endl;
        record.print();
    }

    readFile.close();
}

vector<scheduleRecord> getScheduleFromBin(ifstream &readFile, const string &binFileName = "undefined") {
    bool opened = false;
    if (!readFile.is_open() && binFileName != "undefined") {
        opened = true;
        openFile(readFile, binFileName, "in", "binary");
    }
    scheduleRecord rec;
    vector<scheduleRecord> schedule;
    while (readFile.read((char *) &rec, sizeof(scheduleRecord))) {
        schedule.push_back(rec);
    }
    if (opened)
        readFile.close();
    return schedule;
}

scheduleRecord getScheduleItemByIndex(ifstream &readFile, int index, string direction = "beg",
                                      const string &binFileName = "undefined") {
    bool opened = false;
    if (!readFile.is_open() && binFileName != "undefined") {
        opened = true;
        openFile(readFile, binFileName, "in", "binary");
    } else direction = "cur";
    scheduleRecord rec;
    if (direction == "beg")
        readFile.seekg(sizeof(scheduleRecord) * (index - 1), ios::beg);
    else if (direction == "end")
        readFile.seekg(-sizeof(scheduleRecord) * (index + 1), ios::end);
    else
        readFile.seekg(sizeof(scheduleRecord) * (index - 1), ios::cur);
    readFile.read((char *) &rec, sizeof(scheduleRecord));
    if (opened)
        readFile.close();
    return rec;
}

void
deleteScheduleItemByKey(ifstream &readFile, ofstream &writeFile, int key,
                        const string &binFileName = "undefined") {
    scheduleRecord rec;
    scheduleRecord lastRec = getScheduleItemByIndex(readFile, 0, "end", binFileName);
    vector<scheduleRecord> newSchedule;
    openFile(readFile, binFileName, "in", "binary");
    while (readFile.read((char *) &rec, sizeof(scheduleRecord))) {
        if (rec.key == key) newSchedule.push_back(lastRec);
        else newSchedule.push_back(rec);
    }
    newSchedule.pop_back();
    readFile.close();
    openFile(writeFile, binFileName, "out", "binary");
    for (scheduleRecord rec2: newSchedule)
        writeFile.write((char *) &rec2, sizeof(scheduleRecord));
    writeFile.close();
}

void formScheduleByDay(ifstream &readFile, const string &binFileName, ofstream &writeFile,
                       const string &formedScheduleFileName) {
    openFile(writeFile, formedScheduleFileName, "out", "binary");

    int gotGroupId, gotWeekDay, gotWeekNum;
    if (testMode) {
        gotGroupId = 3;
        gotWeekDay = 3;
        gotWeekNum = 1;
    } else {
        cout << "write id of group" << endl;
        cin >> gotGroupId;
        cout << "write num of day" << endl;
        cin >> gotWeekDay;
        cout << "write num of week" << endl;
        cin >> gotWeekNum;
    }

    vector<scheduleRecord> schedule = getScheduleFromBin(readFile, binFileName);
    vector<scheduleRecord> formedSchedule;
    for (scheduleRecord record: schedule) {
        if (record.weekDay == gotWeekDay && record.groupId == gotGroupId && record.weekNum == gotWeekNum) {
            formedSchedule.push_back(record);
        }
    }

    sort(formedSchedule.begin(), formedSchedule.end(),
         [](const scheduleRecord &a, const scheduleRecord &b) { return a.paraNum < b.paraNum; });

    for (scheduleRecord rec: formedSchedule)
        writeFile.write((char *) &rec, sizeof(scheduleRecord));
    writeFile.close();
}

void refreshAndFixSchedule(ifstream &readFile, ofstream &writeFile, const string &binFileName) {
    vector<scheduleRecord> schedule = getScheduleFromBin(readFile, binFileName);
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; i < schedule.size() - 1; i++) {
            for (int j = i + 1; j < schedule.size(); j++) {
                if (schedule[i].paraNum == schedule[j].paraNum && schedule[i].weekNum == schedule[j].weekNum &&
                    schedule[i].weekDay == schedule[j].weekDay && schedule[i].roomNum == schedule[j].roomNum) {
                    srand(time(nullptr));
                    schedule[i].roomNum = rand() % 100;
                    changed = true;
                }
            }
        }
    }

    openFile(writeFile, binFileName, "out", "binary");
    for (scheduleRecord rec: schedule)
        writeFile.write((char *) &rec, sizeof(scheduleRecord));
    writeFile.close();
}

int main() {
    system("chcp 65001");
    ofstream writeFile;
    ifstream readFile;
    string fileName, binFileName, formedScheduleFileName;

    if (testMode) {
        fileName = "testData.txt";
        binFileName = "binTestData.txt";
        formedScheduleFileName = "formedSchedule_" + binFileName;
    } else {
        cout << "write file name" << endl;
        cin >> fileName;
        cout << "write binary file name" << endl;
        cin >> binFileName;
        cout << "write formedSchedule file name" << endl;
        cin >> formedScheduleFileName;
    }

    int menu = 1;
    while (menu != 0) {
        cout << "-----------------------------------------------------" << endl;
        cout << "1) create and fill txt file" << endl;
        cout << "2) print txt file" << endl;
        cout << "3) print bin file" << endl;
        cout << "4) form schedule for group for one day (task 1)" << endl;
        cout << "5) print formedSchedule bin file (after pt 4/task 1)" << endl;
        cout << "6) refresh and fix schedule (task 2)" << endl;
        cout << "7) create bin file from txt file" << endl;
        cout << "8) create txt file from bin file" << endl;
        cout << "9) write schedule item by index" << endl;
        cout << "10) delete schedule item by key" << endl;
        cout << "0) exit" << endl;
        cin >> menu;
        switch (menu) {
            case 0:
                return 0;
            case 1:
                createTxtFile(writeFile, fileName);
                break;
            case 2:
                printOutTxtFile(readFile, fileName);
                break;
            case 3:
                printOutBinFile(readFile, binFileName);
                break;
            case 4:
                formScheduleByDay(readFile, binFileName, writeFile, formedScheduleFileName);
                break;
            case 5:
                printOutBinFile(readFile, formedScheduleFileName);
                break;
            case 6:
                refreshAndFixSchedule(readFile, writeFile, binFileName);
                break;
            case 7:
                createBinFromTxt(readFile, writeFile, fileName, binFileName);
                break;
            case 8:
                createTxtFromBin(readFile, writeFile, fileName, binFileName);
                break;
            case 9: {
                cout << "write index" << endl;
                int index;
                cin >> index;
                getScheduleItemByIndex(readFile, index, "beg", binFileName).print();
                break;
            }
            case 10:
                cout << "write key" << endl;
                int key;
                cin >> key;
                deleteScheduleItemByKey(readFile, writeFile, key, binFileName);
                break;
            default:
                break;
        }
    }

    system("pause");

    return 0;
}
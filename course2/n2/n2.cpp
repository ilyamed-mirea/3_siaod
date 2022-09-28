#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "istream"
#include <algorithm>

using namespace std;

const bool testMode = true;

struct scheduleRecord {
    int groupId;
    char disciplineName[30];
    int paraNum;
    int weekNum;
    int weekDay;
    char typeOfClass[30];
    int lectureNum;
    scheduleRecord(){}
    scheduleRecord(bool manualFill) {
        if (!manualFill) return;
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
        cout << "write lecture number: ";
        cin >> lectureNum;
    }
    void print() {
        cout << "record start" << endl;
        cout << "id: " << groupId << endl;
        cout << "disciplineName: " << disciplineName << endl;
        cout << "weekNum: " << weekNum << endl;
        cout << "weekDay: " << weekDay << endl;
        cout << "typeOfClass: " << typeOfClass << endl;
        cout << "lectureNum: " << lectureNum << endl;
        cout << "record end" << endl;
    }
};

template <class fileStream>
void checkFileOpen(fileStream& file, string FILE_NAME,const string& type="txt",const string& dir="in") {
    while (!file) {
        cout << endl << !file << endl;
        if (type=="binary"){
            if (dir=="in") file.open(FILE_NAME,ios::in | ios::binary);
            else file.open(FILE_NAME,ios::out | ios::binary);
        }
        else file.open(FILE_NAME);
        cout << "error occured while openning the file. try again" << endl;
        int r;
        cin >> r;
        if (r == 0)
            break;
    }
}

void createTxtFile(ofstream& file, const string& FILE_NAME) {
    file.open(FILE_NAME);
    checkFileOpen(file, FILE_NAME);

    if (testMode) {
        file << 12 << endl << "SIAOD" << endl << 2 << endl << 2 << endl << 2 << endl << "LECTURE" << endl << 4 << endl;
        file << 12 << endl << "OCHM" << endl << 3 << endl << 2 << endl << 6 << endl << "PRACTICE" << endl << 2 << endl;
    }
    else {
        cout << "how many records?" << endl;
        int colv;
        cin >> colv;
        for (int i=0;i<colv;i++) {
            cout << endl << "------------------------------------" << endl;
            cout << "write " << i+1 << " scheduleRecord: ";
            scheduleRecord* record = new scheduleRecord(true);
            file << record->groupId << endl;
            file << record->disciplineName << endl;
            file << record->paraNum << endl;
            file << record->weekNum << endl;
            file << record->weekDay << endl;
            file << record->typeOfClass << endl;
            file << record->lectureNum << endl;
        }
    }
    file.close();
}

void createBinFromTxt(ifstream &readFile, ofstream &writeFile, const string& txtFileName, const string& binFileName) {
    readFile.open(txtFileName);
    checkFileOpen(readFile,txtFileName);
    writeFile.open(binFileName,ios::out | ios::binary);
    checkFileOpen(writeFile,binFileName,"binary","out");
    scheduleRecord rec;
    while (!readFile.eof()) {
        readFile>> rec.groupId >> rec.disciplineName  >> rec.paraNum >>rec.weekNum >> rec.weekDay >>rec.typeOfClass >> rec.lectureNum;
        writeFile.write((char *)&rec, sizeof(scheduleRecord));
    }
    readFile.close();
    writeFile.close();
}
void createTxtFromBin(ifstream &readFile, ofstream &writeFile, const string& txtFileName, const string& binFileName) {
    readFile.open( binFileName,ios::in | ios::binary);
    checkFileOpen(readFile,binFileName,"binary","in");
    writeFile.open(txtFileName);
    checkFileOpen(writeFile,txtFileName);
    scheduleRecord rec;
    while (!readFile.eof()) {
        readFile.read((char *)&rec, sizeof(scheduleRecord));
        writeFile << rec.groupId <<  endl << rec.disciplineName <<  endl << rec.paraNum <<  endl << rec.weekNum <<  endl << rec.weekDay <<  endl << rec.typeOfClass <<  endl << rec.lectureNum << endl;
    }
    readFile.close();
    writeFile.close();
}

void printOutFile(ifstream& file, const string& FILE_NAME) {
    file.open(FILE_NAME);
    checkFileOpen(file, FILE_NAME);

    string line;
    while (!file.eof()) {
        getline(file, line);
        cout << line << endl;
    }
    file.close();
}

void printOutBinFile(ifstream &readFile, const string& binFileName) {
    readFile.open(binFileName,ios::in | ios::binary);
    checkFileOpen(readFile,binFileName,"binary","in");
    //чтение из файла всей записи
    scheduleRecord record;
    int i = 0;
    while (!readFile.eof()) {
        readFile.read((char *)&record, sizeof(scheduleRecord));
        i++;
        cout << "item " << i << endl;
        record.print();
    }
    readFile.close();
}


bool recordsComparsion (const scheduleRecord& a,const scheduleRecord& b) {
    return a.lectureNum<b.lectureNum;
}

void formScheduleByDay(ifstream &readFile, const string& binFileName, ofstream &writeFile, const string& formedScheduleFileName) {
    readFile.open(binFileName,ios::in | ios::binary);
    checkFileOpen(readFile,binFileName,"binary","in");
    writeFile.open(formedScheduleFileName,ios::out | ios::binary);
    checkFileOpen(writeFile,binFileName,"binary","out");

    cout << "write id of group" << endl;
    int gotGroupId;
    cin >> gotGroupId;
    cout << "write num of day" << endl;
    int gotWeekDay;
    cin >> gotWeekDay;

    scheduleRecord record;
    vector<scheduleRecord> schedule;
    while (!readFile.eof()) {
        readFile.read((char *)&record, sizeof(scheduleRecord));
        if (record.weekDay==gotWeekDay && record.groupId==gotGroupId) {
            schedule.push_back(record);
        }
    }
    readFile.close();

    sort(schedule.begin(), schedule.end(), recordsComparsion);

    for (scheduleRecord rec: schedule)
        writeFile.write((char *)&rec, sizeof(scheduleRecord));
    writeFile.close();
}

int main() {
    system("chcp 65001");
    ofstream writeFile;
    ifstream readFile;
    string fileName,binFileName,formedScheduleFileName;

    if (testMode) {
        fileName = "testData.txt";
        binFileName = "binTestData.txt";
        formedScheduleFileName="formedSchedule_"+binFileName;
        createTxtFile(writeFile,fileName);
    }
    else {
        cout << "write file name" << endl;
        cin >> fileName;
        binFileName = "bin"+fileName;
        createTxtFile(writeFile,fileName);
    }

    //printOutFile(readFile,fileName);

    createBinFromTxt(readFile,writeFile,fileName, binFileName);
    printOutBinFile(readFile,binFileName);
    formScheduleByDay(readFile,binFileName,writeFile,formedScheduleFileName);
    printOutBinFile(readFile, formedScheduleFileName);


}
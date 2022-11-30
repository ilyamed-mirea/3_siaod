#include "fstream"
#include "iostream"
#include "istream"
#include <string>
using namespace std;
struct book
{
    string Fam;
    string Name;
    int year;
};
void create_bin_file(ifstream &ft, ofstream &fb)
{
    book x;
    while (!ft.eof())
    {
        getline(ft, x.Fam);
        ft >> x.year;
        ft.get();
        getline(ft, x.Name);
        fb.write((char *)&x, sizeof(book));
        fb.clear();
    }
    ft.close();
    fb.close();
}
void out_bin_file(ifstream &fb)
{
    book x;
    fb.read((char *)&x, sizeof(book));
    while (!fb.eof())
    {
        cout << x.Fam;
        cout << x.Name;
        cout << x.year;
        fb.read((char *)&x, sizeof(book));
    }
    fb.close();
}
void add_bin_file(string fnameBin)
{
    book x;
    ofstream fadd(fnameBin, ios::in | ios::binary | ios::app);
    cin >> x.Fam;
    cin >> x.Name;
    cin >> x.year;
    fadd.write((char *)&x, sizeof(book));
    fadd.close();
}
int main()
{
    system("chcp 65001");
    ifstream ft;
    ofstream fb;
    string fnameText, fnameBin;
    cout << "Name for Text";	fnameText="c.txt";
    cout << "Name for Text";	fnameBin="ce.txt";
    ft.open(fnameText);
    fb.open(fnameBin, ios::out | ios::binary);
    ifstream fbb(fnameBin, ios::in | ios::binary);
    if (!ft || !fb)
    {
        cout << "файл не открыт";
        return 1;
    }
    int num;
    while (1)
    {
        cout << " Operation for files" << endl;
        cout << " 1. Create for TextFile inBinFile"
             << endl;
        cout << " 2. OUT for BinFile" << endl;
        cout << " 3. Add record in BinFile" << endl;
        cout << " 4. EXIT" << endl;
        cout << "numPunkt="; cin >> num;
        switch (num)
        {
            case 1: create_bin_file(ft, fb); break;
            case 2: {out_bin_file(fbb);	break; }
            case 3: add_bin_file(fnameBin); break;
            case 4: exit(0);
        }
        if(!fbb.good())
        {
            cout << "err" << endl;
            return 1;
        }
    }
    return 0;
}

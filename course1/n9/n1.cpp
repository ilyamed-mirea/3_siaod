#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Specialize {
    int code; //ключ
    string name;
    bool operator==(const Specialize& other) const {
        return code == other.code;
    };
    bool operator!=(const Specialize& other) const {
        return code == other.code;
    };
    int operator-(const Specialize& other) const {
        return code - other.code;
    };
    Specialize(int code = 0, string name = "NO NAME") : code(code), name(name) {};
};
class Table {
    vector<Specialize> table;
public:
    long long cf = 0, mf = 0;
    void add(Specialize &obj) {
        table.push_back(obj);
    };
    int lineal_search(Specialize &obj) {
        for (auto& i : table)
            if (i == obj) return i.code;
        return 0;
    };
    int border_search(Specialize &obj) {
        table.push_back(obj);//барьерный объект
        int i = 0;
        while (table[i++] != obj); //ищем барьерный
        table.erase(--table.end());//удаляем барьерный элемент
        if (i <= table.size()) return table[i - 1].code;
        else return 0;
        //если зашли дальше размера вектора, значит ддошли до барьерного и не нашли obj
    };
    int interpolation_search(Specialize &obj) {
        long long l = 0, r = table.size() - 1, d, mid;
        while (table[l].code <= obj.code && table[r].code >= obj.code){
            d = (obj - table[l]) * (r - l) / (table[r] - table[l]);
            mid = l + d;
            if (table[mid] == obj) return table[mid].code;
            if (table[mid].code < obj.code) l = mid + 1;
            else r = mid - 1;
        };
        if (table[l] == obj) return table[l].code;
        else return -1;
    };
};

int main() {

}

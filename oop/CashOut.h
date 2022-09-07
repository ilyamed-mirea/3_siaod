#ifndef CashOut_h
#define CashOut_h

#include "base.h"

class CashOut : public base {
public:
    CashOut(base *head = nullptr, string name = "", int state = 0) : base(head,name,state) {};
    void pointerHandler(base* obj, string& text) {
        if (getState()) {
            base* root = getRoot(this);
            if (root->curStatus=="access") {
                int sum = stoi(text);
                int sumATM = (root->money[0]*5000)+(root->money[1]*2000)+(root->money[2]*1000)+(root->money[3]*500)+(root->money[4]*100);
                Person* user;
                for (int i = 0; i < root->persons.size(); i++) {
                    if (root->persons[i].status == 2) {
                        user = &root->persons[i];
                        break;
                    }
                }
                //cout << endl << "sum " << sum << " have " << sumATM << endl;
                if (user->amount < sum) { //недостаточно денег у человека
                    root->emit(SIGNAL_DEF(base, pointerSignal),this,root,text="poorMan");
                }
                else if (sumATM < sum) { //недостаточно денег у банкомата
                    root->emit(SIGNAL_DEF(base, pointerSignal),this,root,text="poorATM");
                }
                else if (sum%100!=0) {
                    root->emit(SIGNAL_DEF(base, pointerSignal),this,root,text="not100");
                }
                else { //если все ок
                    string res = "";
                    vector<int> moneyBackUp = root->money; //если вдруг в банкомате не хватит денег, восстановим отсюда
                    user->amount-=sum; //снятие денег у человека
                    int k5000 = 0,k2000 = 0,k1000 = 0,k500 = 0,k100 = 0; //количество купюр по номиналу
                    while (sum>=5000) { //пока сумма больше 5000 и в банкомате есть 5тысячные купюры
                        k5000+=1; //счетчик 5тыс увеличиваем на 1
                        sum-=5000; //сумма уменьшается на 5 тысяч
                        root->money[0]-=1; //колво пятитысячных в банкомате уменьшается на 1
                    }
                    while (sum>=2000) {
                        k2000+=1;
                        sum-=2000;
                        root->money[1]-=1;
                    }
                    while (sum>=1000) {
                        k1000+=1;
                        sum-=1000;
                        root->money[2]-=1;
                    }
                    while (sum>=500) {
                        k500+=1;
                        sum-=500;
                        root->money[3]-=1;
                    }
                    while (sum>=100) {
                        k100+=1;
                        sum-=100;
                        root->money[4]-=1;
                    }
                    //int sumATM2 = (root->money[0]*5000)+(root->money[1]*2000)+(root->money[2]*1000)+(root->money[3]*500)+(root->money[4]*100);

                    if (root->money[0]<0 || root->money[1]<0 || root->money[2]<0 || root->money[3]<0 || root->money[4]<0) { //в банкомате не хватило денег.. //покрывается верхней проверкой
                        root->emit(SIGNAL_DEF(base, pointerSignal),this,root,text="poorATM");
                        root->money = moneyBackUp; //восстановление колва денег до операции
                    } else {                 //                                                                                                                                         перед 100 два пробела?....
                        res = "Take the money: 5000 * " + to_string(k5000) + " rub., 2000 * " + to_string(k2000) + " rub., 1000 * " + to_string(k1000) + " rub., 500 * " + to_string(k500) + " rub.,  100 * " + to_string(k100) + " rub.";
                        root->emit(SIGNAL_DEF(base, pointerSignal),this,root,res); //отправка сигнала со списанными деньгами
                    }
                }
            }
        }
    }
};

#endif
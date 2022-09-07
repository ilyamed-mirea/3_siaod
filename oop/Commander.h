#ifndef Commander_h
#define Commander_h

#include "base.h"

class Commander : public base {
public:
    Commander(base *head = nullptr, string name = "", int state = 0) : base(head,name,state) {};
    void pointerHandler(base* obj, string& text) {
        if (!getState()) return;
        base *root = getRoot(this);
        string line;
        if (text == "INIT_CARD" || text=="INIT_MONEY") {
            while (line!="End card loading" && line!="End money loading") {
                getline(cin,line);
                if (line=="End card loading" || line=="End money loading") {
                    emit(SIGNAL_DEF(base, pointerSignal),this,root,line); //возврат успеха
                    break;
                }
                else if (text == "INIT_CARD")
                    emit(SIGNAL_DEF(base, pointerSignal),this,root,line = "Card "+line);
                else if(text=="INIT_MONEY")
                    emit(SIGNAL_DEF(base, pointerSignal),this,root,line = "Money "+line); //возврат успеха
            }
        }
        else if (text=="NEW_COMMAND") {
            getline(cin,line);
            //cout << endl << line << " " << root->curStatus << endl;
            if (line.find("End the session")!=string::npos ) {//&& root->curStatus =="access") {
                emit(SIGNAL_DEF(base, pointerSignal),this,root,line="logout"); //сброс состояний людей в 0
                return;
            }
            else if (line.find("SHOWTREE")!=string::npos) {
                root->printTreeReady();
                this->pointerHandler(this, line = "Turn off the ATM");
            }
            else if (root->curStatus == "card_checked" && line.find("PIN-code")==string::npos) {
                //emit(SIGNAL_DEF(base, pointerSignal),this,root,line="logout");
                emit(SIGNAL_DEF(base, pointerSignal), this, root, line="Ready to work");
            }
            else if (line.find("Turn off the ATM")!=string::npos) {
                //emit(SIGNAL_DEF(base, pointerSignal),this,root,line="logout");
                emit(SIGNAL_DEF(base, pointerSignal), this, root, line="off");
            }
            else if (line.find("Identification")!=string::npos && root->curStatus=="ready") {
                //if () {
                string cardNumStr = "ID"+line.substr(15);
                //cout << root->curStatus << endl;
                emit(SIGNAL_DEF(base, pointerSignal), this, root, cardNumStr);
                //}
            }
            else if (line.find("PIN-code")!=string::npos) {
                if (root->curStatus=="card_checked") {
                    string pinCode = "PIN"+line.substr(9);
                    //cout << root->curStatus << endl;
                    emit(SIGNAL_DEF(base, pointerSignal), this, root, pinCode);
                }
            }
                //else if () { //можно вводить комманды
            else if (line.find("Deposit money")!=string::npos && root->curStatus =="access") {
                //обрезает комманду
                //if (root->curStatus =="access")
                emit(SIGNAL_DEF(base, pointerSignal), this, root, line = "ADD"+line.substr(line.find("y")+2));
                //else
                //	emit(SIGNAL_DEF(base, pointerSignal),this,root,line="logout");//emit(SIGNAL_DEF(base, pointerSignal),this,root,line="Ready to work");
            }
            else if (line.find("Withdraw money")!=string::npos && root->curStatus =="access") {
                //if (root->curStatus =="access")
                //обрезает комманду
                emit(SIGNAL_DEF(base, pointerSignal), this, root, line = "WITHDRAW"+line.substr(line.find("y")+2));
                //else
                //	emit(SIGNAL_DEF(base, pointerSignal),this,root,line="logout");//emit(SIGNAL_DEF(base, pointerSignal),this,root,line="Ready to work");
            }

            else {//if (root->curStatus != "access" && root->curStatus != "ready"){
                emit(SIGNAL_DEF(base, pointerSignal),this,root,line="Ready to work");
                //cout << endl << "what is " << line << endl;

                //emit(SIGNAL_DEF(base, pointerSignal),this,root,line="logout");
                //cout << endl << "error from commander with line";
            }
        }
    }
};

#endif
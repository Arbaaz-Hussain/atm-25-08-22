#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

int last_acc_no();
void update_acc_no();

class account{
public:
    int acc_no;
    string name;
    int balance;
public:
    account(string name="",int balance=0){
        this->acc_no=last_acc_no();
        this->name=name;
        this->balance=balance;
    }
    friend istream& operator>>(istream& i,account &a);
    friend ostream& operator<<(ostream& o,account &a);
    
    friend ofstream& operator<<(ofstream& o,account &a);
    friend ifstream& operator>>(ifstream& i,account &a);
};
void transfer_amount(){
    cout<<"Enter account_no:";
    int num;     cin>>num;
    string s,str="account.txt";
    stringstream ss;
    ss<<num;
    ss>>s;
    s=s+str;
    ifstream ifs1(s);
    if (!ifs1) {
        cout<<"**no such account**"<<endl<<endl;
    }
    else{
    account a1;
    ifs1>>a1;
    
    cout<<"enter deposit account:";
    cin>>num;
    string s2;
    stringstream ss2;
    ss2<<num;
    ss2>>s2;
    s2=s2+str;
    ifstream ifs2(s2);
        if (!ifs2) {
            cout<<"**no such account**"<<endl<<endl;
        }
        else{
            account a2;
            ifs2>>a2;
            
            cout<<"how much want to transfer:";
            int cash;   cin>>cash;
            cout<<endl;
            if (a1.balance-cash<0) {
                cout<<"* Insufficient funds *"<<endl<<endl;
            }
            else{
                a1.balance=a1.balance-cash;
                a2.balance=a2.balance+cash;
                
                stringstream ss3;
                ss3<<a1.acc_no;
                string s3;
                ss3>>s3;
                s3=s3+str;
                ofstream ofs1(s3);
                ofs1<<a1;
                
                stringstream ss4;
                ss4<<a2.acc_no;
                string s4;
                ss4>>s4;
                s4=s4+str;
                ofstream ofs2(s4);
                ofs2<<a2;
            }
        }
    }
}
void close_an_account(){
    cout<<"enter account_no:";
    int num;    cin>>num;
    stringstream ss;
    ss<<num;
    string s,str="account.txt";
    ss>>s;
    s=s+str;
    ifstream ifs(s);
    account a;
    if (!ifs) {
        cout<<"**no such account**"<<endl<<endl;
    }
    else{
        ifs>>a;
        cout<<a;
        
        char c[1]="",ch[]="account.txt";
        stringstream ccc;
        
        ccc<<num;
        ccc>>c;
        strcat(c,ch);
        remove(c);
        ifs.close();
    }
}
void show_all_account(){
    int no_accounts=last_acc_no();
    for(int i=1;i<no_accounts;i++){
        int num=i;
        stringstream ss;
        ss<<num;
        string s,str="account.txt";
        ss>>s;
        s=s+str;
        ifstream ifs(s);
        account a;
        if (!ifs) {
            continue;
        }
        else{
            ifs>>a;
            cout<<a;
        }
    }
}
void cash_withdrawl(){
    cout<<"enter account number:";
    int num;    cin>>num;
    stringstream ss;
    ss<<num;
    string s,str="account.txt";
    ss>>s;
    s=s+str;
    ifstream ifs(s);
    account a;
    if (!ifs) {
        cout<<"**no such account**"<<endl<<endl;
    }
    else{
        ifs>>a;
        cout<<"enter the amount:";
        int cash; cin>>cash;
        int temp=a.balance-cash;
        if(temp>0){
            a.balance=a.balance-cash;
            stringstream ss;
            ss<<a.acc_no;
            string s,str="account.txt";
            ss>>s;
            s=s+str;
            ofstream ofs(s);
            ofs<<a;
        }
        else
            cout<<"* Insufficient funds *"<<endl;
        cout<<a;
    }
}
void cash_deposit(){
    cout<<"enter account number:";
    int num;    cin>>num;
    stringstream ss;
    ss<<num;
    string s,str="account.txt";
    ss>>s;
    s=s+str;
    ifstream ifs(s);
    account a;
    if (!ifs) {
        cout<<"**no such account**"<<endl;
    }
    else{
        ifs>>a;
        cout<<"enter the amount:";
        int cash; cin>>cash;
        a.balance=a.balance+cash;
        
        stringstream ss;
        ss<<a.acc_no;
        string s,str="account.txt";
        ss>>s;
        s=s+str;
        ofstream ofs(s);
        ofs<<a;
        
        cout<<a;
    }
}
void balance_enquiry(){
    cout<<"enter account_no:";
    int num;
    cin>>num;
    stringstream ss;
    ss<<num;
    string s,str="account.txt";
    ss>>s;
    s=s+str;
    ifstream ifs(s);
    account a;
    if (!ifs) {
        cout<<"**no such account**"<<endl;
    }
    else{
        ifs>>a;
        cout<<a;
    }
}
void create_account(){
    account a;
    cin>>a;
    cout<<"Congragulations account has been created:"<<endl<<endl;
    cout<<a;
    
    stringstream ss;
    ss<<a.acc_no;
    string s,str="account.txt";
    ss>>s;
    s=s+str;
    ofstream ofs(s);
    ofs<<a;
}
ifstream& operator>>(ifstream& i,account &a){
    i>>a.acc_no>>a.name>>a.balance;
    return i;
}
ofstream& operator<<(ofstream& o,account &a){
    o<<a.acc_no<<endl;
    o<<a.name<<endl;
    o<<a.balance<<endl;
    return o;
}
istream& operator>>(istream& i,account &a){
    a.acc_no=last_acc_no();
    update_acc_no();
    cout<<"name:";
    i>>a.name;
    cout<<"balance:";
    i>>a.balance;
    return i;
}
ostream& operator<<(ostream& o,account &a){
    o<<"acc_no="<<a.acc_no<<endl;
    o<<"name="<<a.name<<endl;
    o<<"balance="<<a.balance<<endl;
    o<<endl;
    return o;
}
int last_acc_no(){
    ifstream ifs("last_acc_no.txt");
    if (!ifs) {
        ofstream ofs("last_acc_no.txt");
        ofs<<1;
        return 1;
    }
    else{
        int num;
        ifs>>num;
        return num;
    }
}
void update_acc_no(){
    int num;
    ifstream ifs("last_acc_no.txt");
    ifs>>num;
    num++;
    ofstream ofs("last_acc_no.txt");
    ofs<<num;
}
int main() {
    while(1){
    int op;
    cout<<"BANKING SYSTEM:"<<endl;
    cout<<"(1)create account:"<<endl;
    cout<<"(2)balance enquiry"<<endl;
    cout<<"(3)cash deposit"<<endl;
    cout<<"(4)cash withdarawl"<<endl;
    cout<<"(5)close an account"<<endl;
    cout<<"(6)show all account"<<endl;
    cout<<"(7)Transfer amount"<<endl;
    cout<<"(8)EXIT"<<endl;
    cout<<"give an option=";
    cin>>op;
    cout<<endl;
    switch (op) {
        case 1:
            create_account();
            break;
        case 2:
            balance_enquiry();
            break;
        case 3:
            cash_deposit();
            break;
        case 4:
            cash_withdrawl();
            break;
        case 5:
            close_an_account();
            break;
        case 6:
            show_all_account();
            break;
        case 7:
            transfer_amount();
            break;
        case 8:
            exit(0);
        default:
            cout<<"provide a proper option"<<endl;
            break;
    }
    }
    return 0;
}
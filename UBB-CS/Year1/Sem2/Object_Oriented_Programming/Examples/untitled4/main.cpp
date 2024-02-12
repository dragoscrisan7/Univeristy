#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Channel{
public:
    virtual void send() = 0;
    virtual ~Channel() = default;
};

class Telephone: public Channel{
private:
    string number;
public:
    Telephone(const string& number): number(number){}
    virtual void send() override{
        int r = rand() %2;
        if(r == 1)
            throw exception();
        else{
            cout<<"dialing "<<number;
        }
    }
};
class Fax: public Telephone{
public:
    Fax(string& number) : Telephone(number){}
    void send() override{ int r = rand() %2;
        if(r == 1)
            throw exception();
        else{
            cout<<"sending fax\n";
        }}
};
class SMS: public Telephone{
public:
    SMS(string& number) : Telephone(number){}
    void send() override {
        int r = rand() % 2;
        if (r == 1)
            throw exception();
        else {
            cout << "sending sms\n";
        }
    }
};
class Failover: public Channel{
private:
    Channel *c1, *c2;
public:
    void send(string& number){
        try{
            Fax f(number);
            f.send();
        }catch(exception& e){
            cout<<e.what();
            SMS s(number);
            try {
                s.send();
            }
            catch(exception& e){
                cout<<e.what();
            }
        }
    }
};

class Contact{
private:
    Channel *c1, *c2, *c3;
public:
    Contact(Channel *c1, Channel *c2, Channel *c3): c1(c1), c2(c2), c3(c3){}
    void send_allarm(){
        while(1){
            try{
                c1->send();
                break;
            }
            catch(exception& e) {}
            try{
                c2->send();
                break;
            }
            catch(exception& e) {}
            try{
                c3->send();
                break;
            }
            catch(exception& e) {}
        }
    }
    ~Contact(){delete c1; delete c2; delete c3;}
};

int main() {
    srand(time(NULL));
    string message = "911";
    auto *t = new Telephone(message);
    auto *f = new Fax(message);
    auto *s = new SMS(message);
    Contact* c = new Contact(t,f,s);
    c->send_allarm();
    delete c;
}
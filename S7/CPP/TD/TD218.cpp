#include <iostream>
using namespace std;

class B {
public:
    virtual void show() = 0;
};

class D1: public B {
};

class D2: public B {
    void show() { cout << "ok!\n"; }
};

class D3 {
public:
    void show() { cout << "D2 says: "; /* B::*/ show() ; }
};

int main() {
   //B *b = new B;
   //D1 *d1 = new D1;
   D2 *d2 = new D2;
   B *p = new D2;
   p->show();
   D3 d3;
   d3.show();

    return 0;
}
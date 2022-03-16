#include <iostream>
using namespace std;

class P {
public:
    void f1() { cout << "f1 from P\n"; }
    virtual void f2() { cout << "f2 from P\n"; }
    virtual void f3() { cout << "f3 from P\n"; }
    void f1(int x) { cout << "f4 from P\n"; }
};

class Q: public P {
public:
    void f1() { cout << "f1 from Q\n"; }
    /* virtual */ void f2() override { cout << "f2 from Q\n"; }
};

class R: public Q { };

int main() {
    R r;
    cout << "R:\n";
    r.f1();
    r.f2();
    r.f3();

    P *p = &r;
    cout << "P\n";
    p->f1();
    p->f2();
    p->f3();

    //r.f1(0);
    P& pr = r;
    //R& rr = pr;
    R& rr = dynamic_cast<R&>(pr);

    return 0;
}
#include <iostream>
using namespace std;

class B1 {
public:
    B1() { cout << "B1 constructed!" << endl; }
    //virtual donc B1 est classe virtuelle capable de se souvenir de sa vraie classe (D par exemple q2)
    virtual ~B1() { cout << "B1 destructed!" << endl; }
};

class B2 {
public:
    B2() { cout << "B2 constructed!" << endl; }
    ~B2() { cout << "B2 destructed!" << endl; }
};

class D: public B1, public B2 {
public:
    D() { cout << "D constructed!" << endl; }
    ~D() { cout << "D destructed!" << endl; }
};

int main() {
    //D d;
    //cout << "au milieu\n";

    B1 *b1 = new D();
    cout << "1\n";
    delete b1;
    cout << "2\n";

    return 0;
}
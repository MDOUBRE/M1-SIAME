#include <iostream>
using namespace std;

class Expr {
    virtual float eval(float x) const = 0; //quand on met =0 ca veut dire qu'on déclare la fonction comme étant purement virtuelle
    virtual void print(ostream& out) const = 0;
};

class Const: public Expr {
public:
    Const(float c): c(c) { }
    float eval(float x) const override { return c; }
    void print(ostream& out) const override { out << c; }
private:
    float c;
};

// 3. Définissez la classe var. Expression -> x
// Var x; x.eval(3) = 3
class Var : public Expr{
public:
    float eval(float x) const override { return x; }
    void print (ostream& out) const override { out << 'x'; }
};

class Neg: public Expr{
private:
    const Expr& _g;
public:
    Neg(const Expr& g): _g(g) { cout << "DEBUG: " << &g << endl; }
    float eval(float x) const override { return -_g.eval(x); }
    void print (ostream& out) const override {
        out << '-';
        _g.print(out);
        out << " (" << &_g << ") ";
    }
};

int main() {
   Const two(2.0);
   Var x;

   cout << "f(x) = "; two.print(cout); cout << endl;
   cout << "g(x) = "; x.print(cout); cout << endl;

   cout << "f(3.14) = " << two.eval(3.14) << endl;
   cout << "g(3.14) = " << x.eval(3.14) << endl;

   Neg n1(x);
   Neg n2(static_cast<const Expr&>(n1));

   cout << n1.eval(3.14) << endl;
   cout << n2.eval(3.14) << endl;
   cout << &x << endl;
   n1.print(cout); cout << endl;
   n2.print(cout); cout << endl;
    return 0;
}
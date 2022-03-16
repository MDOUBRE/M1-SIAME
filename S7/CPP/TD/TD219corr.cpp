// Exercice 19
#include <iostream>
#include <math.h>
using namespace std;

class Expr {

// 1-2 Que manque-t-il dans la déclaration de Expr ci-dessus pour qu’elle soit une classe de base acceptable ?
public:		// 1
	virtual float eval(float x) const = 0;			// 1-2
	virtual void print(ostream& out) const = 0;		// 1-2

    float operator()(float x) const { return eval(x); }
};

ostream& operator<<(ostream& out, const Expr& e){
    e.print(out);
    return out;
}

class Const: public Expr {
public:
	Const(float c): c(c) { }
	float eval(float x) const override { return c; }
	void print(ostream& out) const override { out << c; }
private:
	float c;
};

// 3. Définissez la classe var. Expression -> x
//	Var x; x.eval(3) = 3
class Var : public Expr{	// f(x) = x
public:
    float eval(float x)  const override { return x; }
    void print (ostream & out) const override { out << 'x';}
};

// 4. Définissez la classe Neg qui inverse la signe de l’expression qu’elle prend en paramètre. Un choix de gestion de la mémoire doit être fait : que décidez-vous ?
// f(x) = -g(x)

class Neg : public Expr{
private :
	const Expr& _g;
	//Neg(const Neg& x): _g(x._g) { }
public :
    Neg(const Expr& g): _g(g) { cout << "DEBUG: " << &g << endl; }
    //Neg(const Neg& x) = delete;
    float eval(float x)  const override { return -_g.eval(x);}
    void print (ostream & out) const override {
		out << '-' << _g;
        /*
        out << '-';
		_g.print(out);
		out << " (" << &_g << ") ";
        */
	}
};

class BinOp: public Expr{
public:    
    BinOp(const Expr& f1, const Expr& f2): f1(f1), f2(f2) { }

    float eval(float x) const override { return compute(f1.eval(x), f2.eval(x)); }
    void print (ostream& out) const override {
        out << "(" << f1 << op() << f2 << ")"; }
    virtual float compute(float x, float y) const = 0;
    virtual string op() const =0;

private:
    const Expr& f1;
    const Expr& f2;

};

class Add: public BinOp{
public:
    using BinOp::BinOp;

    float compute(float x, float y) const override { return x + y; }
    string op() const override { return " + "; }
    /*
    Add(const Expr& f1, const Expr&f2): f1(f1), f2(f2) { }
    float eval(float x) const override { return f1.eval(x) + f2.eval(x); }
    void print(ostream& out) const override {
        //Pour ac on surcharge l'opérateur <<
        // A chaque appel de << ca appelle la surcharge de << dans laquelle le print fait appel au print de Expr
        out << "(" << f1 << "+" << f2 << ")";
        //la on a pas surchargé l'opérateur donc obligé de faire des out et appels à print
        
        out << "(";
        f1.print(out);
        out << " + ";
        f2.print(out);
        out << ")";
        
    }
    */
    /*
private:
    const Expr& f1;
    const Expr& f2;
    */

};

class Sub: public BinOp{
public:
    using BinOp::BinOp;

    float compute(float x, float y) const override { return x - y; }
    string op() const override { return " - "; }
};

class Mul: public BinOp{
public:
    using BinOp::BinOp;

    float compute(float x, float y) const override { return x * y; }
    string op() const override { return " * "; }
};

class Div: public BinOp{
public:
    using BinOp::BinOp;

    float compute(float x, float y) const override { return x / y; }
    string op() const override { return " / "; }
};

class Pow: public BinOp{
public:
    using BinOp::BinOp;

    float compute(float x, float y) const override { return pow(x,y); }
    string op() const override { return " ^ "; }
};

Add make() {
    Var x;
    Const two(2.0);
    Const three(3.0);
    Const one(1.0);
    return Add(Sub(Pow(x,two), Mul(three,x)), Div(one,x));
}

int main() {
	Const two(2.0);
    Const three(3.0);
    Const one(1.0);
	Var x;

    /*
	cout << "f(x) = "; two.print(cout); cout << endl;
	cout << "g(x) = "; x.print(cout); cout << endl;

	cout << "f(3.14) = " << two.eval(3.14) << endl;
	cout << "g(3.14) = " << x.eval(3.14) << endl;

	Neg n1(x);
	Neg n2(static_cast<const Expr&>(n1));
    Add a(x,two);
    */
    /*
	cout << n1.eval(3.14) << endl;
	cout << n2.eval(3.14) << endl;
	cout << &x << endl;
	n1.print(cout); cout << endl;
	n2.print(cout); cout << endl;
	*/
    //cout << "5 = " << a.eval(3) << endl;

    Pow t1(x,two);
    Mul t2(three,x);
    Sub t3(t1,t2);
    Div t4(one,x);
    Add f(t3,t4);

    /*
    cout << f.eval(3) << endl;
    cout << f.eval(4) << endl;

    auto f2 = Add(Sub(Pow(x,two), Mul(three,x)), Div(one,x));
    //auto f2 = make(); //fait péter une segfault!!
    cout << f2.eval(3) << endl;
    cout << f2.eval(4) << endl;
    */
    float l, u, e;
    cin >> l;
    cin >> u;
    cin >> e;
    for(auto x = l; x<=u;x+=e){
        cout << "f(" << x << ") = " << f(x) << endl;
    }

	return 0;
}

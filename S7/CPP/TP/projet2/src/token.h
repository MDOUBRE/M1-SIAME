#include <iostream>

// Enumération Type
// le type d'un Token peut être un de ceux contenu dans l'enum
enum class Type : char{
    plus = '+',
    minus = '-',
    mul = '*',
    div = '/',
    equal = '=',
    lp = '(',
    rp = ')',
    number = ';',
    pos = '&',
    neg = '!',
    cos = 'c',
    sin = 's',
    tan = 't',
    sqrt = 'r',
    log = 'g',
    exp = 'e',
    pow = 'o',
    hypot = 'h',
    lerp = 'l',
    polynome = 'p'
};

class Token {
public:
    Token();
    Token(std::string *str, Type type, Type type2, double val): strtok{str}, typetok{type}, typeSigne{type2}, valtok{val} {}
    Token(std::string &str, Type type, Type type2, double val): strtok{&str}, typetok{type}, typeSigne{type2}, valtok{val} {}

    // renvoie true si le token a un type correspondant à plus, minus, mul ou div, false sinon
    bool isOperator();

    // renvoie true si le type est 'number', false sinon
    bool isNumber();

    // renvoie true si le type est corresonpdant à lp ou rp, false sinon
    bool isPar();

    // renvoie true si le type correspond à une des fonctions possibles
    bool isFunct();

    // renvoie le type contenu dans la variable typetok
    Type getType();

    // renvoie pos ou neg selon si la valeur est positive ou négative
    Type getTypeSign();

    // on modifie la string str
    void setStr(std::string &str);

    // on change le signe en le mettant à positif
    void setSign();

    // renvoie la valeur du type, par exemple '(' si type=lp
    string getTypeVal();

    // renvoie la valeur contenue dans la variable valtok
    double getVal();

    // on modifie la valeur valtok par un double passé en paramètres
    void setVal(double dbl);

private:
    // caractère(s) du token
    std::string *strtok;

    // type du token
    Type typetok;
    
    // type du signe du token
    Type typeSigne;

    //valeur du token
    double valtok;
};
#include <iostream>
using namespace std;

#include "token.h"

bool Token::isOperator(){
    return ((typetok==Type::plus) || (typetok==Type::minus) || (typetok==Type::mul) || (typetok==Type::div));
}

bool Token::isNumber(){
    return typetok==Type::number;
}

bool Token::isPar(){
    return ((typetok==Type::lp) || (typetok==Type::rp));
}

bool Token::isFunct(){
    return ((typetok==Type::cos) || (typetok==Type::sin) || (typetok==Type::tan) || (typetok==Type::sqrt) || (typetok==Type::log) || (typetok==Type::exp) || (typetok==Type::pow) || (typetok==Type::hypot) || (typetok==Type::lerp) || (typetok==Type::polynome));
}

Type Token::getType(){
    return typetok;
}

Type Token::getTypeSign(){
    return typeSigne;
}

void Token::setStr(string &str){
    *strtok=str;
    cout << strtok << endl;
}

void Token::setSign(){
    typeSigne=Type::pos;
}

string Token::getTypeVal(){
    switch (typetok)
    {
    case Type::plus :
        return "+";
        break;
    case Type::minus :
        return "-";
        break;
    case Type::mul :
        return "*";
        break;
    case Type::div :
        return "/";
        break;
    case Type::lp :
        return "(";
        break;
    case Type::rp :
        return ")";
        break; 
    case Type::cos :
        return "cos";
        break;
    case Type::sin :
        return "sin";
        break;
    case Type::tan :
        return "tan";
        break;
    case Type::sqrt :
        return "sqrt";
        break;
    case Type::log :
        return "log";
        break;
    case Type::exp :
        return "exp";
        break;
    case Type::pow :
        return "pow";
        break;
    case Type::hypot :
        return "hypot";
        break;
    case Type::lerp :
        return "lerp";
        break;
    case Type::polynome :
        return "polynome";
        break;
    default:
        break;
    }    
   return "E";
}

double Token::getVal(){
    return valtok;
}

void Token::setVal(double dbl){
    valtok=dbl;
}


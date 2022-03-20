#include <list>
#include <sstream>
#include <iostream>
#include <math.h>
using namespace std;

#include "tokenstring.h"

// Cette méthode est celle qui tokenise notre expression
void Tokenstring::tok(string str)
{
    build_fct_table();
    tokenString.clear();
    string nameVarFunc{""};     // cette string contiendra les noms de fonctions
    string numb{""};            // cette string contiendra les valeurs de double
    for(char c : str){
        string strtmp{""};
        // cas ou notre charcatère n'est ni une lettre ni un chiffre ni un point, donc un opérand
        if(!(isdigit(c)) && !(isalpha(c)) && c!='.')
        {
            // on teste si on a une fonction ou un nom de variable dans notre variable 'nameVarFunc'
            if(!(nameVarFunc.empty()))
            {
                // on test si c'est une fonction
                if(isFct(nameVarFunc)==true)   
                {
                    // si c'est le cas on traite chaque fonction
                    // on crée un Token associé selon la fonction
                    if (nameVarFunc=="cos"){
                        tokenString.push_back(Token{nameVarFunc,Type::cos,Type::pos,0.0});
                    }
                    else if(nameVarFunc=="sin"){
                        tokenString.push_back(Token{nameVarFunc,Type::sin,Type::pos,0.0});
                    }
                    else if(nameVarFunc=="tan"){
                        tokenString.push_back(Token{nameVarFunc,Type::tan,Type::pos,0.0});
                    }
                    else if(nameVarFunc=="sqrt"){
                        tokenString.push_back(Token{nameVarFunc,Type::sqrt,Type::pos,0.0});
                    }
                    else if(nameVarFunc=="log"){
                        tokenString.push_back(Token{nameVarFunc,Type::log,Type::pos,0.0});
                    }
                    else if(nameVarFunc=="exp"){
                        tokenString.push_back(Token{nameVarFunc,Type::exp,Type::pos,0.0});
                    }
                    else if(nameVarFunc=="pow"){
                        tokenString.push_back(Token{nameVarFunc,Type::pow,Type::pos,0.0});
                    }
                    else if(nameVarFunc=="hypot"){
                        tokenString.push_back(Token{nameVarFunc,Type::hypot,Type::pos,0.0});
                    }
                    else if(nameVarFunc=="lerp"){
                        tokenString.push_back(Token{nameVarFunc,Type::lerp,Type::pos,0.0});
                    }
                    else if(nameVarFunc=="polynome"){
                        tokenString.push_back(Token{nameVarFunc,Type::polynome,Type::pos,0.0});
                    }                    
                }
                // sinon c'est une variable
                else{                          
                    // on va chercher dans la mémoire la valeur associée à cette variable et on crée un Token avec cette valeur
                    double resVar=memory.find(nameVarFunc)->second;
                    tokenString.push_back(Token{nameVarFunc,Type::number,Type::pos,resVar});
                }
                // on oublie pas de clear() notre string pour la prochaine variable ou fonction
                nameVarFunc.clear();
            }
            // on test si on a un nombre dans la string numb
            else if(!(numb.empty()))
            {
                // si c'est le cas on la convertit en double et on crée un Token avec cette valeur
                double number=stod(numb);
                tokenString.push_back(Token{numb,Type::number,Type::pos,number});
                // on oublie pas de clear() notre string pour la prochaine valeur
                numb.clear();
            }
        }
        // selon notre caractère on le met dans nameVarFunc ou numb ou alors on crée direct un Token pour les opérands
        if(isalpha(c))
        {
            nameVarFunc.push_back(c);
        }
        else if(isdigit(c) || c=='.')
        {
            numb.push_back(c);
        }
        else if(c=='+')
        {
            strtmp+=c;
            tokenString.push_back(Token{strtmp,Type::plus,Type::pos,0.0});
        }
        else if(c=='-')
        {
            strtmp+=c;
            tokenString.push_back(Token{strtmp,Type::minus,Type::pos,0.0});
        }
        else if(c=='*')
        {
            strtmp+=c;
            tokenString.push_back(Token{strtmp,Type::mul,Type::pos,0.0});
        }
        else if(c=='/')
        {
            strtmp+=c;
            tokenString.push_back(Token{strtmp,Type::div,Type::pos,0.0});
        }
        else if(c=='(')
        {
            strtmp+=c;
            tokenString.push_back(Token{strtmp,Type::lp,Type::pos,0.0});
        }
        else if(c==')')
        {
            strtmp+=c;
            tokenString.push_back(Token{strtmp,Type::rp,Type::pos,0.0});
        }
        // on oublie pas de remettre à vide notre string pour la prochaine expression
        strtmp="";
    }
    // on traite nos string si elles ne sont aps vides afin de ne pas oublier des membres de l'expression
    if(!(nameVarFunc.empty())){
        if(isFct(nameVarFunc)){
            if (nameVarFunc=="cos"){
                tokenString.push_back(Token{nameVarFunc,Type::cos,Type::pos,0.0});
            }
            else if(nameVarFunc=="sin"){
                tokenString.push_back(Token{nameVarFunc,Type::sin,Type::pos,0.0});
            }
            else if(nameVarFunc=="tan"){
                tokenString.push_back(Token{nameVarFunc,Type::tan,Type::pos,0.0});
            }
            else if(nameVarFunc=="sqrt"){
                tokenString.push_back(Token{nameVarFunc,Type::sqrt,Type::pos,0.0});
            }
            else if(nameVarFunc=="log"){
                tokenString.push_back(Token{nameVarFunc,Type::log,Type::pos,0.0});
            }
            else if(nameVarFunc=="exp"){
                tokenString.push_back(Token{nameVarFunc,Type::exp,Type::pos,0.0});
            }
            else if(nameVarFunc=="pow"){
                tokenString.push_back(Token{nameVarFunc,Type::pow,Type::pos,0.0});
            }
            else if(nameVarFunc=="hypot"){
                tokenString.push_back(Token{nameVarFunc,Type::hypot,Type::pos,0.0});
            }
            else if(nameVarFunc=="lerp"){
                tokenString.push_back(Token{nameVarFunc,Type::lerp,Type::pos,0.0});
            }
            else if(nameVarFunc=="polynome"){
                tokenString.push_back(Token{nameVarFunc,Type::polynome,Type::pos,0.0});
            }
        }
        else{
            double resVar=memory.find(nameVarFunc)->second;
            tokenString.push_back(Token{nameVarFunc,Type::number,Type::pos,resVar});
        }
        nameVarFunc.clear();
    }
    else if(!(numb.empty())){
        double number=stod(numb);
        tokenString.push_back(Token{numb,Type::number,Type::pos,number});
        numb.clear();
    }
}

// Cette méthode affiche la liste des Token de l'expression
void Tokenstring::print(){
    cout << endl << "Liste de token pour l'expression " << *_chaine << " :" << endl;
    for(Token tok: tokenString){
        string ctmp{""};
        if(tok.isNumber()){
            cout << "number(" << tok.getVal() << ")" << endl;
        }
        else if(tok.isOperator()){
            ctmp=tok.getTypeVal();
            cout << "operator(" << ctmp << ")" << endl;
        }
        else if(tok.isFunct()){
            ctmp=tok.getTypeVal();
            cout << "fct(" << ctmp << ")" << endl;
        }
        else{
            ctmp=tok.getTypeVal();
            cout << "par('" << ctmp << "')" << endl;
        }
    }
}

// Cette méthode renvoie la taille de la liste des Token
int Tokenstring::sizeListTok(){
    return tokenString.size();
}

// Cette méthode vide la liste des Token
void Tokenstring::free(){
    tokenString.clear();
}

// Cette méthode renvoie la list de Token 'tokenString'
list<Token> Tokenstring::getListToken(){
    return tokenString;
}

// Cette méthode teste si on a une fonction à v variables
// elle prend en argument une string qui est le nom de la fonction
// elle renvoie true si le nom de la fonction correspond à la fonction dans la table des fonctions, false sinon
bool Tokenstring::isVaraires(string Id){
    auto v = _vaires.find(Id);
    if(v!=_vaires.end()){
        return true;
    }
    return false;
}

// Cette méthode teste si on a une fonction à n variables
// elle prend en argument une string qui est le nom de la fonction
// elle renvoie true si le nom de la fonction correspond à la fonction dans la table des fonctions, false sinon
bool Tokenstring::isFct(string Id){
    auto f=_naires.find(Id);
    if(f!=_naires.end()){
        return true;
    }
    return isVaraires(Id);
}

// Cette méthode initialise la table des fonctions
// elle ne renvoie rien
void Tokenstring::build_fct_table(){
    _naires[string("sin")] = make_pair(1, [](const DoubleParams& x)->double{ return sin(x[0]); });
    _naires[string("cos")] = make_pair(1, [](const DoubleParams& x)->double{ return cos(x[0]); });
    _naires[string("tan")] = make_pair(1, [](const DoubleParams& x)->double{ return tan(x[0]); });
    _naires[string("sqrt")] = make_pair(1, [](const DoubleParams& x)->double{ return sqrt(x[0]); });
    _naires[string("log")] = make_pair(1, [](const DoubleParams& x)->double{ return log(x[0]); });
    _naires[string("exp")] = make_pair(1, [](const DoubleParams& x)->double{ return exp(x[0]); });
    _naires[string("pow")] = make_pair(1, [](const DoubleParams& p)->double{ return pow(p[0],p[1]); });
    _naires[string("hypot")] = make_pair(1, [](const DoubleParams& p)->double{ return hypot(p[0],p[1]); });
    _naires[string("lerp")] = make_pair(1, [](const DoubleParams& p)->double{ return /*(1-p[2])*p[0]+p[2]*p[1]*/ p[0]*(1-p[2])+p[1]*p[2]; });

    _vaires[string("polynome")] = make_pair(1, [](const DoubleParams& p)->double {
        if(p.size()!= p[0]+3){
            throw Tokenstring::Error("polynome() ==> mauvais nombre d'arguments");
        }
        double x=p[p.size()-1];
        double res=0;
        for(int i=p.size()-2;i>0;i--){
            res=res*x+p[i];
        }
        return res;
    });
}


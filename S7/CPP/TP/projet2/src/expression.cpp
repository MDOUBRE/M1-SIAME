#include <iostream>
using namespace std;
#include <list>
#include <math.h>

#include "expression.h"

// Cette méthode fait l'évaluation de l'expression à partir de la list RPN
// elle utilise la liste RPN et une pile dans lauqelle on aura le résultat final
double Expression::eval(){
    list<Token> pile;
    while(!(listRPN.empty())){
        if(listRPN.front().isNumber()){
            pile.push_back(listRPN.front());
            listRPN.pop_front();
        }
        else if(listRPN.front().isOperator()){
            double tmp1=pile.back().getVal();
            // on teste si le 'TypeSigne' est négative et on fait -val si c'est le cas
            if(pile.back().getTypeSign()==Type::neg){
                tmp1=-tmp1;
            }
            pile.pop_back();
            double tmp2=pile.back().getVal();
            if(pile.back().getTypeSign()==Type::neg){
                tmp2=-tmp2;
                pile.back().setSign();
            }
            double res=op(listRPN.front().getType(), tmp2, tmp1);
            pile.back().setVal(res);
            listRPN.pop_front();
        }
        else{
            listRPN.pop_front();
        }
    }
    if(pile.back().getTypeSign()==Type::neg){
        return -pile.back().getVal();
    }
    return pile.back().getVal();
}

// Cette méthode fait les opérations
// Elle prend en paramètre un Type qui sert à féterminer l'opérand
// deux double sur lesquels on fait le calcul
double Expression::op(Type type, double d1, double d2){
    if(type==Type::plus){
        return d1+d2;
    }
    else if(type==Type::minus){
        return d1-d2;
    }
    else if(type==Type::mul){
        return d1*d2;
    }
    else if(type==Type::div){
        return d1/d2;
    }
    else{
        return 0;
    }
}

// on appelle la fonction adéquate pour parser selon si on a des paranthèses ou pas dans l'expression
void Expression::parse(){
    bool norm{true};
    for (Token tok:listTokExpr)
    {
        if(tok.isPar()){
            norm=false;
        }
    }
    if(norm==true){
        parseNorm();
    }
    else{
        parsePar();
    }      

}
// Token en RPN à partir d'expression sans paranthèses
void Expression::parseNorm(){
    list<Token> pile;
    for(Token tok:listTokExpr){
        if(tok.isNumber()){
            listRPN.push_back(tok);
        }
        else{
            if(tok.getType()==Type::mul || tok.getType()==Type::div){
                while(pile.back().getType()==Type::div || pile.back().getType()==Type::mul){
                    listRPN.push_back(pile.back());
                    pile.pop_back();
                }
                pile.push_back(tok);
            }
            else{
                while(!(pile.empty())){
                    listRPN.push_back(pile.back());
                    pile.pop_back();
                }
                pile.push_back(tok);
            }
        }
    }
    while(!(pile.empty())){
        listRPN.push_back(pile.back());
        pile.pop_back();
    }
}

// Token en RPN à partir d'expression avec paranthèses
void Expression::parsePar(){
    build_fct_table();
    list<Token> pile;
    bool fct{false};
    for(Token tok:listTokExpr){
        if(tok.isNumber()){
            if(fct==true){
                pile.push_back(tok);
            }
            else{
                listRPN.push_back(tok);
            }
        }
        else if(tok.getType()==Type::lp || tok.isFunct()){
            // on teste si on a une fonction ou pas et on passe un bool à true si c'est le cas
            if(tok.isFunct()){
                fct=true;
            }
            pile.push_back(tok);
        }
        else if(tok.getType()==Type::rp){
            // on regarde si on était dans les arg d'une fonction
            // si c'est le cas on fait le traitement en conséquence
            if(fct==true)
            {
                // ce vecteur tab nous sert à trouver les arguments
                vector<double> tab{};
                tab.clear();
                double res{};           // resultat de la fonction avec ses arguments
                double taille{};        // taille de tab
                // on met dans tab les arguments pour calculer le résultat
                while(pile.back().getType()!=Type::lp){
                    tab.push_back(pile.back().getVal());
                    pile.pop_back();
                }
                pile.pop_back();
                // on teste chaque fonction et rentre dans celle qui correspond
                if(pile.back().getType()==Type::cos){
                    auto n = _naires.find("cos");
                    DoubleParams params(n->second.first);
                    params.clear();
                    taille=tab.size();
                    // on remet les paramètre dans le bon sens et dans notre tableau de paramètres 'params'
                    for(double i=0;i<taille;i=i+1){
                        params.push_back(tab.back());
                        tab.pop_back();
                    }
                    // on calcule le résultat
                    res=(n->second.second(params));
                    string val=to_string(res);
                    // si le résultat est négatif on crée un token avec TypeSigne=neg
                    if(res<0){
                        res=res-2*res;
                        listRPN.push_back(Token{val,Type::number,Type::neg,res});
                    }
                    // sinon avec TypeSigne=pos
                    else{
                        listRPN.push_back(Token{val,Type::number,Type::pos,res})    ;
                    }
                    pile.pop_back();
                }
                else if(pile.back().getType()==Type::sin){
                    auto n = _naires.find("sin");
                    DoubleParams params(n->second.first);
                    params.clear();
                    taille=tab.size();
                    for(double i=0;i<taille;i=i+1){
                        params.push_back(tab.back());
                        tab.pop_back();
                    }
                    res=(n->second.second(params));
                    string val=to_string(res);
                    if(res<0){
                        res=res-2*res;
                        listRPN.push_back(Token{val,Type::number,Type::neg,res});
                    }
                    else{
                        listRPN.push_back(Token{val,Type::number,Type::pos,res})    ;
                    }
                    pile.pop_back();
                }   
                else if(pile.back().getType()==Type::tan){
                    auto n = _naires.find("tan");
                    DoubleParams params(n->second.first);
                    params.clear();
                    taille=tab.size();
                    for(double i=0;i<taille;i=i+1){
                        params.push_back(tab.back());
                        tab.pop_back();
                    }
                    res=(n->second.second(params));
                    string val=to_string(res);
                    if(res<0){
                        res=res-2*res;
                        listRPN.push_back(Token{val,Type::number,Type::neg,res});
                    }
                    else{
                        listRPN.push_back(Token{val,Type::number,Type::pos,res})    ;
                    }
                    pile.pop_back();
                }    
                else if(pile.back().getType()==Type::sqrt){
                    auto n = _naires.find("sqrt");
                    DoubleParams params(n->second.first);
                    params.clear();
                    taille=tab.size();
                    for(double i=0;i<taille;i=i+1){
                        params.push_back(tab.back());
                        tab.pop_back();
                    }
                    res=(n->second.second(params));
                    string val=to_string(res);
                    listRPN.push_back(Token{val,Type::number,Type::pos,res});
                }     
                else if(pile.back().getType()==Type::log){
                    auto n = _naires.find("log");
                    DoubleParams params(n->second.first);
                    params.clear();
                    taille=tab.size();
                    for(double i=0;i<taille;i=i+1){
                        params.push_back(tab.back());
                        tab.pop_back();
                    }
                    res=(n->second.second(params));
                    string val=to_string(res);
                    if(res<0){
                        res=res-2*res;
                        listRPN.push_back(Token{val,Type::number,Type::neg,res});
                    }
                    else{
                        listRPN.push_back(Token{val,Type::number,Type::pos,res})    ;
                    }
                    pile.pop_back();
                }
                else if(pile.back().getType()==Type::exp){
                    auto n = _naires.find("exp");
                    DoubleParams params(n->second.first);
                    params.clear();
                    taille=tab.size();
                    for(double i=0;i<taille;i=i+1){
                        params.push_back(tab.back());
                        tab.pop_back();
                    }
                    res=(n->second.second(params));
                    string val=to_string(res);
                    listRPN.push_back(Token{val,Type::number,Type::pos,res})    ;
                    pile.pop_back();
                }
                else if(pile.back().getType()==Type::pow){
                    auto n = _naires.find("pow");
                    DoubleParams params(n->second.first);
                    params.clear();
                    taille=tab.size();
                    for(double i=0;i<taille;i=i+1){
                        params.push_back(tab.back());
                        tab.pop_back();
                    }
                    res=(n->second.second(params));
                    string val=to_string(res);
                    if(res<0){
                        res=res-2*res;
                        listRPN.push_back(Token{val,Type::number,Type::neg,res});
                    }
                    else{
                        listRPN.push_back(Token{val,Type::number,Type::pos,res})    ;
                    }
                    pile.pop_back();
                }
                else if(pile.back().getType()==Type::hypot){
                    auto n = _naires.find("hypot");
                    DoubleParams params(n->second.first);
                    params.clear();
                    taille=tab.size();
                    for(double i=0;i<taille;i=i+1){
                        params.push_back(tab.back());
                        tab.pop_back();
                    }
                    res=(n->second.second(params));
                    string val=to_string(res);
                    listRPN.push_back(Token{val,Type::number,Type::pos,res})    ;
                    pile.pop_back();
                }
                else if(pile.back().getType()==Type::lerp){
                    auto n = _naires.find("lerp");
                    DoubleParams params(n->second.first);
                    params.clear();
                    taille=tab.size();
                    for(double i=0;i<taille;i=i+1){
                        params.push_back(tab.back());
                        tab.pop_back();
                    }
                    res=(n->second.second(params));
                    string val=to_string(res);
                    if(res<0){
                        res=res-2*res;
                        listRPN.push_back(Token{val,Type::number,Type::neg,res});
                    }
                    else{
                        listRPN.push_back(Token{val,Type::number,Type::pos,res})    ;
                    }
                    pile.pop_back();
                }
                else if(pile.back().getType()==Type::polynome){
                    auto v = _vaires.find("polynome");
                    DoubleParams params(v->second.first);
                    params.clear();
                    taille=tab.size();
                    for(double i=0;i<taille;i++){
                        params.push_back(tab.back());
                        tab.pop_back();
                    }
                    res=(v->second.second(params));                   string val=to_string(res);
                    if(res<0){
                        res=res-2*res;
                        listRPN.push_back(Token{val,Type::number,Type::neg,res});
                    }
                    else{
                        listRPN.push_back(Token{val,Type::number,Type::pos,res})    ;
                    }
                    pile.pop_back();
                }                
                fct=false;
            }
            // cas ou on a une rp mais pas de fonction
            else{
                while(pile.back().getType()!=Type::lp){
                    listRPN.push_back(pile.back());
                    pile.pop_back();
                }
                pile.pop_back();
            }
        }
        // traitement des opérands
        else{
            if(pile.empty() || pile.back().getType()==Type::lp){
                pile.push_back(tok);
            }
            else if((tok.getType()==Type::mul || tok.getType()==Type::div)/* && (pile.back().getType()==Type::plus || pile.back().getType()==Type::minus)*/){
                while(pile.back().getType()==Type::div || pile.back().getType()==Type::mul){
                    listRPN.push_back(pile.back());
                    pile.pop_back();
                }
                pile.push_back(tok);
            }
            else{
                
                while(!(pile.back().getType()==Type::lp) && !(pile.empty())){
                    listRPN.push_back(pile.back());
                    pile.pop_back();
                }
                pile.push_back(tok);
            }
        }
    }
    // on oublie pas de vider la pile dans la liste RPN pour ne pas oublier de token et donc de caractères
    while(!(pile.empty())){
        listRPN.push_back(pile.back());
        pile.pop_back();
    }
}

// Cette méthode affiche la listRPN
void Expression::printRPN(){
    cout << endl << "Liste RPN des token triés pour evaluation : " << _expr << " :" << endl;
    for(Token tok: listRPN){
        string ctmp{""};
        if(tok.isNumber()){
            cout << "number(" << tok.getVal() << ")" << endl;
        }
        else if(tok.isOperator()){            
            ctmp=tok.getTypeVal();
            cout << "operator(" << ctmp << ")" << endl;
        }
        else if(tok.isPar()){
            ctmp=tok.getTypeVal();
            cout << "operator('" << ctmp << "')" << endl;
        }
        else{
            cout << "Error" << endl;
        }
    }
}

bool Expression::isVaraires(string Id){
    auto v = _vaires.find(Id);
    if(v!=_vaires.end()){
        return true;
    }
    return false;
}

bool Expression::isFct(string Id){
    auto f=_naires.find(Id);
    if(f!=_naires.end()){
        return true;
    }
    return isVaraires(Id);
}

void Expression::build_fct_table(){
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

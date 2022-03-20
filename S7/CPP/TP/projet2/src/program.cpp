#include <iostream>
#include <sstream>
#include <string>
#include <locale>
#include <stack>
using namespace std;

#include "program.h"

#define N 100000000

// cette méthode boucle() sert à boucler et appeler la méthode 'analyse()'
// on l'appelle tant que l'utilisateur ne rnetre pas 'quitter'
void Program::boucle(){
    // ces deux booléens sert à stopper la boucle dans le cas ou analyse() envoie true
    bool tq{true};
    bool fin{false};
    //build_fct_table();
    while(tq){
        fin=analyse();
        if(fin==true){
            tq=false;
        }
        printMemory();
    }
    memory.clear();
}

// cette méthode 'analyse()' elle celle dans laquelle on traite les expressions de l'utilisateur
// elle renvoie un booléen qui détermine si on stop la boucle ou non
bool Program::analyse(){
    bool fin{false};
    locale loc;
    cout << endl << "bonsoir!!! Entrez expression arithmétique puis '$' à la ligne, ou 'quitter$' pour sortir du programme." << endl << endl;
    
    // on met dans le string expression ce que rentre l'util tant qu'on a pas de 'e'
    getline(cin,expression,'$');
    
    // on test si ce qu'à rentrer l'util n'est pas 'quitter'
    if(expression=="quitter"){
        fin=true;
    }    

    // sinon on traite 'expression'
    else{
        // on init uin nouveau string dont on va se servir pour créer les tokens
        string test_expr{""};

        // on boucle sur tous les caractères de 'expression'
        for(char c : expression)
        {
            // si ce n'est pas un retour à la ligne aors on enfile dans 'test_expr'
            if(c!='\n')
            {
                test_expr.push_back(c);
            }
            // sinon on est arrivé à la fin d'une expression à traiter
            else
            {
                bool equal{false};
                for(char assign : test_expr){
                    if(assign=='='){
                        equal=true;
                    }
                }
                if(equal==true and test_expr.back()==';'){
                    memo(test_expr);
                }
                else if(equal==false && test_expr.back()!=';'){
                    Tokenstring tokstr{test_expr,memory};
                    tokstr.tok(test_expr);
                    //tokstr.print();                    
                    
                    Expression expr(test_expr,tokstr.getListToken());
                    expr.parse();
                    //expr.printRPN();
                    result.push_back(expr.eval());
                }
                test_expr="";
            }
        }
    }       
    // on finit de mettre dans le string expression les lettres qui auraient été rentrés après un e
    getline(cin,expression);
    // on vide le string expression pour le prochain appel à analyse()
    expression="";
    cout << endl;
    print();
    // on vide la liste des résultats
    result.clear();
    // on retourne le booléen fin qui stop ou non la boucle
    return fin;
}

// Dans cette fonction on affiche les résultats
// ces résultats sont contenus dans la liste 'result'
// ce sont les résultats des expressions rentrés par l'utilisateur
void Program::print(){
    for(double res : result){
        cout << res << endl;
    }
}

void Program::printMemory(){
    map<string,double>::iterator it;
    cout << "----- MEMORY -----" << endl << endl;
    for(it=memory.begin(); it!=memory.end(); it++){
        cout << it->first << " = ";
        cout << it->second << endl;
    }
    cout << endl << "------------------" << endl;
}


void Program::memo(string expr){
    string nameVar{""};
    string expression{""};
    locale loc;
    int i{0};
    string tmp{""};
    // tq pas égal alors ca fait parti du nom de la variable
    while(expr[i]!='='){
        nameVar.push_back(expr[i]);
        i++;
    }
    i++;
    // on test si chiffre ou chaine de caractère
    // si chaine de caractère alors on va chercher dans la mam
    // la valeur correspondante à la chaine de caractère
    while(expr[i]!=';'){
        if(isalpha(expr[i],loc)){
            tmp.push_back(expr[i]);
        }
        else if(((expr[i]=='*') || (expr[i]=='/') || (expr[i]=='+') || (expr[i]=='-')) && (!(tmp.empty()))){
            double tempo=memory.find(tmp)->second;
            string temp=to_string(tempo);
            for(char c : temp){
                expression.push_back(c);
            }
            expression.push_back(expr[i]);
            tmp="";
        }
        else{
            expression.push_back(expr[i]);

        }
        i++;
    }
    if(!(tmp.empty())){
            double tempo=memory.find(tmp)->second;
            string temp=to_string(tempo);
            for(char c : temp){
                expression.push_back(c);
            }
        tmp="";
    }
    // on évalue l'expression afin de pouvoir associer la valeur au nom de la nouvelle variable
    Tokenstring tokstr{expression,memory};
    tokstr.tok(expression);

    // on passe cette liste dans un objet Expression dans lequel on va la parser
    Expression express{expression,tokstr.getListToken()};
    express.parse();
    //expr.printRPN();

    // on insert dans la mémoire le nom avec sa valeur associée
    memory.insert(pair<string,double>(nameVar,express.eval()));
    // on libère l'espace de la liste des tokens
    tokstr.free();
}



#include <iostream>
#include <list>

#include "tokenstring.h"

class Expression{

public:
    Expression(std::string str, list<Token> list): _expr{str}, listTokExpr{list} {}

    // on renvoie la valeur de l'évaluation d'une expression
    double eval();

    // on renvoie le résultats de l'opération type sur les double d1 et d2
    double op(Type type, double d1, double d2);

    // on vérifie si on a des paranthèses et on apelle le bon parsesur l'expression
    void parse();

    // on traite la list de Tokens pour obtenir la listRPN
    // listTokens sans paranthèses
    void parseNorm();

    // on traite la list de Tokens pour obtenir la listRPN
    // listTokens avec paranthèses
    void parsePar();

    // on affiche à l'écran la listRPN qui contient les tokens triés pour évaluations
    void printRPN();

    // on teste si fonction à v variables
    bool isVaraires(std::string Id);

    // on test si fonction à n variables
    bool isFct(std::string Id);

    // on initialise la table des fonctions possibles
    void build_fct_table();


private:
    // expression à traiter
    std::string _expr;

    //liste de Token
    list<Token> listTokExpr;
    //list de Token triés pour évaluation
    list<Token> listRPN;

    using DoubleParams=std::vector<double>;
    using NaireFct=std::function<double(DoubleParams)>;
    using InterneFct=std::pair<int, NaireFct>;

    // nos deux maps contenant nos fonctions possibles
    std::map<std::string, InterneFct> _naires;
    std::map<std::string, InterneFct> _vaires;
};
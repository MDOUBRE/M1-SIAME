#include <iostream>
#include <list>
#include <map>
#include <functional>
#include <vector>

#include "token.h"

class Tokenstring{

public:
    
    class Error {
    public:
        explicit Error(const std::string &error): message("Program error : " + error) {}
    private:
        std::string message;    
    };   
       
    Tokenstring();
    Tokenstring(std::string &str, std::map<std::string,double> mem): _chaine{&str}, memory{mem} {}
    Tokenstring(std::string *str): _chaine{str} {}

    void tok(std::string str);
    // on affiche la list de Token tokenString
    
    void print();

    // on renvoie la taille de la liste tokenString
    int sizeListTok();

    // on vide la liste tokenString
    void free();

    // on renvoie la list tokenString
    list<Token> getListToken();

    // on teste si fonction à v variables
    bool isVaraires(std::string Id);

    // on test si fonction à n variables
    bool isFct(std::string Id);

    // on initialise la table des fonctions possibles
    void build_fct_table();

   
private:
    // expression à évaluer
    std::string *_chaine;

    // liste de Token réalisé à partir de l'expression _chaine
    list<Token> tokenString;
    // liste de caractères temporaire utilisée dans les méthodes
    list<char> tmp;

    // une map contenant nom de variable et valeur associées
    // on la passe en paramètre pour pouvoir faire les calculs avec les valeurs des variables utilisées
    std::map<std::string,double> memory;

    // on crée notre tableau de paramètres
    using DoubleParams=std::vector<double>;
    using NaireFct=std::function<double(DoubleParams)>;
    using InterneFct=std::pair<int, NaireFct>;

    // nos deux maps contenant nos fonction possibles
    std::map<std::string, InterneFct> _naires;
    std::map<std::string, InterneFct> _vaires;

    
};
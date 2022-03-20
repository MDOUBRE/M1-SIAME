#include <iostream>
#include <sstream>
#include <list>
#include <map>
#include <vector>
#include <functional>
#include "expression.h"

class Program{
public:

    class Error {
    public:
        explicit Error(const std::string &error): message("Program error : " + error) {}
    private:
        std::string message;    
    };

    // Les deux constructeurs d'objet Program
    Program(std::istream &is): stream{&is} {}
    
    Program(std::istream *is): stream{is} {}
    
    // la méthode boucle lance une boucle qui ne se termine pas tant qu'un booléen n'est pas sur true
    void boucle();

    // la méthode analyse est la méthode qui contient toutes les actions
    // pour traiter les expressions et/ou suites d'expressions
    bool analyse();

    // la méthode print affiche les résultats des exprs
    // ces résultats sont dans la liste résult qui contient des doubles
    void print();

    // la méthode printMemory affiche le contenu de la mémoire
    // elle est utilisée après chaque boucle du programme
    void printMemory();

    // la méthode memo sert à mettre en mémoire une nouvelle variable
    // elle prend une chaine de caractère et la traite afin de mettre dans la map memory
    // le nom de la variable et sa valeur associée
    void memo(std::string expr);


private:
    // flux d'entrée standard
    std::istream *stream;

    // liste contenant les résultats des expressions rentrées par l'utilisateur
    list<double> result;
    // string contenant les expressions rentrées  par l'utilisateur
    std::string expression;
    // map contenant les variables mémorisée
    // elle conteient pour chaque variable son nom et sa valeur
    std::map<std::string,double> memory;

    /*
    using DoubleParams=std::vector<double>;
    using NaireFct=std::function<double(DoubleParams)>;
    using InterneFct=std::pair<int, NaireFct>;

    std::map<std::string, InterneFct> _naires;
    std::map<std::string, InterneFct> _vaires;
    */
};


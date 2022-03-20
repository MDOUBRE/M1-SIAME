#include <string>
#include <iostream>
#include <sstream>
using namespace std;

#include "program.h"


int main(int argc, const char* argv[]){
    cout << "--------------- Debut Programme --------------" << endl;

    // je crée un objet prog dans lequelje passe le fux d'entrée stantard
    // puis j'appelle la méthode boucle() de cet objet
    Program prog{cin};
    prog.boucle();

    cout << endl << "---------------- Fin programme ---------------" << endl;
    
    return 0;
}
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

// Class "Game"
class Game {
    public:
        Game(int, int);

        void Reset();       // Reinitialise pour une nouvelle partie
        void PrintGrid();   // Affiche grille de jeu

    private:
        int rows;       // Nombre de rangés
        int cols;       // Nombre de colonnes
        int ** grid;    // Grille de jeu ( indice du symbole )

        string symboles = "XO ";    // Symboles possibles
};
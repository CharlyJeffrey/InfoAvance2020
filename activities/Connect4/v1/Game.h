#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

// Class "Game"
class Game {
    public:
        Game(int, int);

        void Reset();
        void PrintGrid();

    private:
        int rows;       // Nombre de rangés
        int cols;       // Nombre de colonnes
        int ** grid;    // Grille de jeu

        string symboles = "XO ";    // Symboles possibles
};
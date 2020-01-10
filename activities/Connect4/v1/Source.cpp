#include <stdlib.h>
#include "Game.cpp"

#define ROWS 6
#define COLS 7

int main() {
    // Instancie une classe de jeu
    Game CFG = Game(ROWS, COLS);

    // Affiche la grille
    CFG.PrintGrid();
    
    return 0;
}
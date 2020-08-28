#include "Game.cpp"

/* MACRO ( optionnelles ), sinon hard-coded */
#define ROWS 6
#define COLS 7

int main() {
    // Instancie une classe de jeu
    Game CFG = Game(ROWS, COLS);

    // Joue 3 parties ( best of 3 )
    CFG.PlaySetOf(3);
    
    return 0;
}
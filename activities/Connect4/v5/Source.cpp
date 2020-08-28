#include "Game.cpp"

/* MACRO ( optionnelles ), sinon hard-coded */
#define ROWS 6
#define COLS 7

int main() {
    /* 
        Laisser les jeunes modifier cette section comme il veulent 

        Exemple:
            - Demander le nombre de parties ( pas hard-coded )
            - Demander si les joueurs veulent rejouer ( après un set )
            - etc
    */
    // Instancie une classe de jeu
    Game CFG = Game(ROWS, COLS);
    
    // Joue 3 parties ( best of 3 )
    CFG.PlaySetOf(3);
    
    return 0;
}
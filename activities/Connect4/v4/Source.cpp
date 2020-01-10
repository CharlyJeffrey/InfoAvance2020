#include <stdlib.h>
#include "Game.cpp"

/* MACRO */
#define ROWS 6
#define COLS 7
#define NOMBRE_JOUEURS 2
#define NOMBRE_CHAR_NOM 16

/* HEADER */
char ** GetNames();

int main() {
    // Obtient le nom des joueurs
    char ** joueurs = GetNames();

    // Instancie une classe de jeu
    Game CFG = Game(ROWS, COLS, 3, joueurs);

    // Joue une partie
    CFG.Play();
    
    return 0;
}

// Fonction pour obtenir le nom des joueurs
char ** GetNames() {
    // Allocation de mémoire
    char ** _names = (char**) malloc(NOMBRE_JOUEURS * sizeof(char*));
    // Boucle pour allouer de la mémoire et obtenir les noms
    for (int i = 0; i < NOMBRE_JOUEURS; i++) {
        // Allocation
        _names[i] = (char*) malloc(NOMBRE_CHAR_NOM * sizeof(char));
        // Obtention
        cout << "Joueur " << i+1 << ", quel est votre nom?\n";
        cin >> _names[i];
    }
    // Retourne le pointeur
    return _names;
}
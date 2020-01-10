#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

enum EChoiceStatus {
    OK,
    INVALID_CHOICE,
    INVALID_COLUMN_RANGE,
    INVALID_ROW_RANGE,
    DEFAULT
};

class Game {
    public:
        Game(int, int);

        bool getPlayer();
        bool hasPlayerWon();
        bool isGameOver();

        void reset();
        void play(int);
        void checkGrid(int);
        void printGrid();

        EChoiceStatus getStatus(int);

    private:
        int rows;           // Nombre de rangés
        int cols;           // Nombre de colonnes
        int ** grid;        // Grille de jeu

        int nPiecePlayed;   // Nombre de pieces jouées
        int * colCounter;   // Array pour contenir le nombre de piece de chaque colonne

        bool player;        // Switch pour changer déterminer qui joue

        bool gameOver;      // Partie terminée
        bool playerWon;     // Un joueur a gagné

        string symboles = "XO ";            // Symboles des jouers X == P1; O == P2; " " == Default
        int symbolesValues[3] = {2, 3, 5};  // Valeurs associées pour chaque symbole
        int winningValues[2];               // Valeurs nécéssaire pour gagner (pour chaque joueur)
};
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

// Enum des status possible d'un choix
enum EChoiceStatus {
    OK,
    INVALID_CHOICE,
    INVALID_COLUMN_RANGE,
    INVALID_COLUMN_FULL,
    DEFAULT
};

// Class "Game"
class Game {
    public:
        Game(int, int, string*);

        bool IsColumnFull(int);
        EChoiceStatus GetChoiceStatus(int);

        void Reset();
        void PrintGrid();
        void PlaceJeton(int);
        void ChangeJoueur();

    private:
        int rows;       // Nombre de rangés
        int cols;       // Nombre de colonnes
        int ** grid;    // Grille de jeu
        int * colsCounter;   // Compteur de jetons de chaque colonne

        bool quiJoue;   // Variable pour déterminer quel joueur joue
        string * joueurs;   // Array pour contenir le nom des joueurs

        string symboles = "XO ";    // Symboles possibles
};
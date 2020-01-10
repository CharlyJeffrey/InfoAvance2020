#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>

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
        Game(int, int, int, char**);

        bool IsColumnFull(int);
        bool IsGameOver();
        EChoiceStatus GetChoiceStatus(int);
        string GetCurrentPlayer();

        int GetValidChoice();

        void Play();
        void PlayGame();
        void Reset();
        void PrintGrid();
        void PlaceJeton(int);
        void ChangeJoueur();
        void CheckGrid(int);
        void PrintGameStatus();

    private:
        int rows;       // Nombre de rangés
        int cols;       // Nombre de colonnes
        int ** grid;    // Grille de jeu
        int * colsCounter;   // Compteur de jetons de chaque colonne

        bool gameOver;  // Game over
        bool gameWon;   // Player won

        int nombreParties;  // Nombre de partie qui seront jouées

        bool quiJoue;       // Variable pour déterminer quel joueur joue
        char ** joueurs;   // Noms des joueurs

        int * score;    // Score des joueurs
        
        string symboles = "XO ";            // Symboles possibles
        int valeurSymbole[3] = {2, 3, 0};   // Valeur associée à chaque symbole
        int * valeurGagnante;
};
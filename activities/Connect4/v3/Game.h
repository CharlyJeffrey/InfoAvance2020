#include <iostream>
#include <string>
#include <stdlib.h>

#define NOMBRE_JOUEURS 2
#define NOMBRE_CHAR_NOM 16

using namespace std;

// Enum des status possible d'un choix
enum EChoiceStatus {
    DEFAULT,
    OK,
    INVALID_CHOICE,
    INVALID_COLUMN_RANGE,
    INVALID_COLUMN_FULL
};

// Class "Game"
class Game {
    public:
        Game(int, int);   // Constructeur

        void Reset();
        void PlayGame();
        void PrintGrid();

    private:
        /* Attributs */
        int rows;       // Nombre de rangés
        int cols;       // Nombre de colonnes
        int coups;      // Nombre de coup joué
        int maxCoups;   // Nombre de coup maximum possible
        int ** grid;    // Grille de jeu
        int * colsCounter;   // Compteur de jetons de chaque colonne
        int scoreCoup[3] = {0, 0, 0};   // Score pour un coup joué
        int score[2] = {0, 0};          // Score des joueurs
             
        bool gameOver;              // Game over
        bool gameWon;               // Player won
        bool quiJoue;               // Déterminer quel joueur joue
        
        char ** joueurs;   // Array pour contenir le nom des joueurs
        char symboles[3] = {'X', 'O', ' '}; // Symboles possibles

        /* Méthodes */
        EChoiceStatus GetChoiceStatus(int); // Obtient le statut associé au choix

        bool IsColumnFull(int);         // Colonne pleine?

        void ChangeJoueur();
        void GetValidChoice(int*);
        void PlaceJetonThenCheck(int);
        void CheckGrid(int);
};
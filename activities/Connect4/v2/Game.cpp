#include "Game.h"

// Constructeur de la classe
Game::Game(int _rows, int _cols, string * _joueurs) {
    // Dimension de la grille
    rows = _rows;
    cols = _cols;

    // Obtient le nom des joueurs
    joueurs = _joueurs;

    // Réinitialise la grille de jeu
    Reset();
}

// Méthode pour déterminer si une colonne est pleine
bool Game::IsColumnFull(int col) {return colsCounter[col] < rows;}

// Méthode pour obtenir le status d'un choix
EChoiceStatus Game::GetChoiceStatus(int choix) {
    // Vérifie si le choix fait n'est pas un nombre
    if (!cin.good()) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Votre choix doit être un nombre entier!\n\n";
        return EChoiceStatus::INVALID_CHOICE;
    }
    // Vérifie si le nombre choisi correspond à une colone valide
    if (choix < 0 || cols <= choix) {
        cout << "Votre choix doit être un nombre entre 0 et " << cols-1 << "!\n\n";
        return EChoiceStatus::INVALID_COLUMN_RANGE;
    }
    // Vérifie si la colonne choisi est pleine
    if (colsCounter[choix]+1 >= rows) {
        cout << "La colonne choisie est pleine! Refaites votre choix!\n\n";
        return EChoiceStatus::INVALID_COLUMN_FULL;
    }
    // Sinon, choix valide
    return EChoiceStatus::OK;
}

// Méthode pour réinitialiser une instance de jeu
void Game::Reset() {
    // Initialise la grille de jeu
    grid = (int**) malloc(rows * sizeof(int*));
    // Vérifie si allocation échouée
    if (grid == nullptr) {cout << "/> Allocation mémoire échouée.\n"; return;}
    for (int i = 0; i < rows; i++) {
        grid[i] = (int*) malloc(cols * sizeof(int));
        // Vérifie si allocation échouée
        if (grid[i] == nullptr) {cout << "/> Allocation mémoire échouée.\n"; return;}
        // Remplie toutes les cases avec la valeur '2'
        for (int j = 0; j < cols; j++) grid[i][j] = 2;
    }

    // Initialise le comtpeur
    colsCounter = (int*) malloc(cols * sizeof(int));
    for (int i = 0; i < cols; i++) colsCounter[i] = 0;

    // Joueur 1 commence à jouer par défaut
    quiJoue = false;
}

// Méthode pour afficher la grille
void Game::PrintGrid() {
    // Boucle pour afficher les éléments de la grille
    for (int i = rows - 1; i >= 0; i--) {
        for (int j = 0; j < cols; j++) cout << "----";
        cout << endl;
        // Boucle sur les colonnes
        for (int j = 0; j < cols; j++) {
            // Affiche symbole de la case (i, j)
            cout << "| " << symboles[grid[i][j]] << " ";
        }
        cout << "|\n";
    }
    // Affiche le numéro de chaque colonne dans le bas
    for (int i = 0 ; i < cols; i++) cout << "----"; cout << endl;
    for (int i = 0; i < cols; i++) cout << "  " << i << " "; cout << endl;
    for (int i = 0 ; i < cols; i++) cout << "===="; cout << endl;
}

// Méthode pour placer un jeton dans une colonne spécifiée
void Game::PlaceJeton(int col) {
    // Ajoute le jeton du joueur dans la colonne 'col'
    grid[colsCounter[col]++][col] = quiJoue;
};

// Méthode pour changer le joueur qui joue
void Game::ChangeJoueur() {quiJoue = !quiJoue;}
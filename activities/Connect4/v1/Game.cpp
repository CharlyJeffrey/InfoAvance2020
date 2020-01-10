#include "Game.h"

// Constructeur de la classe
Game::Game(int _rows, int _cols) {
    // Dimension de la grille
    rows = _rows;
    cols = _cols;

    // Réinitialise la grille de jeu
    Reset();
}

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
}

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
    for (int i = 0 ; i < cols; i++) cout << "====="; cout << endl;
}
#include "Game.h"

// Constructeur de la classe
Game::Game(int _rows, int _cols) {
    // Dimension de la grille
    rows = _rows;
    cols = _cols;
    // Limite pour jeu fonctionnel
    if (rows < 4) rows = 4;
    if (cols < 4) cols = 4; 

    // Initialise la grille de jeu
    grid = new int*[_rows]; // == int *(_rows)
    for (int i = 0; i < rows; i++) {
        grid[i] = new int[_cols];
        for (int j = 0; j < cols; j++) grid[i][j] = 2;
    }

    // Réinitialise la grille de jeu
    Reset();
}

//
void Game::Reset() {
    // Initialise la grille de jeu
    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < cols; j++) grid[i][j] = 2;
}

void Game::PrintGrid() {
    // Boucle ( décroissante ) pour afficher les éléments à partir du "top"
    for (int i = rows - 1; i >= 0; i--) {
        // Affiche séparateur de rangés
        for (int j = 0; j < cols; j++) 
            cout << "----";
        cout << endl;
        // Affiche les éléments colonne par colonne, en commençant par la gauche
        for (int j = 0; j < cols; j++) 
            cout << "| " << symboles[grid[i][j]] << " ";
        cout << "|\n";
    }
    // Affiche le numéro de chaque colonne dans le bas
    for (int i = 0 ; i < cols; i++) cout << "----"; cout << endl;
    for (int i = 0; i < cols; i++) cout << "  " << i << " "; cout << endl;
    for (int i = 0 ; i < cols; i++) cout << "===="; cout << "\n\n";
}
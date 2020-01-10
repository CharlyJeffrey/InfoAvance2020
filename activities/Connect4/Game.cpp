/*

*/

#include "Game.h"

Game::Game(int _rows, int _cols) {
    // Dimension de la grille
    rows = _rows;
    cols = _cols;  

    /// Détermine les valeurs gagnantes unique à chaque joueurs
    for (int i = 0; i < 2; i++) {
        winningValues[i] = 1;
        for (int j = 0; j < 4; j++) winningValues[i] = winningValues[i] * symbolesValues[i];
    }

    // Réinitialise les variables et la grille de jeu
    reset();
}

/// Getters 
bool Game::getPlayer() {return player;}
bool Game::hasPlayerWon() {return playerWon;}
bool Game::isGameOver() {return gameOver;}

// Méthode pour réinitialiser le jeu
void Game::reset() {
    // Qui joue; false == P1; true == P2
    player = false;

    // Grille initialement vide
    nPiecePlayed = 0;

    /// Variables de l'état d'une partie
    gameOver = false;
    playerWon = false;

    /// Initialise le compteur de chaque colonne à 0
    colCounter = new int[cols];
    for (int i = 0; i < cols; i++) colCounter[i] = 0;

    /// Initialise la grille de jeu
    grid = (int**) malloc(rows * sizeof(int*));
    if (grid == nullptr) {
        cout << "Allocation mémoire échouée.\n";
        return;
    }
    for (int i = 0; i < rows; i++) {
        grid[i] = (int*) malloc(cols * sizeof(int));
        if (grid[i] == nullptr) {
            cout << "Allocation mémoire échouée.\n";
            return;
        }
        for (int j = 0; j < cols; j++) {
            grid[i][j] = 2;
        }
    }
}

// Méthode pour vérifier si la grille contient un connect4 suite à l'ajout d'un jeton
void Game::checkGrid(int col) {

    /// Position du jeton placé
    int _col = col;
    int _row = colCounter[col]-1;

    // Score de la vérification
    int score;

    // Indices utiles à la vérification
    int indexOne, indexTwo;

    bool flag = false;

    /// Horizontal check
    int c = col - 3;
    // Clipping
    if (c < 0) c = 0;

    // Loop pour obtenur la première valeur de 'score'
    score = 1;
    for (int i = 0; i < 4; i++) {
        indexOne = grid[_row][c++];
        score = score * symbolesValues[indexOne];
    }
    // Vérifie si le jouer a gagné
    if (score == winningValues[player]) {playerWon = true; gameOver = true; return;}

    // Boucle sur le reste de la rangé
    while (c < _col+3 && c < cols) {
        indexOne = grid[_row][c-3]; // Jeton trois position à gauche
        indexTwo = grid[_row][c++]; // Jeton une position plus loin à droite
        // Modifie la valeur de score
        score = score / symbolesValues[indexOne] * symbolesValues[indexTwo];
        // Vérifie si le joueur a gagné
        if (score == winningValues[player]) {playerWon = true; gameOver = true; return;}
    }

    // Réinitialise le score
    score = 1;
    // 
    int r;
    // Vertical check (seulement si le jeton est au moins à 3e rangé)
    if (_row > 2) {
        r = _row;
        for (int i = 0; i < 4; i++) {
            indexOne = grid[r--][col];
            score = score * symbolesValues[indexOne];
        }
        // Vérifie si le joueur a gagné
        if (score == winningValues[player]) {playerWon = true; gameOver = true; return;}
    }

    score = 1;
    // First Diagonal check 
    r = _row - 3;
    c = _col - 3;
    // Clipping
    if (r < 0) {c = c - r; r = 0;}
    if (c < 0) {r = r - c; c = 0;}

    // Boucle sur les 4 premiers éléments de la diagonale
    for (int i = 0; i < 4; i++) {
        indexOne = grid[r++][c++];
        score = score * symbolesValues[indexOne];
        if (r >= rows || c >= cols) {flag = true; break;}
    }
    
    // Vérifie si le joueur a gagné
    if (score == winningValues[player]) {playerWon = true; gameOver = true; return;}
    // Boucle sur le reste de la diagonale
    
    while (!flag && r < rows && c < cols && r <= _row + 3 && c <= _col + 3) {
        indexOne = grid[r-3][c-3];
        indexTwo = grid[r++][c++];
        score = score / symbolesValues[indexOne] * symbolesValues[indexTwo];
        // Vérifie si le joueur a gagné
        if (score == 4 * winningValues[player]) {playerWon = true; gameOver = true; return;}
    }
    // Réinitialise le score
    score = 1;
    // Reinitialise le flag
    flag = false;

    // Second Diagonal check
    r = _row + 3;
    c = _col - 3;
    // Clipping
    if (r >= rows) {c = c - r + rows; r = rows - 1;}
    if (c < 0) {r = r + c; c = 0;}
    for (int i = 0; i < 4; i++) {
        indexOne = grid[r--][c++];
        score = score * symbolesValues[indexOne];
        if (r < 0 || c >= cols) {flag = true; break;}
    }
    // Vérifie si le joueur a gagné
    if (score == winningValues[player]) {playerWon = true; gameOver = true; return;}

    //if (r < 0 || c >= cols) flag = true;
    while (!flag && r>= 0 && r < rows && c < cols && r >= _row - 3 && c <= _col + 3) {
        indexOne = grid[r+3][c-3];
        indexTwo = grid[r--][c++];
        score = score / symbolesValues[indexOne] * symbolesValues[indexTwo];
        // Vérifie si le joueur a gagné
        if (score == 4 * winningValues[player]) {playerWon = true; gameOver = true; return;}
    }
}

// Méthode pour placer le jeton dans la colonne choisie
void Game::play(int col) {
    // Obtient la rangé où le jeton sera placé
    int row = colCounter[col]++;
    // Place le jeton
    grid[row][col] = player;
    // Vérifie si le joueur a gagné
    checkGrid(col);
    // Vérifie si la colonne est maintenant pleine
    if (colCounter[col] == rows-1) nPiecePlayed++;
    // Vérifie si toutes les colonnes sont pleines
    if (nPiecePlayed == cols) gameOver = true;
    // Change de joueur (si besoin)
    if (!playerWon) {player = !player;}
}

// Méthode pour afficher la grille de jeu
void Game::printGrid() {
    // Boucle pour afficher les éléments de la grille
    for (int i = rows-1; i >= 0; i--) {
        for (int j = 0; j < cols; j++) cout << "----";
        cout << endl;
        // boucle sur les colonnes
        for (int j = 0; j < cols; j++) {
            // Affiche le symbole de la case
            cout << "| " << symboles[grid[i][j]] << " ";
        }
        cout << "|\n";
    }
    // Affiche le numéro de chaque colonne dans le bas
    for (int i = 0 ; i < cols; i++) cout << "----"; cout << endl;
    for (int i = 0; i < cols; i++) cout << "  " << i << " "; cout << endl;
    for (int i = 0 ; i < cols; i++) cout << "====="; cout << endl;
}

// Méthode pour obtenir le statu associé au choix fait par le joueur
EChoiceStatus Game::getStatus(int rep) {

    // Vérifie si le choix fait n'est pas un nombre
    if (!cin.good()) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Votre choix doit être un nombre entier!\n\n";
        return EChoiceStatus::INVALID_CHOICE;
    }

    // Vérifie si le nombre choisi correspond à une colone valide
    if (rep < 0 || cols <= rep) {
        cout << "Votre choix doit être un nombre entre 0 et " << cols-1 << "!\n\n";
        return EChoiceStatus::INVALID_COLUMN_RANGE;
    }

    // Vérifie si la colonne choisi est pleine
    if (colCounter[rep]+1 >= rows) {
        cout << "La colonne choisie est pleine! Refaites votre choix!\n\n";
        return EChoiceStatus::INVALID_ROW_RANGE;
    }

    return EChoiceStatus::OK;
}

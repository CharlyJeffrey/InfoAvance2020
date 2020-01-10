#include "Game.h"

// Constructeur de la classe
Game::Game(int _rows, int _cols, string * _joueurs) {
    // Dimension de la grille
    rows = _rows;
    cols = _cols;

    // Nom des joueurs
    joueurs = _joueurs;

    // Réinitialise la grille de jeu
    Reset();
}

// Méthode pour déterminer si une colonne est pleine
bool Game::IsColumnFull(int col) {return colsCounter[col] < rows;}

// Méthode pour déterminer si la partie est terminée
bool Game::IsGameOver() {return gameWon || gameOver;}

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
    // Initialise les attibuts lié à la partie
    gameOver = false;
    gameWon = false;

    // Valeur gagnante
    valeurGagnante = (int*) malloc(2 * sizeof(int));
    for (int i = 0; i < 2; i++) valeurGagnante[i] = pow(valeurSymbole[i], 4);

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

// Méthode pour déterminer si un joueur à gagné
void Game::CheckGrid(int col) {
    // Variable pour contenir le score d'une vérification
    int score = 1;

    // Variable pour contenir la position de la rangé du jeton joué
    int row = colsCounter[col] - 1;

    // Variable pour déterminer si on sort de la grille
    bool flag = false;

    // Variables utilisées comme balise
    int indexOne, indexTwo;

    /* Vérification horizontale */
    int _col = col - 3;
    // Clipping
    if (_col < 0) _col = 0;
    // Loop pour obtenir la première valeur de score
    for (int i = 0; i < 4; i++) {
        indexOne = grid[row][_col++];
        score = score * valeurSymbole[indexOne];
    }
    // Vérifie si le jouer a gagné
    if (score == valeurGagnante[quiJoue]) {
        gameWon = true;
        gameOver = true;
        return;
    }
    // Boucle sur le reste de la rangé
    while (_col < col + 3 && _col < cols) {
        indexOne = grid[row][_col-3];
        indexTwo = grid[row][_col++];
        // Modifie la valeur de score
        score = score / valeurSymbole[indexOne] * valeurSymbole[indexTwo];
        // Vérifie si le joueur a gagné
        if (score == valeurGagnante[quiJoue]) {
            gameWon = true;
            gameOver = true;
            return;
        }
    }

    // Réinitialise le score
    score = 1;

    // Vérification verticale
    int _row = 0;
    // Vérifie si il y a au moins 4 jetons dans la colonne
    if (row > 2) {
        _row = row;
        // Boucle sur la colonne
        for (int i = 0; i < 4; i++) {
            indexOne = grid[_row--][col];
            score = score * valeurSymbole[indexOne];
        }
        // Vérifie si le joueur a gagné
        if (score == valeurGagnante[quiJoue]) {
            gameWon = true;
            gameOver = true;
            return;
        }
    }

    // Réinitialise le score
    score = 1;

    // Vérification diagonale #1
    _row = row - 3;
    _col = col - 3;
    // Clipping
    if (_row < 0) {_col = _col - _row; _row = 0;}
    if (_col < 0) {_row = _row - _col; _col = 0;}

    // Boucle sur les 4 premiers éléments
    for (int i = 0; i < 4; i++) {
        indexOne = grid[_row++][_col++];
        score = score * valeurSymbole[indexOne];
        // Vérifie si on sors de la grille de jeu
        if (_row >= rows || _col >= cols) {flag = true; break;}
    }
    // Vérifie si le joueur a gagné
    if (score == valeurGagnante[quiJoue]) {
        gameWon = true;
        gameOver = true;
        return;
    }
    // Boucle sur le reste de la diagonale
    while (!flag && _row < rows && _col < cols && _row < row+4 && _col < col+4) {
        indexOne = grid[_row-3][_col-3];
        indexTwo = grid[_row++][_col++];
        // Update score
        score = score / valeurSymbole[indexOne] * valeurSymbole[indexTwo];
        // Vérifie si score gangnant
        if (score == valeurGagnante[quiJoue]) {
            gameWon = true;
            gameOver = true;
            return;
        }
    }

    // Réinitialise le score et flag
    score = 1;
    flag = false;

    // Vérification diagonale #2
    _row = row + 3;
    _col = col - 3;

    // Clipping
    if (_row >= rows) {_col = _col - _row; _row = rows-1;}
    if (_col < 0) {_row = _row + _col; _col = 0;}
    if (_row < 3) return;

    // Premiere boucle sur la seconde diagonale
    for (int i = 0; i < 4; i++) {
        indexOne = grid[_row--][_col++];
        score = score * valeurSymbole[indexOne];
        // Vérifie si on est hors domaine
        if (_row < 0 || _col >= cols) {flag = true; break;}
    }
    
    // Vérifie si score gangnant
    if (score == valeurGagnante[quiJoue]) {
        gameWon = true;
        gameOver = true;
        return;
    }
    // Boucle sur le reste de la diagonale
    while (!flag && _row >= 0 && _col < cols && _row > row-4 && _col < col+4) {
        indexOne = grid[_row+3][_col-3];
        indexTwo = grid[_row--][_col++];
        // Update score
        score = score / valeurSymbole[indexOne] * valeurSymbole[indexTwo];
        // Vérifie si score gangnant
        if (score == valeurGagnante[quiJoue]) {
            gameWon = true;
            gameOver = true;
            return;
        }
    }
}
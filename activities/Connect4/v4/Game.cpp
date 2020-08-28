#include "Game.h"

// Constructeur de la classe
Game::Game(int _rows, int _cols) {
    // Dimension de la grille
    rows = _rows;
    cols = _cols;
    // Limite pour jeu fonctionnel
    if (rows < 4) rows = 4;
    if (cols < 4) cols = 4; 

    // Nombre de coups maximum
    maxCoups = rows * cols;

    // Initialise la grille de jeu
    grid = new int*[_rows];
    for (int i = 0; i < rows; i++) {
        grid[i] = new int[_cols];
        for (int j = 0; j < cols; j++) grid[i][j] = 2;
    }

    // Nom des joueurs
    joueurs = new char*[NOMBRE_JOUEURS];
    for (int i = 0; i < NOMBRE_JOUEURS; i++) {
        joueurs[i] = new char[NOMBRE_CHAR_NOM];
        cout << "Joueur " << i+1 << ", quel est votre nom?\n";
        cin >> joueurs[i];
    }

    // Compteur de colonne
    colsCounter = new int[_cols];

    // Réinitialise la grille de jeu
    Reset();
}

// Méthode pour réinitialiser une instance de jeu
void Game::Reset() {
    // Initialise les attibuts lié à la partie
    gameOver = false;
    gameWon = false;
    quiJoue = true;
    coups = 0;

    // Initialise la grille de jeu
    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < cols; j++) grid[i][j] = 2;

    // Initialise le comtpeur
    for (int i = 0; i < cols; i++) colsCounter[i] = 0;
}

// Méthode pour jouer une série de partie
void Game::PlaySetOf(unsigned int nombreParties) {
    // Boucle sur le nombre de partie qui seront jouées
    for (int p = 0; p < nombreParties; p++) {
        // Joue une partie
        PlayGame();
        // Reset
        Reset();
    }
    // Affiche score final
    cout << score[0] << " " << score[1] << endl;
}

// Méthode pour jouer une partie
void Game::PlayGame() {
    // Variable pour contenir le choix du joueur
    int choix;

    // Affiche la grille
    PrintGrid();

    // Boucle de jeu principale
    while (!gameOver) {
        // Change de joueur
        quiJoue = !quiJoue;
        // Obtient un choix valide
        GetValidChoice(&choix);
        // Place le jeton
        PlaceJetonThenCheck(choix);
        // Affiche la grille
        PrintGrid();
    }

    // Affiche résultat
    PrintGameResults();
}

// Méthode pour déterminer si une colonne est pleine
bool Game::IsColumnFull(int col) {return colsCounter[col] < rows;}

// Méthode pour déterminer si la partie est terminée
bool Game::IsGameOver() {return gameWon || gameOver;}

// Méthode pour obtenir le status d'un choix
EChoiceStatus Game::GetChoiceStatus(int choix) {
    // Vérifie si le choix fait n'est pas un nombre entier
    if (!cin.good()) {
        cin.clear();
        cin.ignore(64, '\n');
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

// Méthode pour obtenir un choix valide
void Game::GetValidChoice(int * pchoix) {
    // Variable pour contenir le status du joueur
    EChoiceStatus status = EChoiceStatus::DEFAULT; // == 0 
    
    // Affiche le nom du joueur
    cout << joueurs[quiJoue] << " à vous de jouer!\n";
    // Boucle 
    while(status != EChoiceStatus::OK) {
        // Demande au joueur dans quelle colonne il veut placer son jeton
        cout << "Dans quelle colonne voulez-vous jouer?" << endl;
        cin >> *pchoix;
        // Update status
        status = GetChoiceStatus(*pchoix);
    }
}

// Méthode pour placer un jeton dans une colonne spécifiée
void Game::PlaceJetonThenCheck(int col) {
    // Ajoute le jeton du joueur dans la colonne 'col'
    grid[colsCounter[col]++][col] = quiJoue;
    // Vérifie la grille de jeu
    CheckGrid(col);
    // Coup joué + vérification
    coups++;
    gameOver = (gameWon || coups==maxCoups);
};

// Méthode pour déterminer si un joueur à gagné
void Game::CheckGrid(int col) {
    // Reset du score associé au coup joué
    scoreCoup[0] = scoreCoup[1] = scoreCoup[2] = 0;

    // Variable pour contenir la position de la rangé du jeton joué
    int row = colsCounter[col] - 1;

    // Variable pour déterminer si on sort de la grille
    bool flag = false;

    // Variables utilisées comme balises
    int indexOne, indexTwo;

    // Vérification horizontale ( de gauche vers la droite )
    int _col; // == col - 3
    // Clipping
    if (col < 3) 
        _col = 0;
    else 
        _col = col - 3;

    // Loop pour obtenir la première valeur de score
    for (int i = 0; i < 4; i++) {
        indexOne = grid[row][_col++];
        scoreCoup[indexOne]++;
    }
    
    // Vérifie si le jouer a gagné
    if (scoreCoup[quiJoue] == 4) {
        gameWon = true;
        return;
    }

    // Boucle sur le reste de la rangé
    while (_col < col + 3 && _col < cols) {
        indexOne = grid[row][_col-3];
        indexTwo = grid[row][_col++];
        // Modifie la valeur de score
        scoreCoup[indexOne]--;
        scoreCoup[indexTwo]++;
        // Vérifie si le joueur a gagné
        if (scoreCoup[quiJoue] == 4) {
            gameWon = true;
            return;
        }
    }

    // Reset du score associé au coup joué
    scoreCoup[0] = scoreCoup[1] = scoreCoup[2] = 0;

    // Vérification verticale ( de haut vers le bas )
    int _row = 0;
    // Vérifie si il y a au moins 4 jetons dans la colonne
    if (row > 2) {
        _row = row;
        // Boucle sur la colonne
        for (int i = 0; i < 4; i++) {
            indexOne = grid[_row--][col];
            scoreCoup[indexOne]++;
        }
        // Vérifie si le joueur a gagné
        if (scoreCoup[quiJoue] == 4) {
            gameWon = true;
            return;
        }
        // Reset du score associé au coup joué
        scoreCoup[0] = scoreCoup[1] = scoreCoup[2] = 0;
    }

    // Vérification diagonale #1 ( bas-gauche vers haut-droite )
    _row = row - 3;
    _col = col - 3;
    // Clipping
    if (_row < 0) {_col = _col - _row; _row = 0;}
    if (_col < 0) {_row = _row - _col; _col = 0;}

    // Boucle sur les 4 premiers éléments
    for (int i = 0; i < 4; i++) {
        indexOne = grid[_row++][_col++];
        scoreCoup[indexOne]++;
        // Vérifie si on sors de la grille de jeu
        if (_row >= rows || _col >= cols) {flag = true; break;}
    }
    // Vérifie si le joueur a gagné
    if (scoreCoup[quiJoue] == 4) {
        gameWon = true;
        return;
    }
    // Boucle sur le reste de la diagonale
    while (!flag && _row < rows && _col < cols && _row < row+4 && _col < col+4) {
        indexOne = grid[_row-3][_col-3];
        indexTwo = grid[_row++][_col++];
        // Update score
        scoreCoup[indexOne]--;
        scoreCoup[indexTwo]++;
        // Vérifie si score gangnant
        if (scoreCoup[quiJoue] == 4) {
            gameWon = true;
            return;
        }
    }

    // Reset du score associé au coup joué
    scoreCoup[0] = scoreCoup[1] = scoreCoup[2] = 0;
    flag = false;

    // Vérification diagonale #2 ( haut-gache vers bas-droit )
    _row = row - 3;
    _col = col + 3;

    // Clipping
    if (_row < 0) {_col = _col + _row; _row = 0;}
    if (_col >= cols) {_row = _row + (_col - cols + 1); _col = cols-1;}

    // Premiere boucle sur la seconde diagonale
    for (int i = 0; i < 4; i++) {
        indexOne = grid[_row++][_col--];
        scoreCoup[indexOne]++;
        // Vérifie si on est hors domaine
        if (_row >= rows || _col < 0) {flag = true; break;}
    }
    
    // Vérifie si score gangnant
    if (scoreCoup[quiJoue] == 4) {
        gameWon = true;
        return;
    }
    
    // Boucle sur le reste de la diagonale
    while (!flag && _row < rows && _col >= 0 && _row > row-4 && _col < col-4) {
        indexOne = grid[_row-3][_col+3];
        indexTwo = grid[_row++][_col--];
        // Update score
        scoreCoup[indexOne]--;
        scoreCoup[indexTwo]++;
        // Vérifie si score gangnant
        if (scoreCoup[quiJoue] == 4) {
            gameWon = true;
            return;
        }
    }
}

// Méthode pour afficher la grille
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

// Méthode pour afficher les résultats d'une partie
void Game::PrintGameResults() {
    // Détermine un joueur a gagné
    if (gameWon) {
        // Félicite le joueur
        cout << "Félicitation " << joueurs[quiJoue] << ", vous avez gagné la partie!\n\n";
        // Update score
        score[quiJoue]++;
    } else {
        // Sinon, partie nulle
        cout << "Partie nulle!\n\n";
    }
    // Affiche le score 
    cout << "C'est maintenant " << score[0] << " à " << score[1] << "!\n\n";
}
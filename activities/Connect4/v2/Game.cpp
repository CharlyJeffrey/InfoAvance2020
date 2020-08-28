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
    grid = new int*[_rows];
    for (int i = 0; i < rows; i++) {
        grid[i] = new int[_cols];
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
    
    gameOver = false;
    quiJoue = false;

    // Initialise la grille de jeu
    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < cols; j++) grid[i][j] = 2;

    // Initialise le comtpeur
    for (int i = 0; i < cols; i++) colsCounter[i] = 0;
}

// Méthode pour déterminer si une colonne est pleine
bool Game::IsColumnFull(int col) {return colsCounter[col] < rows;}

// Méthode pour obtenir le nom du joueur qui joue
string Game::GetCurrentPlayer() {return joueurs[quiJoue];}

// Méthode pour changer le joueur qui joue
void Game::ChangeJoueur() {quiJoue = !quiJoue;}
 
void Game::PlayGame() {
    // Variable pour contenir le choix du joueur
    int choix;

    // Boucle de jeu principale
    while (!gameOver) {
        // Affiche la grille
        PrintGrid();
        // Obtient un choix valide
        GetValidChoice(&choix);
        // Place le jeton
        PlaceJeton(choix);
        // Change de joueur
        quiJoue = !quiJoue;
    }
}

// Méthode pour obtenir le status d'un choix
EChoiceStatus Game::GetChoiceStatus(int choix) {
    // Vérifie si le choix fait n'est pas un nombre
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
    cout << GetCurrentPlayer() << " à vous de jouer!\n";
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
void Game::PlaceJeton(int col) {
    // Ajoute le jeton du joueur dans la colonne 'col'
    grid[colsCounter[col]++][col] = quiJoue;
};

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

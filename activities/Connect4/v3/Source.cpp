#include <stdlib.h>
#include "Game.cpp"

/* MACRO */
#define ROWS 6
#define COLS 7

/* HEADER */
int GetValidChoice(Game*);

int main() {
    // Variables pour contenir le nom de chque joueur
    string joueur1, joueur2;
    cout << "Joueur 1, entrez votre nom: "; 
    getline(cin, joueur1);
    cout << "Joueur 2, entrez votre nom: "; 
    getline(cin, joueur2);
    cout << endl;
    // Place les noms dans un array
    string joueurs[2] = {joueur1, joueur2};

    // Instancie une classe de jeu
    Game CFG = Game(ROWS, COLS, joueurs);


    // Variable pour contenir le choix du joueur
    int choix;

    // Boucle de jeux principale
    while (!CFG.IsGameOver()) {
        // Affiche la grille
        CFG.PrintGrid();
        // Demande au joueur son choix
        choix = GetValidChoice(&CFG);
        // Place le jeton
        CFG.PlaceJeton(choix);
        // Vérfie la grille
        CFG.CheckGrid(choix);
        // Change de joueur
        CFG.ChangeJoueur();
    }
    return 0;
}


// Fonction pour obtenir un choix valide d'un joueur
int GetValidChoice(Game * CFG) {
    // Variable pour contenir le status du joueur
    EChoiceStatus status = EChoiceStatus::DEFAULT;
    // Initialise une variable pour contenir le choix du joueur
    int choix;

    // Boucle 
    while(status != EChoiceStatus::OK) {
        // Demande au joueur dans quelle colonne il veut placer son jeton
        cout << "Dans quelle colonne voulez-vous jouer?" << endl;
        cin >> choix;
        // Update status
        status = CFG->GetChoiceStatus(choix);
    }
    // Retourne le choix du joueur
    return choix;
}
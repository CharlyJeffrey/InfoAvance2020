/*

*/

#include <stdlib.h>
#include "Game.cpp"


int main() {

    int rows = 6;
    int cols = 7;

    Game CFG = Game(rows, cols);


    int rep;
    while (true) {
        CFG.printGrid();
        cout << "colonne: ";
        cin >> rep;
        cout << endl;

        if (rep >= cols) break;

        CFG.play(rep);

        if (CFG.getGameOver()) break;

    }

    return 0;
}
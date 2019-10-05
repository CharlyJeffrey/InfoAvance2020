#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>

using namespace std;

class Game {
    public:
        Game();
        Game(int, int);

        bool getGameOver();

        void play(int);
        void checkGrid(int);
        void printGrid();

    private:
        int rows;
        int cols;

        int * colCounter;

        bool player;
        bool gameOver;

        int ** grid;
        string symboles;

};
/*

*/

#include "Game.h"

Game::Game(int _rows, int _cols) {
    rows = _rows;
    cols = _cols;

    player = false;
    gameOver = false;

    colCounter = new int [_cols];
    for (int i = 0; i < _cols; i++) colCounter[i] = 0;

    grid = new int* [_rows];
    for (int i = 0; i < _rows; i++) {
        grid[i] = (int*) malloc(_cols * sizeof(int));
        for (int j = 0; j < _cols; j++) {
            grid[i][j] = 2;
        }
    }

    symboles = "XO ";
    
}

bool Game::getGameOver() {return gameOver;}

void Game::checkGrid(int col) {
    // Position initiale
    int _col = col;
    int _row = colCounter[col]-1;
    // Score de la vérification
    int score = 0;
    int winningScore = 4 * symboles[player];
    cout << "row : " << _row << "  col : " << _col << "  score : " << winningScore << endl;

    // Horizontal check
    cout << "Horizontal Check\n";
    int c = col - 3;
    // Clipping
    if (c < 0) c = 0;

    // Loop pour obtenur la première valeur de 'score'
    for (int i = 0; i < 4; i++) {
        if (grid[_row][c++] == player) score = score + symboles[player];
        else score = 0;
    }

    if (score == winningScore) {gameOver = true; return;}

    // Boucle sur le reste de la rangé
    while (c < _col+3 && c < cols) {
        score = score - grid[_row][c-3] + grid[_row][c++];
        if (score == winningScore) {gameOver = true; return;}
    }

    score = 0;

    int r;
    // Vertical check
    cout << "Vertical Check\n";
    if (_row > 2) {
        r = _row;
        for (int i = 0; i < 4; i++) {
            if (grid[r--][col] == player) score = score + symboles[player];
            else score = 0;
        }
        if (score == winningScore) {gameOver = true; return;}
    }

    score = 0;
    // First Diagonal check
    cout << "First Diagonale Check\n";
    r = _row - 3;
    c = _col - 3;
    if (r < 0) {c = c - r; r = 0;}
    if (c < 0) {r = r - c; c = 0;}

    for (int i = 0; i < 4; i++) {
        if (r >= rows || c >= cols) break;
       
        if (grid[r++][c++] == player) score = score + symboles[player];
        else score = 0;
    }
    
    if (score == winningScore) {gameOver = true; return;}

    while (r < rows && c < cols && r <= _row + 3 && c <= _col + 3) {
        if (grid[r++][c++] == player) {
            score = score + symboles[player];
            if (score == 4 * winningScore) {gameOver = true; return;}
        }
        else score = 0;
    }

    score = 0;
    
    // Second Diagonal check
    r = _row + 3;
    c = _col - 3;
    if (r >= rows) {c = c - r + rows; r = rows - 1;}
    if (c < 0) {r = r + c; c = 0;}

    cout << r << " " << c << endl;

    for (int i = 0; i < 4; i++) {
        if (r < 0 || c >= cols) break;
       
        if (grid[r--][c++] == player) score = score + symboles[player];
        else score = 0;
    }
    
    if (score == winningScore) {gameOver = true; return;}
    
}

void Game::play(int col) {
    if (col < cols && colCounter[col] < rows) {
        int row = colCounter[col]++;
        if (row < rows) grid[row][col] = player;
        else colCounter[col]--;
    } 
    checkGrid(col);
    

    player = !player;
}

void Game::printGrid() {
    for (int i = rows-1; i >= 0; i--) {
        for (int j = 0; j < cols; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// EightQueens.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <bitset>

using namespace std;

#define NUM_ROWS_COLS 8

typedef struct _attacked_t {
    bitset<NUM_ROWS_COLS> rows;
    bitset<NUM_ROWS_COLS> cols;
    bitset<NUM_ROWS_COLS * 2 - 1> slashes;
    bitset<NUM_ROWS_COLS * 2 - 1> backslashes;
} attacked_t;


bool isRowAttacked(int y);
bool isColAttacked(int x);
bool isSlashAttacked(int x, int y);
bool isBackSlashAttacked(int x, int y);

void attackRow(int y);
void attackCol(int x);
void attackSlash(int x, int y);
void attackBackSlash(int x, int y);
void unAttackRow(int y);
void unAttackCol(int x);
void unAttackSlash(int x, int y);
void unAttackBackSlash(int x, int y);

void printChessBoard();


attacked_t attacked = { 0,0,0,0 };

char chessBoard[NUM_ROWS_COLS][NUM_ROWS_COLS] = { ' ' };

int placeQueen(int row);

void attackQueen(int x, int y);

void unAttackQueen(int x, int y);


int numChessBoards = 0;


int main()
{
    placeQueen(0);
    cout << endl << "Number of solutions for " << NUM_ROWS_COLS << "x" << NUM_ROWS_COLS << " board: " << numChessBoards << endl;
}

int placeQueen(int row) {
    if (row == NUM_ROWS_COLS) {
        numChessBoards++;
        printChessBoard();
        cout << endl << endl;
        return 0;
    }
    for (int y = row; y < NUM_ROWS_COLS; y++) {
        for (int x = 0; x < NUM_ROWS_COLS; x++) {
            if (!isRowAttacked(y) && !isColAttacked(x) && !isSlashAttacked(x,y) && !isBackSlashAttacked(x,y)) {
                attackQueen(x, y);
                //printChessBoard();
                placeQueen(y + 1);
                unAttackQueen(x, y);
            }
        }
        return 1;
    }
}


void attackQueen(int x, int y) {
    chessBoard[y][x] = 'Q';
    attackRow(y);
    attackCol(x);
    attackSlash(x, y);
    attackBackSlash(x, y);
}

void unAttackQueen(int x, int y) {
    chessBoard[y][x] = ' ';
    unAttackRow(y);
    unAttackCol(x);
    unAttackSlash(x, y);
    unAttackBackSlash(x, y);
}


void printChessBoard() {
    cout << "-";
    for (int a = 0; a < NUM_ROWS_COLS; a++) {
        cout << "----";
    }
    cout << endl;
    //cout << "| Q |   |   |   |   |   |   |   |";
    for (int y = 0; y < NUM_ROWS_COLS; y++) {
        cout << "|";
        for (int x = 0; x < NUM_ROWS_COLS; x++) {
            if (chessBoard[y][x] == 'Q') {
                cout << " Q |";
            }
            else if (isColAttacked(x) || isRowAttacked(y) || isSlashAttacked(x,y) || isBackSlashAttacked(x,y)) {
                chessBoard[y][x] = '*';
                cout << "   |";
            }
            else {
                cout << "   |";
            }
        }
        cout << endl;
        cout << "-";
        for (int a = 0; a < NUM_ROWS_COLS; a++) {
            cout << "----";
        }
        cout << endl;
    }
}

bool isRowAttacked(int y) {
    return attacked.rows[y];
}

bool isColAttacked(int x) {
    return attacked.cols[x];
}

bool isSlashAttacked(int x, int y) {
    return attacked.slashes[x + y];// &(1 << (x + y)));
}

bool isBackSlashAttacked(int x, int y) {
    return attacked.backslashes[x - y + NUM_ROWS_COLS - 1];
}

void attackRow(int y) {
    attacked.rows[y] = true;
}

void attackCol(int x) {
    attacked.cols[x] = true;
}

void attackSlash(int x, int y) {
    attacked.slashes[x + y] = true;
}

void attackBackSlash(int x, int y) {
    attacked.backslashes[x - y + NUM_ROWS_COLS - 1] = true;
}


void unAttackRow(int y) {
    attacked.rows[y] = false;
}

void unAttackCol(int x) {
    attacked.cols[x] = false;
}

void unAttackSlash(int x, int y) {
    attacked.slashes[x + y] = false;
}

void unAttackBackSlash(int x, int y) {
    attacked.backslashes[x - y + NUM_ROWS_COLS - 1] = false;
}






// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

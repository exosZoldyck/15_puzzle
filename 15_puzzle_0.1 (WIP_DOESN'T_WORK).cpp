#include <iostream>
#include <iomanip> // For spacing

using namespace std;

void draw(int *pos) {
    cout << "--------------------" << endl;

    for (int i = 0; i < 16; i++) {
            if (i == 4 || i == 8 || i == 12) { cout << endl; } // Spacing

            cout << setw(5) << *(pos + i);
    }

    cout << endl << endl << "--------------------";

    return;
}

void grabPos(int *pos, int *pi, int *pj, int *px) {
    *px = -1;

    for (*pi = 0; *pi < 4; *pi++) {
        for (*pj = 0; *pj < 4; *pj++) {
            (*px)++;

            if (*(pos + (*px)) == 0) { return; }
        }
    }
}

int inputCheck(int input, int *pos) {
    int i, j, x, *pi = &i, *pj = &j, *px = &x;
    grabPos(pos, pi, pj, px); // Finds the empty field

    int check = 0;

    switch (input) { // Checks if the swap can be done according to the direction set by the input
        case 1: // Up
        if (i - 1 < 0) {check++;}
        break;

        case 2: // Left
        if (j - 1 < 0) {check++;}
        break;

        case 3: // Right
        if (j + 1 > 3) {check++;}
        break;

        case 4: // Down
        if (i + 1 > 3) {check++;}
        break;
    }

    if (check != 0) { return 1; }
    else { return 0; }
}

void swap(int input, int *pos){
    int i, j, x, *pi = &i, *pj = &j, *px = &x;
    grabPos(pos, pi, pj, px); // Finds the empty field

    int temp_var; // Temporary variable for keeping values saved while swapping

    switch (input) { // Swaps the spots according to the input value
        case 1: // Up
        temp_var = *(pos + (*px));
        *(pos + (*px)) = *((pos) + (*px) - 4);
        *((pos) + (*px) - 4) = temp_var;
        break;

        case 2: // Left
        temp_var = *(pos + (*px));
        *(pos + (*px)) = *((pos) + (*px) - 1);
        *((pos) + (*px) - 1) = temp_var;
        break;

        case 3: // Right
        temp_var = *(pos + (*px));
        *(pos + (*px)) = *((pos) + (*px) + 1);
        *((pos) + (*px) + 1) = temp_var;
        break;

        case 4: // Down
        temp_var = *(pos + (*px));
        *(pos + (*px)) = *((pos) + (*px) + 4);
        *((pos) + (*px) + 4) = temp_var;
        break;
    }
}

void move(int input, int *pos, int *fail_cond) {
    if (inputCheck(input, pos) == 1) { *fail_cond++; return; } // Checks if input is valid

    swap(input, pos); // Swaps a spot with the empty slot according to the input value
}

void randomMoveGen(int *pos) {
    int move_random, fail_cond, *pfail_cond = &fail_cond;

    restart:
    move_random = ((rand() % 4) + 1); // Generates a random move

    move(move_random, pos, pfail_cond); // Executes a move if the input value is valid

    if (fail_cond != 0) { goto restart; } // Starts new input genesis if input is invalid
}



void randomGen(int *pos){
    int seed, seed_reset;

    seed = ((rand() % 100) + 1); // Generates seed for random move generation

    while (seed_reset < seed) {
        randomMoveGen(pos); // Generates random move

        seed_reset++; // Adds up every repetition (for ending the random move loop)
    }
}



int main()
{
    int pos_m[4][4] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12},  {13, 14, 15, 0} };
    int *pos = &pos_m[0][0]; // Critical pointer for all calculations
    
    randomGen(pos); // Generates a random puzzle layout
    draw(pos);
}
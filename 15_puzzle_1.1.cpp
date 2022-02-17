// 15 Puzzle (1.1) by exosZoldyck

// New in version 1.1:
//  - added movement instructions
//  - other small text changes

#include <iostream>
#include <math.h>
#include <iomanip> // For spacing

using namespace std;

void draw(int* pos) {
    cout << "------------------------" << endl << endl;

    for (int i = 0; i < 16; i++) {
        if (i == 4 || i == 8 || i == 12) { cout << endl << endl; } // Spacing

        cout << setw(5) << *(pos + i);
    }

    cout << endl << endl << "------------------------";

    return;
}

void grabPos(int* pos, int* pi, int* pj, int* px) {
    int jj  = -1;
    *px = -1;

    for ((*pi) = 0; *pi < 16; (*pi)++) {
            (*px)++;
            jj++;

            if (*((pos) + jj) == 0) { return; }
    }
}

int inputCheck(int input, int* pos) {
    int i, j, x, * pi = &i, * pj = &j, * px = &x;
    grabPos(pos, pi, pj, px); // Finds the empty field

    int check = 0;

    switch (input) { // Checks if the swap can be done according to the direction set by the input
    case 4: // Up
        if (*px - 4 < 0) { check  = 1; }
        break;

    case 3: // Left
        if (*px - 1 < 0 || *px - 1 == 3 || *px - 1 == 7 || *px - 1 == 11) { check = 1; }
        break;

    case 2: // Right
        if (*px + 1 > 15 || *px + 1 == 4 || *px + 1 == 8 || *px + 1 == 12) { check = 1; }
        break;

    case 1: // Down
        if (*px + 4 > 15) { check = 1; }
        break;
    }

    if (check != 0) { return 1; } // Gives output based on input validity
    else { return 0; }
}

void swap(int input, int* pos) {
    int i, j, x, * pi = &i, * pj = &j, * px = &x;
    grabPos(pos, pi, pj, px); // Finds the empty field

    int temp_var; // Temporary variable for keeping values saved while swapping

    switch (input) { // Swaps the spots according to the input value
    case 4: // Up
        temp_var = *(pos + (x));
        *(pos + (x)) = *(pos + (x - 4));
        *(pos + (x - 4)) = temp_var;
        break;

    case 3: // Left
        temp_var = *(pos + (x));
        *(pos + (x)) = *(pos + (x - 1));
        *(pos + (x - 1)) = temp_var;
        break;

    case 2: // Right
        temp_var = *(pos + (x));
        *(pos + (x)) = *(pos + (x + 1));
        *(pos + (x + 1)) = temp_var;
        break;

    case 1: // Down
        temp_var = *(pos + (x));
        *(pos + (x)) = *(pos + (x + 4));
        *(pos + (x + 4)) = temp_var;
        break;
    }
}

void move(int input, int* pos, int* fail_cond) {
    *fail_cond = 0;

    int check = inputCheck(input, pos);

    if (check == 1) { (*fail_cond)++; return; } // Checks if input is valid

    swap(input, pos); // Swaps a spot with the empty slot according to the input value
}

void randomMoveGen(int* pos) {
    int move_random, fail_cond(0), * pfail_cond = &fail_cond;

    restart:
    fail_cond = 0;

    move_random = ((rand() % 4) + 1); // Generates a random move

    move(move_random, pos, pfail_cond); // Executes a move if the input value is valid

    if (fail_cond != 0) { goto restart; } // Starts new input genesis if input is invalid
}

int getInput() {
    char input;

    char inputLetter[9] = "wWaAdDsS"; // Acceptable inputs

    reset:
    cout << endl << endl << "Input move: "; cin >> input; // Askes the player for an input and saves it in memory

    if (input == inputLetter[0] || input == inputLetter[1]) {return 1;} // Checks what the input is
    else if (input == inputLetter[2] || input == inputLetter[3]) {return 2;}
    else if (input == inputLetter[4] || input == inputLetter[5]) {return 3;}
    else if (input == inputLetter[6] || input == inputLetter[7]) {return 4;}
    else {cout << endl << "Invalid input!!!" << endl; goto reset; } // Restarts input if input was invalid

    return 0;
}



void randomGen(int* pos) {
    int seed, seed_reset(0);
    float seed2, seed_reset2, nomess, nomess2;

    srand(time(0)); // Makes the rng actually random
    seed = ((rand() % 1000) + 1); // Generates seed for random move generation

    cout << "Seed = " << seed << endl;

    while (seed_reset < seed) {
        randomMoveGen(pos); // Generates random move

        seed_reset++; // Adds up every repetition (for ending the random move loop)

        seed2 = seed; seed_reset2 = seed_reset;
        nomess2 = nomess;
        nomess = round((seed_reset2/seed2) * 100);
        if (round(nomess) != round(nomess2)) {cout << "Random seed generation progress: " << nomess << "% ("
        << seed_reset << " / " << seed << ")" << endl;}
    }
    
    cout << "Random seed generation progress: 100% ("<< seed << " / " << seed << ")" << endl;

    cout << endl; draw(pos); // Draws game layout
}



void startGame(int *pos) {
    int input, fail_cond_m, *fail_cond = &fail_cond_m;

    cout << endl << "Controls: W (up), A (left), S (down), D (right)" << endl;

    reInput:
    input = getInput(); // Askes and defines the player input

    move(input, pos, fail_cond); // Tries to commit the move according to the input

    if (*fail_cond != 0) { cout << endl << "Invalid input!!!"; goto reInput; } // Makes the player give a new input if input is invalid

    cout << endl; draw(pos); // Draws game layout

    goto reInput; // Makes the player input the next input
}



int main()
{
    int pos_m[4][4] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12},  {13, 14, 15, 0} };
    int* pos = &pos_m[0][0]; // Critical pointer for all calculations

    randomGen(pos); // Generates a random puzzle layout and draws it

    startGame(pos); // Starts the game
}
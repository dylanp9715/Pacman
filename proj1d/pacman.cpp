// pacman.cpp
// purpose: pacman class implementation
// by: dylan park
// date: 30 March 2016
//
//
#include <iostream>
using namespace std;

#include "termfuncs.h"
#include "constants.h"
#include "pacman.h"

// pacman constructor
// purpose: to initialize the private members of the pacman class
// arguments: none
// return value: none
Pacman::Pacman() {
        alive = true;
        num_moves = 0;
        score = 0; 
}

// purpose: change pacman's location to be the center of the board and have
// pacman face up
// arguments: none
// return value: none
void Pacman::center() {
        head = UP;
        row = 10;
        col = 30;
}

// purpose: call functions that move pacman based on user input, sets alive to
// false if pacman hits a ghost, sets alive to true if he hits a dot, and 
// increments num_moves every time function is called
// arguments: board array and char command
// return value: bool value
bool Pacman::move(char board[ROWS][COLS], char command) {
        num_moves++; // increment num_moves every time move function is called
        move_forward(board, command);
        if (board[row][col] == GHOST) {
                alive = false;
        }
        else if (board[row][col] == DOT) {
                return true;
        }
        return false;
} 

// purpose: move pacman based on user input
// argument: char command
// return value: none
void Pacman::move_forward(char board[ROWS][COLS], char command) { 
        int r = row;               // declare two variables for rows and cols
        int c = col;               // to keep track of the original values to  
        if (command == CMD_UP) {   // use for when pacman hits the boulder
                board[row][col] = ' ';    // place a space at the location 
                head = UP;                // pacman was just in
                row = row - 1; 
        }
        else if (command == CMD_RGT) {
                board[row][col] = ' ';
                head = RIGHT;
                col = col + 1; 
        }
        else if (command == CMD_DWN) {
                board[row][col] = ' ';
                head = DOWN;
                row = row + 1;   
        }
        else if (command == CMD_LFT) {
                board[row][col] = ' ';
                head = LEFT;
                col = col - 1; 
        }
        wrap_around(); // call wrap around function
        if (board[row][col] == BOULDER) {  //keep pacman in his original
                row = r;                   // position when next to 
                col = c;                   // boulder
        }
}

// purpose: get row location
// argument: none
// return value: int
int Pacman::get_row() {
        return row;
}

// purpose: get col location
// argument: none
// return value: int 
int Pacman::get_col() {
        return col;
}

// purpose: wrap pacman around the border
// arguments: board array and char command
// return value: none
void Pacman::wrap_around() { 
        row = (row + ROWS) % ROWS;
        col = (col + COLS) % COLS;
} 
// purpose : place pacman on the board at the desire location
// argument: board array
// return value: none
void Pacman::place_on_board(char board[ROWS][COLS]) {
        board[row][col] = head;
}

// purpose: set alive to false and display losing message if pacman hits a ghost
// argument: board array
// return value: none
void Pacman::die() {
        alive = false;
        cout << "You Lose" << endl;
}

// purpose: display message if you win the game
// argument: none
// return value: none
void Pacman::win_game() {
        cout << "Congratulations! You made it!" << endl;
}

// purpose: returns if pacman is alive
// arguments: none
// return value: none
bool Pacman::is_alive() {
        return alive;
}

// purpose: returns amount of moves made by pacman
// arguments: none
// return value: int
int Pacman::get_num_moves() {
       return num_moves;
}

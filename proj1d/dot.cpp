// dot.cpp
// purpose: dot class implementation
// date: 28 March 2016
//
//
#include <iostream>
using namespace std;

#include "termfuncs.h"
#include "constants.h"
#include "dot.h"

// dot constructor
// purpose: to initialize the private members of the dot class
// arguments: none
// return value: none
Dot::Dot()
{
        // initialize private variables in dot class
        row = 0;
        col = 0;
        eaten = false;
}

// purpose: chooses a random location for the dot on the board
// argument: board array
// return value: none 
void Dot::set_random_location(char board[ROWS][COLS])
{
        // generate random numbers to use for the place_on_board function
        row = random_int(0, ROWS-1);
        col = random_int(0, COLS-1);
        // if the random location in the board array is a space, put a dot 
        // at that location. if not, rerun this function and create a new
        // random location
        if (board[row][col] == ' ') {
                place_on_board(board);
        }
        else {
                set_random_location(board);
        }
 
}

// purpose: places the dot in the board array
// argument: board array
// return value: none
void Dot::place_on_board(char board[ROWS][COLS])
{
        board[row][col] = DOT; 
}

// purpose: sets eaten to be the passed in bool
// arguments: bool
// return value none
void Dot::set_eaten(bool s) {
        eaten = s;
}

// purpose: returns true if the dot has been eaten
// arguments: none
// return value: bool value
bool Dot::was_eaten() {
        if (eaten == true) {
                return true;
        }
        else {
                return false;
        }
}
 
// purpose: returns if the dot is at this row and col
// arguments: int r and int c
// return value: bool 
bool Dot::is_at(int r, int c) {
        if (row == r and col == c) {
                return true;
        }
        else {
                return false;
        }
}

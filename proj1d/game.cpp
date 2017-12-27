/*******************************************************************************
 * Game Class Implementation                                                   *
 * For Pacman Game (COMP 11 Project 1 | 2016 Spring)                           *
 *****************************************************************************/

#include <iostream>
#include "termfuncs.h"
using namespace std;

#include "game.h"
#include "pacman.h"
#include "ghost.h"
#include "dot.h"
#include "termfuncs.h"


/* Constructor */
Game::Game()
{
        // fill array with initial blank spaces
        for (int r = 0; r < ROWS; r++) {
               for (int c = 0; c < COLS; c++) {
                       board[r][c] = ' ';
               }
        }
        dots_eaten = 0;
        dots_per_level = DOTS_PER_LEVEL;        // variables needed to multiply
        boulders_per_level = BOULDERS_PER_LEVEL;// num of dots and boulders by 
        level = 1;                              // current level value
        score = 0;
        result_move = false;
        result_ghost = false; 
}

/* print_manual()
 * Purpose:   Prints the manual and stalls until the user types a character
 * Arguments: None
 * Returns:   None
 */
void Game::print_manual()
{
        screen_clear();
        cout << "PACMAN GAME\n"
                "            \n"
                " Move left:    " << CMD_LFT << "\n"
                " Move right:   " << CMD_RGT << "\n"
                " Move up:      " << CMD_UP  << "\n"
                " Move down:    " << CMD_DWN << "\n"
                "\n"
                " Collect all the dots. They look like: " << DOT << "\n"
                " Avoid the ghosts.     They look like: " << GHOST << "\n"
                "\n"
                " Good luck!\n"
                "\n"
                " Press any key to continue...\n";

        getachar();
}

// purpose: run the pacman game
// argument: none
// return value: none
void Game::run()
{
        set_up_board();
        cout << "Level " << level << ": Press any key to start" << endl;
        getachar();
        while (p.is_alive() and dots_eaten != dots_per_level) {//game runs until
                command = getacharnow(SPEED);                  //all dots eaten
                if (command == 'g') {                          // or you are 
                        dots_eaten = dots_per_level;           // killed
                }
                move_ghosts();   // have the ghosts move and kill pacman 
                result_move = p.move(board, command); // move pacman 
                p.place_on_board(board);  // places updated pacman on the board
                if (result_move == true) { // if you eat a dot...
                        for (int i = 0; i < dots_per_level; i++) {
                                if (dots[i].is_at(p.get_row(), p.get_col())) {
                                        dots[i].set_eaten(true);
                                        dots_eaten++;
                                        score++;
                                }
                        }
                }  
                print_border();      // reprint updated board
        }
        level_over();    // determine what to do next(end game/go to next level)
}                       

// purpose: call functions to put the boulders, dots, pacman, and ghosts in the
// array and then call the print_border function to print out the updated array 
// argument: none
// return value: none
void Game::set_up_board() 
{ 
        for (int r = 0; r < ROWS; r++) {
               for (int c = 0; c < COLS; c++) {
                      board[r][c] = ' ';
               }
        }  
        for (int i = 0; i < boulders_per_level; i++) { // call functions to put
                boulders[i].place_on_board(board);     // boulders, dots,and 
        }                                              // ghosts in the board 
        for (int i = 0; i < dots_per_level; i++) {     // array      
                dots[i].set_random_location(board);
        }
        p.center(); // place pacman
        p.place_on_board(board); 
        ghosts[0].set_location(0,0);
        ghosts[1].set_location(0,COLS-1);
        ghosts[2].set_location(ROWS-1,0);
        ghosts[3].set_location(ROWS-1,COLS-1);
        for (int i = 0; i < NUM_GHOSTS; i++) {
                ghosts[i].place_on_board(board);
        }
        print_border();  // print surrounding border and the board array itself
}

// purpose: print out the border and the updated array 
// argument: none
// return value: none
void Game::print_border()
{
        screen_clear();
        screen_home();
        cout << BORD_CORN; // print border
        for (int i = 0; i < COLS; i++) {
                cout << BORD_TOP;
        }
        cout << BORD_CORN << endl;
        for (int r = 0; r < ROWS; r++) {         
                cout << BORD_SIDE;                    
                for (int c = 0; c < COLS; c++) {
                        cout << board[r][c];   // print out the updated array 
                }                              // with the spaces, boulders,
                cout << BORD_SIDE << endl;     // ghosts, and dots
        }
        cout << BORD_CORN;
        for (int i = 0; i < COLS; i++) {
                cout << BORD_TOP;
        }
        cout << BORD_CORN << endl;
        cout << "Score: " << score << endl;
}

// purpose: to determine which function to call after level is over
// argument: none
// return value: none
void Game::level_over() {
        if (p.is_alive() == false) {  // if you died, call die() to print losing
                board[p.get_row()][p.get_col()] = GHOST; // message and replace 
                print_border();                          // pacman with ghost
                p.die();        
        }
        if (p.is_alive() and level != NUM_LEVELS) {
                level++; // run next level function to reprint board with
                next_level();// new num of boulders and dots as long as current
        }                    // completed level is not the last one (10)
        else if (p.is_alive() and level == NUM_LEVELS) {
                cout << "You win!! Congratulations!" << endl;
        }
}

// purpose: to move the ghosts automatically and have them kill pacman if they 
// run into him
// arguments: none
// return value: none
void Game::move_ghosts() {
        if (p.is_alive()) {   // as long as pacman is alive...
                for (int i = 0; i < NUM_GHOSTS; i++) {
                        if (p.get_num_moves() % GHOST_FREQ == 0) { //ghosts move
                                result_ghost = ghosts[i].move(board,//even when 
                                p.get_row(), p.get_col());//there is no input
                                if (result_ghost) {// if ghost runs 
                                        p.die();   // into pacman, you
                                }                  // die
                        ghosts[i].place_on_board(board); // put ghosts on board
                        }
                }
        }
}
// purpose: start the next level, get rid of the last pacman and ghosts,
// update the number of dots and boulders printed on the board, and reset the
// number of dots currently eaten back to zero
// argument: none
// return value: none
void Game::next_level() {
        screen_clear();
        dots_eaten = 0;   // reset the number of dots eaten back to zero
        dots_per_level = DOTS_PER_LEVEL * level; // increase num of dots
        boulders_per_level = BOULDERS_PER_LEVEL * level; // and boulders
        board[p.get_row()][p.get_col()] = ' ';  // get rid of last pacman 
        for (int i = 0; i < NUM_GHOSTS; i++) {  // get rid of last ghosts
                board[ghosts[i].get_row()][ghosts[i].get_col()] = ' ';
        }
        run();   // run the game again
}

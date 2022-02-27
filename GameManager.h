/*
 * Tunji Afolabi-Brown
 * CIS 554-M401 Object-Oriented Programming in C++ - Syracuse University
 * HW #5 - Minesweeper
 * GameManager.h - Runs and manages the game of minesweeper
*/

#ifndef HW5_GAMEMANAGER_H
#define HW5_GAMEMANAGER_H

#include "MineField.h"
#include <string>

// A class for controlling the game
// does not expose any internal state so no getters or setters
class GameManager {
private:
    // Holds the minefield, aka the game state
    MineField mineField;

    // gets a command from the user, free/mine, and modifies the board
    void getCommand();

    // returns if the game is over, controlled by the minefield
    bool gameOver();

    // helper for getCommand
    // checks if input received is a valid command
    static bool isValidCommand(const std::vector<std::string> &command);

    // helper for getCommand
    // checks if arguments to command are valid in-range ints
    // "returns" the parsed ints through the reference parameters
    static bool validCommandArgs(const std::vector<std::string> &command, int &xVal, int &yVal);

public:
    // constructor, initializes the minefield
    GameManager();

    // runs the game
    void runGame();
};

#endif//HW5_GAMEMANAGER_H

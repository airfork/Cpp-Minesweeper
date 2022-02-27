/*
 * Tunji Afolabi-Brown
 * CIS 554-M401 Object-Oriented Programming in C++ - Syracuse University
 * HW #5 - Minesweeper
 * GameManager.cpp - Function definitions for GameManager.h
 * Also includes some non-external helper functions
 * Runs and manages the game of minesweeper
*/

#include "GameManager.h"
#include "Helpers.h"
#include <iostream>
#include <vector>


// Constructor, create the minefield that we're managing
GameManager::GameManager() : mineField{Helpers::getIntegerFromUser("How many mines do you want on the field (max 79)?")} {}

// run the game
void GameManager::runGame() {
    while (!gameOver()) {
        std::cout << mineField;
        // get command from user
        getCommand();

        // generate mines if they have not been already
        // this will happen automatically if the user calls
        // free first instead of mine
        if (!mineField.minesGenerated()) mineField.generateMines();
    }

    // print out final state of field
    std::cout << mineField;

    // Game is over, get the game status and print out message depending on it
    switch (mineField.getGameStatus()) {
        case GameStatus::EXPLORED_ALL:
            std::cout << "Congratulations, you won! You explored all of the free spaces!\n";
            break;
        case GameStatus::HIT_MINE:
            std::cout << "Boom! Game over, you stepped on a mine!\n";
            break;
        case GameStatus::MARKED_ALL:
            std::cout << "Congratulations, you won! You successfully marked all of the mines!\n";
            break;
        case GameStatus::IN_PROGRESS:
            std::cout << "Uh oh, something went wrong\n";
            break;
    }
}

// get command from user and run it
void GameManager::getCommand() {
    // store input from user
    std::string input{};

    // string to store the name of the command
    std::string command;

    // x coordinate from user
    int xVal{};

    // y coordinate from user
    int yVal{};

    // if the user input is a valid command
    bool valid{false};

    // get input from user until valid
    while (!valid) {
        input = Helpers::getStringFromUser("Set/unset mine marks or claim a cell as free");

        // split input, on space, from user into a vector
        std::vector<std::string> stringSplit{Helpers::split(input, ' ')};

        // check if the command is valid
        if (isValidCommand(stringSplit)) {
            command = std::move(stringSplit[0]);
            valid = true;
        } else {
            std::cout << "The command entered is not valid. Enter 'free' or 'mine' and a x & y value\n";
            // skip checking args
            continue;
        }

        // check arguments
        // if args are not valid, inform user and set valid to false
        if (!validCommandArgs(stringSplit, xVal, yVal)) {
            std::cout << "The arguments of '" << command << "' could not be parsed as valid coordinates (1-9), please try again\n";
            valid = false;
        }
    }

    // run function on minefield based on command
    if (command == "free") {
        mineField.free(xVal, yVal);
    } else if (command == "mine") {
        mineField.targetMine(xVal, yVal);
    } else {
        std::cout << "Something went wrong\n";
    }
}

// check to see if the game is over or not
bool GameManager::gameOver() {
    return mineField.getGameStatus() != GameStatus::IN_PROGRESS;
}

// helper for getCommand, check to see if the command is valid
bool GameManager::isValidCommand(const std::vector<std::string> &command) {
    // make sure vector size matches expected length
    if (command.size() != 3) {
        return false;
    }

    // only valid commands are free and mine
    return command[0] == "free" || command[0] == "mine";
}

// Check arguments to the command and make sure they are both
// numbers and represent valid coordinates
// stores result of command parsing in the two references
bool GameManager::validCommandArgs(const std::vector<std::string> &command, int &xVal, int &yVal) {
    // make sure correct number of arguments are present
    if (command.size() != 3) return false;

    // parse args into ints, any exceptions result in a value of -1 being returned
    xVal = Helpers::parseInt(command[1]);
    yVal = Helpers::parseInt(command[2]);

    // make sure points are in range
    if ((xVal < 1 || xVal > 9) || (yVal < 1 || yVal > 9)) {
        return false;
    }

    // decrement output references
    // user is inputting 1-9, but our internal coordinates start at 0 and
    // end at 8
    xVal--;
    yVal--;
    return true;
}

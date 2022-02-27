/*
* Tunji Afolabi-Brown
* CIS 554-M401 Object-Oriented Programming in C++ - Syracuse University
* HW #5 - Minesweeper
* main.cpp - Main method, starts the game in user controlled loop
*/

#include "GameManager.h"
#include "Helpers.h"
#include <iostream>


int main() {
    // print out welcome message and game instructions
    std::cout << "Welcome to Minesweeper!\n\n";
    std::cout << "How to play:\n"
                 "1. Choose how many mines you want on the field. It's recommend to choose\n"
                 "   at least 8, otherwise the game might immediately end (by design)\n"
                 "   or it will be rather easy to beat\n"
                 "2. Enter free x y (x & y are nums 1-9) to explore a point.\n"
                 "   or enter mine x y to mark a point as a mine.\n"
                 "   Unmark a point as a mine by calling mine on it again.\n"
                 "3. You win if you mark all the mines successfully or if you explore\n"
                 "   all open spaces.\n"
                 "4. You lose if you try to free a point that contains a mine.\n\n";

    // keep track of if user is still playing
    bool stillPlaying{true};
    while (stillPlaying) {
        // create gameManager and run the game
        GameManager gameManager{};
        gameManager.runGame();

        // Game is over, ask user if they want to play again
        const std::string response{Helpers::getStringFromUser("\nEnter 'yes' to play again or enter anything else to exit")};
        // they don't want to play again
        if (response != "yes") {
            // change to false so loop will exit
            stillPlaying = false;
            std::cout << "Thanks for playing!\n";
        } else {
            // give some whitespace before starting the next game
            std::cout << '\n';
        }
    }

    return 0;
}

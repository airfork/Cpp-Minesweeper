/*
 * Tunji Afolabi-Brown
 * CIS 554-M401 Object-Oriented Programming in C++ - Syracuse University
 * HW #5 - Minesweeper
 * Helpers.cpp - Defines some helper functions from
 * Helpers.h that are used throughout the project
*/

#include "Helpers.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

namespace Helpers {
    // taken from learncpp.com
    // This function clears out the std::cin buffer
    void ignoreLine() {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // prompts for a string from the user and returns it
    std::string getStringFromUser(const std::string &prompt) {
        std::cout << prompt << ": ";

        // store input from user
        std::string value{};

        // get line from user and place into string
        std::getline(std::cin, value);
        return value;
    }

    // try to get an integer from the user and return it
    int getIntegerFromUser(const std::string &prompt) {
        // loop until number successfully parsed
        while (true) {
            // prompt user and try to read in value
            std::cout << prompt << ": ";
            int value{};
            std::cin >> value;

            // if parsing failed, clear error from cin and the buffer; try again
            if (std::cin.fail()) {
                std::cin.clear();
                ignoreLine();
                std::cout << "Failed to parse input as a number, try again\n";

                // value must be in range 1 - 79
                // 79 comes from number of points (81) - 2
                // need to have one spot open for first guess and at least
                // one other spot open so that the game does not immediately end
            } else if (value < 1 || value > 79) {
                // value outside of range
                ignoreLine();
                std::cout << "Number must be between 1 and 79, try again\n";
            } else {
                // value parsed; clear buffer and return
                ignoreLine();
                return value;
            }
        }
    }

    // split a string into a vector based on a delimiter
    std::vector<std::string> split(const std::string &s, char delim) {
        // turn string input into string stream so we can read from it
        std::stringstream ss(s);

        // read input into this variable
        std::string item;

        // store split strings in this
        std::vector<std::string> elems;

        // read from stream and delimit on passed in value
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }

        return elems;
    }

    // try to parse an int and return it
    // return -1 if failed to parse
    // this isn't robust, but works for this situation
    int parseInt(const std::string &str) {
        try {
            return std::stoi(str);
        } catch (std::exception const &ex) {
            return -1;
        }
    }
}// namespace Helpers

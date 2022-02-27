/*
 * Tunji Afolabi-Brown
 * CIS 554-M401 Object-Oriented Programming in C++ - Syracuse University
 * HW #5 - Minesweeper
 * Helpers.h - Declares some helper functions that are used throughout the project
*/

#ifndef HW5_HELPERS_H
#define HW5_HELPERS_H

#include <string>
#include <vector>

namespace Helpers {
    // taken from learncpp.com
    // This function clears out the std::cin buffer
    void ignoreLine();

    // prompts for a string from the user and returns it
    std::string getStringFromUser(const std::string &prompt);

    // try to get an integer from the user and return it
    int getIntegerFromUser(const std::string &prompt);

    // split a string into a vector based on a delimiter
    std::vector<std::string> split(const std::string &s, char delim);

    // try to parse an int and return it
    // return -1 if failed to parse
    // this isn't robust, but works for this situation
    int parseInt(const std::string &str);
}// namespace Helpers

#endif//HW5_HELPERS_H

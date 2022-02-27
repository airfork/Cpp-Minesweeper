/*
 * Tunji Afolabi-Brown
 * CIS 554-M401 Object-Oriented Programming in C++ - Syracuse University
 * HW #5 - Minesweeper
 * Point.cpp - Function definitions for Point.h
 * Defines a point on the minefield
*/

#include "Point.h"

// Constructor, initialize the private data members
Point::Point(int x, int y, std::string val) : x{x}, y{y}, val{std::move(val)} {}

// getter for x coordinate
int Point::getX() const {
    return x;
}

// getter for y coordinate
int Point::getY() const {
    return y;
}

// getter for val
const std::string &Point::getVal() const {
    return val;
}

// setter for val
void Point::setVal(const std::string &val) {
    Point::val = val;
}
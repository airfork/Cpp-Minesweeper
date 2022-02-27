/*
 * Tunji Afolabi-Brown
 * CIS 554-M401 Object-Oriented Programming in C++ - Syracuse University
 * HW #5 - Minesweeper
 * Point.h - Defines a point on the minefield
*/

#ifndef HW5_POINT_H
#define HW5_POINT_H

#include <ostream>
#include <string>

// Defines a point on the minefield
class Point {
private:
    // The x coordinate for the point - const
    const int x;

    // The y coordinate for the point - const
    const int y;

    // The value to display for the point
    std::string val;

public:
    // Constructor for point
    Point(int x, int y, std::string val);

    // Getter for x coordinate
    int getX() const;

    // Getter for y coordinate
    int getY() const;

    // Getter for val
    const std::string &getVal() const;

    // Setter for val
    void setVal(const std::string &val);
};


#endif//HW5_POINT_H

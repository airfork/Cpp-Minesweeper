/*
 * Tunji Afolabi-Brown
 * CIS 554-M401 Object-Oriented Programming in C++ - Syracuse University
 * HW #5 - Minesweeper
 * Position.h - An enum holding positions for a point on the field
 * and some related functions
*/

#ifndef HW5_POSITION_H
#define HW5_POSITION_H

#include "MineField.h"
#include "Point.h"
#include <vector>

// Enum for point positions and some related functions
namespace Position {
    // Enum defining the possible positions of a point on the point
    // Using regular enum instead of enum class to avoid namespacing
    enum Position {
        TOP_LEFT,
        TOP,
        TOP_RIGHT,
        LEFT,
        MIDDLE,
        RIGHT,
        BOTTOM_LEFT,
        BOTTOM,
        BOTTOM_RIGHT
    };

    // returns a position based on the point
    Position getPosition(const Point *point);

    // returns the adjacent points based on the point
    std::vector<Point *> getAdjacentPoints(const std::array<std::array<Point *, 9>, 9> &field, const Point *point);
}// namespace Position

#endif//HW5_POSITION_H

/*
 * Tunji Afolabi-Brown
 * CIS 554-M401 Object-Oriented Programming in C++ - Syracuse University
 * HW #5 - Minesweeper
 * Position.cpp - Definitions for position.h
*/

#include "Position.h"

// keep functions internal to file
namespace {
    // typedef to avoid repeating lengthy type
    typedef const std::array<std::array<Point *, 9>, 9> &Field;

    // helper function for getAdjacentPoints
    // handles corner positions
    std::vector<Point *> getCornerAdjacentPoints(Field field, Position::Position position) {
        // holds the adjacent points
        std::vector<Point *> points{};

        // adjacent points for top left are fixed
        if (position == Position::TOP_LEFT) {
            // right
            points.push_back(field[0][1]);
            // right below
            points.push_back(field[1][1]);
            // direct below
            points.push_back(field[1][0]);
        }

        // adjacent points for top right are fixed
        else if (position == Position::TOP_RIGHT) {
            // left
            points.push_back(field[0][7]);
            // left below
            points.push_back(field[1][7]);
            // direct below
            points.push_back(field[1][8]);
        }

        // adjacent points for bottom left are fixed
        else if (position == Position::BOTTOM_LEFT) {
            // above
            points.push_back(field[7][0]);
            // right above
            points.push_back(field[7][1]);
            // right
            points.push_back(field[8][1]);
        }

        // adjacent points for bottom right are fixed
        else if (position == Position::BOTTOM_RIGHT) {
            // above
            points.push_back(field[7][8]);
            // left above
            points.push_back(field[7][7]);
            // left
            points.push_back(field[8][7]);
        }

        return points;
    }

    // helper function for getAdjacentPoints
    // handles positions on the edge of the field
    std::vector<Point *> getEdgeAdjacentPoints(Field field, Position::Position position, const Point *point) {
        // holds the adjacent points
        std::vector<Point *> points{};

        // hold x and y of point
        int x{point->getX()};
        int y{point->getY()};

        // add direct right and left of point
        // making a lambda for ease of use
        auto directLeftRight = [&points, field, x, y]() mutable {
            // left
            points.push_back(field[y][x - 1]);
            // right
            points.push_back(field[y][x + 1]);
        };

        // add above or below of point
        // making a lambda for ease of use
        auto rowAboveOrBelow = [&points, field, x, y](bool above = false) mutable {
            // set y based on if we're adding above or below point
            int targetY{above ? y - 1 : y + 1};

            // above/below left
            points.push_back(field[targetY][x - 1]);

            // direct above/below
            points.push_back(field[targetY][x]);

            // above/below right
            points.push_back(field[targetY][x + 1]);
        };

        // add directly above and below mine
        // making lambda for ease of use
        auto directAboveBelow = [&points, field, x, y]() mutable {
            // directly above
            points.push_back(field[y - 1][x]);

            // directly below
            points.push_back(field[y + 1][x]);
        };

        // add column to left/right of point
        // making lambda for ease of use
        auto colRightOrLeft = [&points, field, x, y](bool left = false) mutable {
            // set x based on if we're adding to the left or right of point
            int targetX{left ? x - 1 : x + 1};

            // above left/right
            points.push_back(field[y - 1][targetX]);

            // direct left/right
            points.push_back(field[y][targetX]);

            // below left/right
            points.push_back(field[y + 1][targetX]);
        };

        // handle top
        if (position == Position::TOP) {
            // add direct left/right and below
            directLeftRight();
            rowAboveOrBelow();
        }

        // handle left
        else if (position == Position::LEFT) {
            // add direct above/below and col to the right
            directAboveBelow();
            colRightOrLeft();
        }

        // handle right
        else if (position == Position::RIGHT) {
            // add direct above/below and col to the left
            directAboveBelow();
            colRightOrLeft(true);
        }

        // handle bottom
        else if (position == Position::BOTTOM) {
            // add direct left/right and row above
            directLeftRight();
            rowAboveOrBelow(true);
        }

        return points;
    }

    // helper function for getAdjacentPoints
    // handles positions in the middle of the field
    std::vector<Point *> getMiddleAdjacentPoints(Field field, const Point *point) {
        // holds the adjacent points
        std::vector<Point *> points{};

        // hold x and y of point
        int x{point->getX()};
        int y{point->getY()};

        // add above left
        points.push_back(field[y - 1][x - 1]);

        // add direct above
        points.push_back(field[y - 1][x]);

        // add above right
        points.push_back(field[y - 1][x + 1]);

        // add direct left
        points.push_back(field[y][x - 1]);

        // add direct right
        points.push_back(field[y][x + 1]);

        // add below left
        points.push_back(field[y + 1][x - 1]);

        // add direct below
        points.push_back(field[y + 1][x]);

        // add below right
        points.push_back(field[y + 1][x + 1]);

        return points;
    }

}// namespace

// From the point, return an enum representing its
// position on the field
Position::Position Position::getPosition(const Point *point) {
    // store x and y for easier access
    int x{point->getX()};
    int y{point->getY()};

    // based on the x & y, return the position
    // the field is a fixed 9x9 field
    if (x == 0 && y == 0) return TOP_LEFT;
    if (x == 8 && y == 0) return TOP_RIGHT;
    if (x == 0 && y == 8) return BOTTOM_LEFT;
    if (x == 8 && y == 8) return BOTTOM_RIGHT;
    if (y == 0) return TOP;
    if (y == 8) return BOTTOM;
    if (x == 0) return LEFT;
    if (x == 8) return RIGHT;

    // else it's somewhere in the middle
    return MIDDLE;
}

// get the list of adjacent points
std::vector<Point *> Position::getAdjacentPoints(Field field, const Point *point) {
    // get the position of the point
    Position position{getPosition(point)};

    switch (position) {
        // handle corners
        case TOP_LEFT:
        case TOP_RIGHT:
        case BOTTOM_LEFT:
        case BOTTOM_RIGHT:
            return getCornerAdjacentPoints(field, position);

        // handle edges
        case TOP:
        case LEFT:
        case RIGHT:
        case BOTTOM:
            return getEdgeAdjacentPoints(field, position, point);

        // handle middle
        default:
            return getMiddleAdjacentPoints(field, point);
    }
}

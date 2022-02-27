/*
* Tunji Afolabi-Brown
* CIS 554-M401 Object-Oriented Programming in C++ - Syracuse University
* HW #5 - Minesweeper
* MineField.cpp - Function definitions for MineField.h
*/

#include "MineField.h"
#include "Helpers.h"
#include "Position.h"
#include <iostream>
#include <random>


// Constructor for the minefield
// Create the 2D array with all the points
MineField::MineField(int mineCount) : mineCount{mineCount}, mines{std::vector<Point *>{}} {
    // initialize array
    std::array<std::array<Point *, 9>, 9> mineField{};

    // iterate over grid and assign each value in array a point
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            mineField[y][x] = new Point{x, y, "."};
        }
    }

    // assign private member variable
    field = mineField;
}

// stream output override
// print the minefield
std::ostream &operator<<(std::ostream &os, const MineField &field) {
    // print the top two rows
    os << " │ 1 2 3 4 5 6 7 8 9 │\n-│ - - - - - - - - - │\n";

    // Iterate over the rows
    for (int i = 0; i < 9; i++) {

        // add the number and left border for the row
        os << i + 1 << "│";

        // iterate across the row and output the value of the point
        for (auto p: field.field[i]) {
            os << ' ' << p->getVal();
        }

        // output the right border
        os << " │\n";
    }

    // output the footer
    os << "-│ - - - - - - - - - │\n";
    return os;
}

// mark/unmark a mine on the field
void MineField::targetMine(int x, int y) {
    // make sure points are in range
    // this should never be a real issue, but just in case
    if ((x < 0 || x > 8) || (y < 0 || y > 8)) {
        std::cout << "Target point (" << x << ", " << y << ") is out of range\n";
        return;
    }

    // Get point from field
    Point *point{field[y][x]};

    // unmark point if already marked
    if (point->getVal() == "*") {
        point->setVal(".");
    }

    // mark point if not marked
    else if (point->getVal() == ".") {
        point->setVal("*");
    }

    // Don't let user mark a point that has already been explored
    else {
        std::cout << "Cannot mark this point as a mine, it has already been explored!\n";
    }

    // change status of game if this move ended it
    checkPoints();
}

// place mines on the field, can only be run once
void MineField::generateMines() {
    // create random number generator, used as seed
    std::random_device rd;

    // create random number engine, seeded by rd
    std::mt19937 gen(rd());
    // create uniform distribution from 0 to 81
    // 81 because our field is 9x9
    std::uniform_int_distribution<> r{0, 81};

    // keep placing mines until no mines left
    int minesLeft{mineCount};
    while (minesLeft) {
        // use r to transform value produces by gen to a number in range, [0,81]
        const int num{r(gen)};

        // split number into y (floor division) and x (remainder) components
        const int y{num / 9};
        const int x{num % 9};

        // get point from field
        Point *point{field[y][x]};

        // if point isn't in mine list and the val of our point is '.'
        // add it to mine list
        // only add points with val of '.' as first guess of user should not be
        // turned into a mine
        if (!containsPoint(mines, point) && point->getVal() == ".") {
            mines.push_back(point);
            // decrement minesLeft
            minesLeft--;
        }
    }
}

// check if the vector contains the point
bool MineField::containsPoint(const std::vector<Point *> &vec, const Point *point) {
    // use std::find
    // if iterator does not reach the end, it found the value
    return std::find(vec.begin(), vec.end(), point) != vec.end();
}

// if the mines have been generated or not
bool MineField::minesGenerated() {
    return !mines.empty();
}

// explored a point, the game will end if exploration happens on a mine
void MineField::explore(Point *point) {
    // The adjacent points
    std::vector<Point *> adjacentPoints{Position::getAdjacentPoints(field, point)};

    // keep track of explored points
    std::vector<Point *> exploredPoints{};

    // check if there are mines in adjacent points
    int count{numberOfMines(adjacentPoints)};
    if (count != 0) {
        // update proximity count for point
        point->setVal(std::to_string(count));
        // stop exploring
        return;
    }

    // mark val to indicate explored
    point->setVal("/");
    // add point to explored
    exploredPoints.push_back(point);

    // go through all the adjacent points
    while (!adjacentPoints.empty()) {
        // get last element in vector and the remove it
        Point *newPoint{adjacentPoints[adjacentPoints.size() - 1]};
        adjacentPoints.pop_back();

        // if point has already been explored, skip
        if (containsPoint(exploredPoints, newPoint)) continue;

        // add point to explored
        exploredPoints.push_back(newPoint);

        // if point has a mine proximity, a number for its val, skip
        if (Helpers::parseInt(newPoint->getVal()) != -1) continue;

        // get adjacent points for this new point
        std::vector<Point *> tempAdjacent{Position::getAdjacentPoints(field, newPoint)};

        // if adjacent to mines, set proximity and don't add adjacent points to loop vector
        int localCount{numberOfMines(tempAdjacent)};
        if (localCount != 0) {
            // update proximity count for point
            newPoint->setVal(std::to_string(localCount));
        }
        // mark point as explored and add its adjacent points to the vector of points
        // we're iterating over
        else {
            newPoint->setVal("/");
            for (auto p: tempAdjacent) {
                adjacentPoints.push_back(p);
            }
        }
    }
}

// mark a point as free and explore around it
// game will end if free is called on a mine
void MineField::free(int x, int y) {
    // make sure points are in range
    // this should never be a real issue, but just in case
    if ((x < 0 || x > 8) || (y < 0 || y > 8)) {
        std::cout << "Target point (" << x << ", " << y << ") is out of range\n";
        return;
    }

    // get point from field
    Point *point{field[y][x]};

    // don't explore if point is marked as mine or has already been explored
    if (point->getVal() != ".") {
        // print specific message if point is marked a mine
        if (point->getVal() == "*") {
            std::cout << "This spot is marked as a mine!\n";
        } else {
            std::cout << "This point has already been explored!\n";
        }
        return;
    }

    // stepped on mine, end the game
    if (containsPoint(mines, point)) {
        gameStatus = GameStatus::HIT_MINE;
        showMines();
        return;
    }

    // generate mines if they haven't been already
    if (mines.empty()) generateMines();

    // explore around the point
    explore(point);

    // change status of game if this move ended it
    checkPoints();
}

// show the mines on the field
void MineField::showMines() {
    for (auto p: mines) {
        p->setVal("X");
    }
}

// gets the number of mines in the vector
int MineField::numberOfMines(const std::vector<Point *> &vec) {
    // store the count
    int count{0};

    // iterate over the mines and increment the count if
    // point mine is count in vector
    for (const auto p: mines) {
        if (containsPoint(vec, p)) count++;
    }

    return count;
}

// getter for gameStatus
GameStatus MineField::getGameStatus() const {
    return gameStatus;
}

// checks to see if all the mines are marked or
// if all the open points are explored
// updates the gameStatus accordingly
void MineField::checkPoints() {
    // if all mines are marked, set status, show mines, and exit function
    if (minesMarked()) {
        gameStatus = GameStatus::MARKED_ALL;
        return;
    }

    // if all free spots are explored, set status and show mines
    if (allExplored()) {
        gameStatus = GameStatus::EXPLORED_ALL;
        showMines();
    }
}

// helper for checkPoints
// checks to see if all mines are marked correctly
bool MineField::minesMarked() {
    // iterate over field
    for (const auto &row: field) {
        for (const auto p: row) {
            // found point marked as mine, but it's not a mine
            if (p->getVal() == "*" && !containsPoint(mines, p)) return false;

            // current point is a mine, but it's not marked as a mine
            if (p->getVal() != "*" && containsPoint(mines, p)) return false;
        }
    }

    return true;
}

// helper for checkPoints
// checks to see if all free points are explored
bool MineField::allExplored() {
    // iterate over field
    for (const auto &row: field) {
        for (const auto p: row) {
            // point has not been explored, but it's not a mine so return false
            if (p->getVal() == "." && !containsPoint(mines, p)) return false;

            // point is marked as mine, but it's not
            if (p->getVal() == "*" && !containsPoint(mines, p)) return false;
        }
    }

    return true;
}

// clean up pointers
MineField::~MineField() {
    // iterate through field and delete each point
    for (const auto &row: field) {
        for (const auto p: row) {
            delete p;
        }
    }
}

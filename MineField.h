/*
 * Tunji Afolabi-Brown
 * CIS 554-M401 Object-Oriented Programming in C++ - Syracuse University
 * HW #5 - Minesweeper
 * MineField.h - Defines the minefield and the operations that can be taken
*/

#ifndef HW5_MINEFIELD_H
#define HW5_MINEFIELD_H


#include "Point.h"
#include <array>
#include <ostream>
#include <vector>

// an enum to indicate the status of the field
enum class GameStatus {
    EXPLORED_ALL,// explored all free spots
    HIT_MINE,    // stepped on mine
    MARKED_ALL,  // marked all mines
    IN_PROGRESS  // the game isn't over
};

class MineField {
private:
    // Holds the points in the minefield
    std::array<std::array<Point *, 9>, 9> field{};

    // Holds the points that are mines
    std::vector<Point *> mines;

    // How many mines are on the field
    const int mineCount;

    // hold the status of the game
    GameStatus gameStatus{GameStatus::IN_PROGRESS};

    // check if the vector contains the point
    static bool containsPoint(const std::vector<Point *> &vec, const Point *point);

    // explores the field starting from a point
    // this reveals empty spaces and mine proximity information
    void explore(Point *point);

    // shows the mines on the field
    // should only be called when the game is over
    void showMines();

    // gets the number of mines in the vector
    int numberOfMines(const std::vector<Point *> &vec);

    // checks to see if all the mines are marked or
    // if all the open points are explored
    // updates the gameStatus accordingly
    void checkPoints();

    // helper for checkPoints
    // checks to see if all mines are marked correctly
    bool minesMarked();

    // helper for checkPoints
    // checks to see if all free points are explored
    bool allExplored();

public:
    // constructor, only the mine count is determined by the user
    explicit MineField(int mineCount);

    // destructor, clean up pointers
    virtual ~MineField();

    // marks a point on the grid as a mine
    void targetMine(int x, int y);

    // place mines on the field, can only be run once
    void generateMines();

    // if the mines have been generated
    bool minesGenerated();

    // mark a point as free and explore around it
    // game will end if free is called on a mine
    void free(int x, int y);

    // getter for gameStatus
    GameStatus getGameStatus() const;

    // Stream output override
    // prints out the current state of the minefield
    friend std::ostream &operator<<(std::ostream &os, const MineField &field);
};


#endif//HW5_MINEFIELD_H

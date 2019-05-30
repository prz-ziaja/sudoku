#ifndef MAP_SUDOKU_H
#define MAP_SUDOKU_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using myMap = std::vector < std::vector< std::set<size_t> > >;
class board_sudoku
{
public:
    board_sudoku(std::string);
    int counter(); //checks if sudoku has only one solution
    void solve();//sudoku solving method
    void print();//prints actual sudoku
    bool issolved();//checks if sudoku is arleady solved
    void clearRows(size_t x, size_t y); //clears rows' values in map that can't  occur in sudoku
    void clearColumns(size_t x, size_t y); //clears columns' values in map that can't occur in sudoku
    void clearBox(size_t x, size_t y); //clears box's values (9* 3x3 box) in map that can't occur in sudoku
    void onlyOneColumn (bool& flag, bool& goOutOfLoop, size_t x, size_t y, size_t p); //checks if there is only one possible number to be put by the column
    void onlyOneRow(bool& flag, bool& goOutOfLoop, size_t x, size_t y, size_t p); //checks if there is only one possible number in the column
    void onlyOneBox(bool& flag, bool& goOutOfLoop, size_t x, size_t y, size_t p); //checks if there is only one possible number in the column
    void insertElement(bool& goOutOfLoop, size_t y, size_t x, size_t p);
private:
    myMap m_board;
};

#endif // MAP_SUDOKU_H

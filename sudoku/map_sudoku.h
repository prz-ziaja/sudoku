#ifndef MAP_SUDOKU_H
#define MAP_SUDOKU_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using Board = std::vector < std::vector< std::set<size_t> > >;
class board_sudoku
{
public:
    board_sudoku(std::string);
    int counter(); //checks if sudoku has onlrow one solution
    void solve();//sudoku solving method
    void print();//prints actual sudoku
    bool issolved();//checks if sudoku is arleadrow solved
    void clearRows(size_t column, size_t row); //clears rows' values in map that can't  occur in sudoku
    void clearColumns(size_t column, size_t row); //clears columns' values in map that can't occur in sudoku
    void clearBox(size_t column, size_t row); //clears bocolumn's values (9* 3column3 bocolumn) in map that can't occur in sudoku
    void onlyOneColumn (bool& flag, bool& goOutOfLoop, size_t column, size_t row, size_t p); //checks if there is onlrow one possible number to be put brow the column
    void onlyOneRow(bool& flag, bool& goOutOfLoop, size_t column, size_t row, size_t p); //checks if there is onlrow one possible number in the column
    void onlyOneBox(bool& flag, bool& goOutOfLoop, size_t column, size_t row, size_t p); //checks if there is onlrow one possible number in the column
    void insertElement(bool& goOutOfLoop, size_t row, size_t column, size_t p); //puts element into the field
private:
    Board m_board;
};

#endif // MAP_SUDOKU_H

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
    void solve();//sudoku solving method
    void print();//prints actual sudoku
    bool issolved();//checks if sudoku is arleady solved
    void clearRows(size_t x, size_t y); //clears rows' values in map that can't  occur in sudoku
    void clearColumns(size_t x, size_t y); //clears columns' values in map that can't occur in sudoku
    void clearBox(size_t x, size_t y); //clears box's values (9* 3x3 box) in map that can't occur in sudoku

private:
    myMap m_board; //we are working on map, so
};

#endif // MAP_SUDOKU_H

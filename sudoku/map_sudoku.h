#ifndef MAP_SUDOKU_H
#define MAP_SUDOKU_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using myMap = std::vector < std::vector< std::set<unsigned int> > >;
class map_sudoku
{
public:
    map_sudoku(std::string);
    bool send();
    void solve();
    void print();
    bool issolved();
    void clearRows(size_t x, size_t y);
    void clearColumns(size_t x, size_t y);

private:
    myMap m_map;
};

#endif // MAP_SUDOKU_H

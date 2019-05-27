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
private:
    myMap map;
};

#endif // MAP_SUDOKU_H

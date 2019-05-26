#ifndef MAP_SUDOKU_H
#define MAP_SUDOKU_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
class map_sudoku
{
public:
    map_sudoku(std::string);
    bool send();
    bool solve();
    void print();
    bool issolved();
private:
    std::vector < std::vector< std::set<unsigned int> > > map;
};

#endif // MAP_SUDOKU_H

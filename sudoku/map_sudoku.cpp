#include "map_sudoku.h"
#include <regex>

using namespace std;

board_sudoku::board_sudoku(string filename) {
    fstream fileptr;
    fileptr.open(filename, ios::in);
    string line;
    regex pat("^([0-9],)*$"); //file's format
    for (size_t i = 0; i < 9; ++i) {
        getline(fileptr, line);//gets map from sudoku
        if (regex_search(line, pat) == false) {//object destructuion if error occures
            for (auto k:m_board) {
                k.clear();
            }
            fileptr.close();

            m_board.clear();
            throw (string("Zlrow format pliku\n") + filename);
        }

        vector <set<size_t>> &vline = *(new vector <set<size_t>>(9));// getting data from file
        for (size_t i = 0; i < 9; ++i) {//iterating over vec of vec
            if (i * 2 > (line.length() - 1) || line[2 * i] == '0' ||
                line.length() == 0) {//case of non ended line or empty position
                //vline.push_back(*(new set<unsigned int>));
                for (unsigned int j = 1; j < 10; ++j) {
                    vline[i].insert(j);
                }
            } else//case of filled position
            {
                //vline.push_back(*(new set<unsigned int>));
                vline[i].insert(static_cast<unsigned int>(line[i * 2] - 48));
            }
        }
        m_board.push_back(vline);
    }
    fileptr.close();
}

int board_sudoku::counter() {
    int i = 0;
    for (size_t row = 0; row < 9; ++row) {
        for (size_t column = 0; column < 9; ++column) {
            i += m_board[row][column].size();
        }

    }
    return i;
}

bool board_sudoku::issolved() {
    for (size_t row = 0; row < 9; ++row) {
        for (size_t column = 0; column < 9; ++column) {
            if (m_board[row][column].size() != 1) {
                return false;
            }
        }
    }
    return true;
}

void board_sudoku::clearRows(size_t column, size_t row) {
    for (size_t i = 0; i < 9; ++i)
        if (i != row)
            m_board[i][column].erase(*(m_board[row][column].begin()));

}

void board_sudoku::clearColumns(size_t column, size_t row) {
    for (size_t i = 0; i < 9; ++i) {
        if (i != column)
            m_board[row][i].erase(*(m_board[row][column].begin()));
    }
}

void board_sudoku::clearBox(size_t column, size_t row) {
    for (size_t i = (static_cast<size_t>(row / 3)) * 3; i < (static_cast<size_t>(row / 3) + 1) * 3; ++i) {
        for (size_t j = (static_cast<size_t>(column / 3)) * 3; j < (static_cast<size_t>(column / 3) + 1) * 3; ++j) {
            if (i != row && j != column) {
                this->m_board[i][j].erase(*(this->m_board[row][column].begin()));
            }
        }
    }
}

void board_sudoku::onlyOneColumn(bool &flag, bool &goOutOfLoop, size_t column, size_t row, size_t p) {
    flag = true;
    [&](){
        for (size_t i = 0; i < 9; ++i) {
            if (i != column) {
                for (auto j:m_board[row][i]) {
                    if (p == j) {
                        flag = false;
                        return;
                    }
                }
            }
        }
    }();
    if (flag) {
       insertElement(flag, row, column, p);
       goOutOfLoop = true;
    }
}

void board_sudoku::onlyOneRow(bool &flag, bool &goOutOfLoop, size_t column, size_t row, size_t p) {
    flag = true;
    [&](){
        for (size_t i = 0; i < 9; ++i) {
            if (i != row) {
                for (auto j:m_board[i][column]) {
                    if (p == j) {
                        flag = false;
                        return;
                    }
                }
            }
        }
    }();
    if (flag) {
       insertElement(flag, row, column, p);
       goOutOfLoop = true;
    }
}

void board_sudoku::onlyOneBox(bool &flag, bool &goOutOfLoop, size_t column, size_t row, size_t p) {
    flag = true;
    [&](){
        for (size_t i = static_cast<size_t>(row / 3) * 3; i < (static_cast<size_t>(row / 3) + 1) * 3; ++i) {
            for (size_t j = (static_cast<size_t>(column / 3)) * 3; j < (static_cast<size_t>(column / 3) + 1) * 3; ++j)
                if (i != row || j != column) {
                    for (auto l:m_board[i][j]) {
                        if (p == l) {
                            flag = false;
                            return;
                        }
                    }
                }
        }
    }();
    if (flag) {
       insertElement(flag, row, column, p);
       goOutOfLoop = true;
    }
}


void board_sudoku::insertElement(bool &goOutOfLoop, size_t row, size_t column, size_t p) {
    size_t change = p;
    m_board[row][column].erase(m_board[row][column].begin(), m_board[row][column].end());
    m_board[row][column].insert(change);
    goOutOfLoop = true;
}

void board_sudoku::solve() {//coordinates same as in the matrix
    while (!issolved()) {
        int noelem = counter();//number of elements in m_board
        for (size_t row = 0; row < 9; ++row) {
            for (size_t column = 0; column < 9; ++column) {
                if (m_board[row][column].size() == 1) {
                    clearColumns(column, row);
                    clearRows(column, row);
                    clearBox(column,row);
                } else if (m_board[row][column].size() == 0) {
                    delete this;
                    throw (string("Sudoku does not have solution\n"));
                } else {
                    bool flag = true;
                    bool goOutOfLoop = false;
                    for (auto p:m_board[row][column]) {

                        onlyOneRow(flag, goOutOfLoop, column, row, p);
                        if (goOutOfLoop)
                            break;

                        onlyOneColumn(flag, goOutOfLoop, column, row, p);
                        if (goOutOfLoop)
                            break;

                        onlyOneBox(flag, goOutOfLoop, column, row, p);
                        if (goOutOfLoop)
                            break;
                    }
                }
            }
        }
        if (noelem == counter()) {
            delete this;
            throw (string("Sudoku is not a sudoku, more than one solution\n"));
        }
    }

}

void board_sudoku::print() {
    int row_flag = 0;
    int column_flag = 0;
    for (auto column:m_board) {
        row_flag++;
        for (auto row:column) {
            column_flag++;
            for (auto z:row) {
                if (row.size() == 1)
                    cout << ' ' << z << ' ';
                else {
                    cout << "   ";
                    break;
                }
            }
            if (column_flag != 9) cout << '|';
        }
        cout << endl;
        if (row_flag != 9) {
            for (int i = 0; i < 9; i++) {
                cout << "----";
            }
            cout << endl;
        }
        column_flag = 0;
    }
    cout << endl;
}

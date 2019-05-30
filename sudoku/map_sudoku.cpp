#include "map_sudoku.h"
#include <regex>
using namespace std;

board_sudoku::board_sudoku(string filename)
{
    fstream fileptr;
    fileptr.open(filename,ios::in);
    string line;
    regex pat("^([0-9],)*$"); //file's format
    for(size_t i=0;i<9;++i){
        getline(fileptr,line);//gets map from sudoku
            if(regex_search(line,pat)==false){//object destructuion if error occures
                for(auto k:m_board){
                 k.clear();
              }
              fileptr.close();
              m_board.clear();
              throw(string("Zly format pliku\n")+filename);
            }

        vector<set<size_t>> &vline=*(new vector<set< size_t> >(9));// getting data from file
        for(size_t i=0;i<9;++i){//iterating over vec of vec
            if(i*2>(line.length()-1)||line[2*i]=='0'||line.length()==0){//case of non ended line or empty position
                //vline.push_back(*(new set<unsigned int>));
                for(unsigned int j=1;j<10;++j){
                    vline[i].insert(j);}
            }
            else//case of filled position
            {
                //vline.push_back(*(new set<unsigned int>));
                vline[i].insert(static_cast<unsigned int>(line[i*2]-48));
            }
        }
        m_board.push_back(vline);
    }
    fileptr.close();
}

int board_sudoku::counter(){
    int i=0;
    for(size_t y=0;y<9;++y){
        for(size_t x=0;x<9;++x){
            i+=m_board[y][x].size();
        }
    }
    return i;
}

bool board_sudoku::issolved(){
    bool k=true;
    for(size_t y=0;y<9;++y){
        for(size_t x=0;x<9;++x){
            if(m_board[y][x].size()!=1){
                k=false;
                goto fastexit;
            }
        }
    }
    fastexit:
        return k;
}

void board_sudoku::clearRows(size_t x, size_t y){
    for(size_t i=0;i<9;++i)
        if(i!=y)
            m_board[i][x].erase(*(m_board[y][x].begin()));

}

void board_sudoku::clearColumns(size_t x, size_t y){
        for(size_t i=0;i<9;++i){
            if(i!=x)
                m_board[y][i].erase(*(m_board[y][x].begin()));
        }
}

void board_sudoku::onlyOneColumn(bool& flag, bool& goOutOfLoop, size_t x, size_t y, size_t p){
    flag =true;
    for(size_t i=0;i<9;++i){
        if(i!=x){
            for(auto j:m_board[y][i]){
                if(p==j){
                    flag=false;
                    goto fastexitcolumn;
                }
            }
        }
    }
    fastexitcolumn:
    if (flag){
    insertElement(flag,y,x,p);
    goOutOfLoop=true;
    }
}

void board_sudoku::onlyOneRow(bool& flag, bool& goOutOfLoop, size_t x, size_t y, size_t p){
    flag =true;
    for(size_t i=0;i<9;++i){
        if(i!=y){
            for(auto j:m_board[i][y]){
                if(p==j){
                    flag=false;
                    goto fastexitrow;
                }
            }
        }
    }
    fastexitrow:
    if (flag){
    insertElement(flag,y,x,p);
    goOutOfLoop=true;
    }
}

void board_sudoku::clearBox(size_t x, size_t y){
    for(size_t i=(static_cast<size_t>(y/3))*3;i<(static_cast<size_t>(y/3)+1)*3;++i){
       for(size_t j=(static_cast<size_t>(x/3))*3;j<(static_cast<size_t>(x/3)+1)*3;++j){
           if(i!=y&&j!=x){
              this->m_board[i][j].erase(*(this->m_board[y][x].begin()));
           }
       }
   }
}

void board_sudoku::onlyOneBox(bool& flag, bool& goOutOfLoop, size_t x, size_t y, size_t p){
    flag =true;
    for(size_t i=static_cast<size_t>(y/3)*3;i<(static_cast<size_t>(y/3)+1)*3;++i){
        for(size_t j=(static_cast<size_t>(x/3))*3;j<(static_cast<size_t>(x/3)+1)*3;++j)
            if(i!=y||j!=x){
                for(auto l:m_board[i][j]){
                    if(p==l){
                        flag=false;
                        goto fastexitbox;
                    }
                }
            }
    }
    fastexitbox:
    if (flag){
    insertElement(flag,y,x,p);
    goOutOfLoop=true;
    }
}

void board_sudoku::insertElement(bool& goOutOfLoop, size_t y, size_t x, size_t p){
        size_t change=p;
        m_board[y][x].erase(m_board[y][x].begin(),m_board[y][x].end());
        m_board[y][x].insert(change);
        goOutOfLoop = true;
}

void board_sudoku::solve(){//coordinates same as in the matrix
    while(!issolved()){
        int noelem=counter();//number of elements in m_board
        for(size_t y=0;y<9;++y){
            for(size_t x=0;x<9;++x){
                if(m_board[y][x].size()==1){
                clearColumns(x,y);
                clearRows(x,y);
//               clearBox(x,y);
                [this,x,y]() mutable{
                    for(size_t i=(static_cast<size_t>(y/3))*3;i<(static_cast<size_t>(y/3)+1)*3;++i){
                        for(size_t j=(static_cast<size_t>(x/3))*3;j<(static_cast<size_t>(x/3)+1)*3;++j)
                            if(i!=y&&j!=x){
                                this->m_board[i][j].erase(*(this->m_board[y][x].begin()));
                            }
                    }
                }();
                }
                else if(m_board[y][x].size()==0){
                    delete this;
                    throw(string("Sudoku does not have solution\n"));
                }
                else{
                    bool flag=true;
                    bool goOutOfLoop=false;
                    for(auto p:m_board[y][x]){

                        onlyOneRow(flag,goOutOfLoop,x,y,p);
                        if (goOutOfLoop)
                            break;

                        onlyOneColumn(flag,goOutOfLoop,x,y,p);
                        if (goOutOfLoop)
                            break;

                        onlyOneBox(flag,goOutOfLoop,x,y,p);
                        if (goOutOfLoop)
                            break;
                    }
                }
            }
        }
        if(noelem==counter()){
            delete this;
            throw(string("Sudoku is not a sudoku, more than one solution\n"));
        }
    }

}

void board_sudoku::print(){
    int row_flag=0;
    int column_flag=0;
    for(auto x:m_board){
        row_flag++;
        for(auto y:x){
            column_flag++;
            for(auto z:y){
                if (y.size()==1)
                    cout<<' '<<z<<' ';
                else {cout <<"   "; break;}
            }
            if(column_flag!=9) cout<<'|';
        }
        cout<<endl;
        if (row_flag!=9){
            for (int i =0; i<9;i++){
                cout<<"----";
            }
            cout<<endl;
        }
        column_flag=0;
    }
    cout<<endl;
}

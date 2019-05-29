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
        [this,line,pat,filename]() mutable{
            if(regex_search(line,pat)==false){//object destructuion if error occures
                for(auto k:m_board){
                 k.clear();
              }
              m_board.clear();
              throw(string("Zly format pliku\n")+filename);
            }
        }();
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
void board_sudoku::clearBox(size_t x, size_t y){
    for(size_t i=(static_cast<size_t>(y/3))*3;i<(static_cast<size_t>(y/3)+1)*3;++i){
       for(size_t j=(static_cast<size_t>(x/3))*3;j<(static_cast<size_t>(x/3)+1)*3;++j){
           if(i!=y&&j!=x){
              this->m_board[i][j].erase(*(this->m_board[y][x].begin()));
           }
       }
   }
}
void board_sudoku::solve(){//coordinates same as in the matrix
    while(!issolved()){
        for(size_t y=0;y<9;++y){
            for(size_t x=0;x<9;++x){
                if(m_board[y][x].size()==1){
                clearColumns(x,y);
                clearRows(x,y);
                clearBox(x,y);
//                [this,x,y]() mutable{
//                    for(size_t i=(static_cast<size_t>(y/3))*3;i<(static_cast<size_t>(y/3)+1)*3;++i){
//                        for(size_t j=(static_cast<size_t>(x/3))*3;j<(static_cast<size_t>(x/3)+1)*3;++j)
//                            if(i!=y&&j!=x){
//                                this->m_board[i][j].erase(*(this->m_board[y][x].begin()));
//                            }
//                    }
//                }();
                }
                else if(m_board[y][x].size()==0)
                    throw(string("Blad mapy sudoku, upewnij sie ze sudoku jest rozwiazywalne\nPole na mapie nie to ze jest puste co w ogole nie ma tam wartosci\n"));
                else{
                    bool flag=true;
                    for(auto p:m_board[y][x]){
                        for(size_t i=0;i<9;++i){
                            if(i!=y){
                                for(auto j:m_board[i][x]){
                                    if (p==j)
                                            flag = false;

                                }
                            }
                        }
                        if(flag){
                            size_t zmiana=p;
                            m_board[y][x].erase(m_board[y][x].begin(),m_board[y][x].end());
                            m_board[y][x].insert(zmiana);
                            break;
                        }
                        flag =true;
                        for(size_t i=0;i<9;++i){
                            if(i!=x){
                                for(auto j:m_board[y][i]){
                                    if(p==j)
                                        flag=false;
                                }
                            }
                        }
                        if(flag){
                            size_t zmiana=p;
                            m_board[y][x].erase(m_board[y][x].begin(),m_board[y][x].end());
                            m_board[y][x].insert(zmiana);
                            break;
                        }
                        flag =true; //sprawdzam czy w kwadracie są pozycje na ktorych na pewno musi byc dana liczba bo w zadnym innym miejscu nie pasuje
                        for(size_t i=static_cast<size_t>(y/3)*3;i<(static_cast<size_t>(y/3)+1)*3;++i){
                            for(size_t j=(static_cast<size_t>(x/3))*3;j<(static_cast<size_t>(x/3)+1)*3;++j)
                                if(i!=y||j!=x){
                                    for(auto l:m_board[i][j]){
                                        if(p==l)
                                            flag=false;
                                    }
                                }
                        }
                        if(flag){
                            size_t zmiana=p;
                            m_board[y][x].erase(m_board[y][x].begin(),m_board[y][x].end());
                            m_board[y][x].insert(zmiana);
                            break;
                        }
                    }
                }
            }
        }
    }

}
void board_sudoku::print(){
    for(auto x:m_board){
        for(auto y:x){
            for(auto z:y)
                if (y.size()==1)
                    cout<<z<<' ';
                else {cout <<'  '; break;}
        cout<<'|';
        }

        cout<<endl;
    }
}

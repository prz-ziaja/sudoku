#include "map_sudoku.h"
#include <regex>

using namespace std;
map_sudoku::map_sudoku(string filename)
{
    fstream fileptr;
    fileptr.open(filename,ios::in);
    string line;
    regex pat("^([0-9],)*$"); //file's format
    for(size_t i=0;i<9;++i){
        getline(fileptr,line);//gets map from sudoku
        if(regex_search(line,pat)==false){//object destructuion if error occures
            for(auto k:m_map){
                k.clear();
            }
            m_map.clear();
            throw(string("Zly format pliku\n")+filename);
        }
        vector<set<unsigned int>> &vline=*(new vector<set< unsigned int> >(9));// getting data from file
        for(size_t j=0;j<9;++j){//iterating over vec of vec
            if(j*2>(line.length()-1)||line[2*j]=='0'||line.length()==0){//case of non ended line or empty position
                //vline.push_back(*(new set<unsigned int>));
                for(unsigned int jj=1;jj<10;++jj){
                    vline[j].insert(jj);}
            }
            else//case of filled position
            {
                //vline.push_back(*(new set<unsigned int>));
                vline[j].insert(static_cast<unsigned int>(line[j*2]-48));
            }
        }
        m_map.push_back(vline);
    }
}
bool map_sudoku::issolved(){
    bool k=true;
    for(size_t y=0;y<9;++y){
        for(size_t x=0;x<9;++x){
            if(m_map[y][x].size()!=1){
                k=false;
                goto fastexit;
            }
        }
    }
    fastexit:
        return k;
}
void map_sudoku::clearRows(size_t x, size_t y){
    for(size_t i=0;i<9;++i)
        if(i!=y)
            m_map[i][x].erase(*(m_map[y][x].begin()));

}
void map_sudoku::clearColumns(size_t x, size_t y){
        for(size_t i=0;i<9;++i){
            if(i!=x)
                m_map[y][i].erase(*(m_map[y][x].begin()));
        }
}
void map_sudoku::clearBox(size_t x, size_t y){
    for(size_t i=(static_cast<size_t>(y/3))*3;i<(static_cast<size_t>(y/3)+1)*3;++i){
       for(size_t j=(static_cast<size_t>(x/3))*3;j<(static_cast<size_t>(x/3)+1)*3;++j){
           if(i!=y&&j!=x){
              this->m_map[i][j].erase(*(this->m_map[y][x].begin()));
           }
       }
   }
}
void map_sudoku::solve(){//coordinates same as in the matrix
    while(!issolved()){
        for(size_t y=0;y<9;++y){
            for(size_t x=0;x<9;++x){
                if(m_map[y][x].size()==1){
                clearColumns(x,y);
                clearRows(x,y);
                clearBox(x,y);
//                [this,x,y]() mutable{
//                    for(size_t i=(static_cast<size_t>(y/3))*3;i<(static_cast<size_t>(y/3)+1)*3;++i){
//                        for(size_t j=(static_cast<size_t>(x/3))*3;j<(static_cast<size_t>(x/3)+1)*3;++j)
//                            if(i!=y&&j!=x){
//                                this->m_map[i][j].erase(*(this->m_map[y][x].begin()));
//                            }
//                    }
//                }();
                }
                else if(m_map[y][x].size()==0)
                    throw(string("Blad mapy sudoku, upewnij sie ze sudoku jest rozwiazywalne\nPole na mapie nie to ze jest puste co w ogole nie ma tam wartosci\n"));
                else{
                    bool flag=true;
                    for(auto p:m_map[y][x]){
                        for(size_t i=0;i<9;++i){
                            if(i!=y){
                                for(auto j:m_map[i][x]){
                                    if (p==j)
                                            flag = false;

                                }
                            }
                        }
                        if(flag){
                            unsigned int zmiana=p;
                            m_map[y][x].erase(m_map[y][x].begin(),m_map[y][x].end());
                            m_map[y][x].insert(zmiana);
                            break;
                        }
                        flag =true;
                        for(size_t i=0;i<9;++i){
                            if(i!=x){
                                for(auto j:m_map[y][i]){
                                    if(p==j)
                                        flag=false;
                                }
                            }
                        }
                        if(flag){
                            unsigned int zmiana=p;
                            m_map[y][x].erase(m_map[y][x].begin(),m_map[y][x].end());
                            m_map[y][x].insert(zmiana);
                            break;
                        }
                        flag =true; //sprawdzam czy w kwadracie są pozycje na ktorych na pewno musi byc dana liczba bo w zadnym innym miejscu nie pasuje
                        for(size_t i=static_cast<size_t>(y/3)*3;i<(static_cast<size_t>(y/3)+1)*3;++i){
                            for(size_t j=(static_cast<size_t>(x/3))*3;j<(static_cast<size_t>(x/3)+1)*3;++j)
                                if(i!=y||j!=x){
                                    for(auto l:m_map[i][j]){
                                        if(p==l)
                                            flag=false;
                                    }
                                }
                        }
                        if(flag){
                            unsigned int zmiana=p;
                            m_map[y][x].erase(m_map[y][x].begin(),m_map[y][x].end());
                            m_map[y][x].insert(zmiana);
                            break;
                        }
                    }
                }
            }
        }
    }

}
void map_sudoku::print(){
    for(auto x:m_map){
        for(auto y:x){
            for(auto z:y)
                cout<<z<<' ';
        cout<<'|';
        }
        cout<<endl;
    }
}

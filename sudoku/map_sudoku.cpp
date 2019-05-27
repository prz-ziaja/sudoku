#include "map_sudoku.h"
#include <regex>

using namespace std;
map_sudoku::map_sudoku(string filename)
{
    fstream fileptr;
    fileptr.open(filename,ios::in);
    string line;
    regex pat("^([0-9],)*$"); //format pliku
    for(size_t i=0;i<9;++i){
        getline(fileptr,line);//wczytywanie mapy z sudoku
        if(regex_search(line,pat)==false){//destrukcja obiekty przy bledzie
            for(auto k:map){
                k.clear();
            }
            map.clear();
            throw(string("Zly format pliku\n")+filename);
        }
        vector<set<unsigned int>> &vline=*(new vector<set< unsigned int> >(9));// wczytywanie danych z pliku
        for(size_t j=0;j<9;++j){//numeracja po tablicy tzn vec(vec)
            if(j*2>(line.length()-1)||line[2*j]=='0'||line.length()==0){//przypadek niedokonczona linia lub pusta pozycja
                //vline.push_back(*(new set<unsigned int>));
                for(unsigned int jj=1;jj<10;++jj){
                    vline[j].insert(jj);}
            }
            else//przypadek zapelniona pozycja
            {
                //vline.push_back(*(new set<unsigned int>));
                vline[j].insert(static_cast<unsigned int>(line[j*2]-48));
            }
        }
        map.push_back(vline);
    }
}
bool map_sudoku::issolved(){
    bool k=true;
    for(size_t y=0;y<9;++y){
        for(size_t x=0;x<9;++x){
            if(map[y][x].size()!=1){
                k=false;
                goto fastexit;
            }
        }
    }
    fastexit:
        return k;
}
void map_sudoku::solve(){//wspolrzedne tak samo jak w macierzy
    while(!issolved()){
        for(size_t y=0;y<9;++y){
            for(size_t x=0;x<9;++x){
                if(map[y][x].size()==1){
                    for(size_t i=0;i<9;++i)//usuwanie wartosci w kolumnach i wierszach

                        if(i!=x)
                            map[y][i].erase(*(map[y][x].begin()));
                    for(size_t i=0;i<9;++i)
                        if(i!=y)
                            map[i][x].erase(*(map[y][x].begin()));
                    //usuwanie w kwadracie
                    {
                        for(size_t i=(static_cast<size_t>(y/3))*3;i<(static_cast<size_t>(y/3)+1)*3;++i){
                            for(size_t j=(static_cast<size_t>(x/3))*3;j<(static_cast<size_t>(x/3)+1)*3;++j)
                                if(i!=y&&j!=x){
                                    map[i][j].erase(*(map[y][x].begin()));
                                }
                        }
                    }
                }
                else if(map[y][x].size()==0)
                    throw(string("Blad mapy sudoku, upewnij sie ze sudoku jest rozwiazywalne\nPole na mapie nie to ze jest puste co w ogole nie ma tam wartosci\n"));
                else{
                    bool flag=true;
                    for(auto p:map[y][x]){
                        for(size_t i=0;i<9;++i){
                            if(i!=y){
                                for(auto j:map[i][x]){
                                    if (p==j)
                                            flag = false;

                                }
                            }
                        }
                        if(flag){
                            unsigned int zmiana=p;
                            map[y][x].erase(map[y][x].begin(),map[y][x].end());
                            map[y][x].insert(zmiana);
                            break;
                        }
                        flag =true;
                        for(size_t i=0;i<9;++i){
                            if(i!=x){
                                for(auto j:map[y][i]){
                                    if(p==j)
                                        flag=false;
                                }
                            }
                        }
                        if(flag){
                            unsigned int zmiana=p;
                            map[y][x].erase(map[y][x].begin(),map[y][x].end());
                            map[y][x].insert(zmiana);
                            break;
                        }
                        /*flag =true;
                        for(int i=((int)y/3)*3;i<((int)(y/3)+1)*3;++i){
                            for(int j=((int)x/3)*3;j<((int)(x/3)+1)*3;++j)
                                if(i!=y&&j!=x){
                                    for(auto l:map[i][j]){
                                        if(p==l)
                                            flag=false;
                                    }
                                }
                        }
                        if(flag){
                            unsigned int zmiana=p;
                            map[y][x].erase(map[y][x].begin(),map[y][x].end());
                            map[y][x].insert(zmiana);
                            break;
                        }*/
                    }
                }
            }
        }
    }

}
void map_sudoku::print(){
    for(auto x:map){
        for(auto y:x){
            for(auto z:y)
                cout<<z<<' ';
        cout<<'|';
        }
        cout<<endl;
    }
}

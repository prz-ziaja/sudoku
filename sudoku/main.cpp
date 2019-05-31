#include <iostream>
#include <map_sudoku.h>
#include <cstdlib>
#include <experimental/filesystem>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
namespace fs=std::experimental::filesystem;

vector <string> &getsudoku(string namefile);

int main() {
    string namefile;
    //cout<<"Podaj nazwe plikow do wyszukiwania w podfolderach:"<<endl;

    getline(cin, namefile);      //z linii wczytuje po jakiej nazwie szukac plikow z nierozwiazanymi sudoku
    if (namefile.size() == 0)
        namefile = "nierozwiazane-sudoku";
    vector <string> &filelist = getsudoku(namefile);//wektor sciezek do plikow z sudoku
    for (auto i:filelist) {
        //cout<<i<<endl;
        try {
            board_sudoku &a = *(new board_sudoku(i));
            a.print();
            cout << endl;
            a.solve();
            a.print();
            cout << endl;
            delete &a;
        }
        catch (string blad) {
            cout << blad << endl;
            continue;
        }
        //a.send();
    }
}

vector <string> &getsudoku(string namefile) {
#ifdef _WIN32
    char slash='\\';
#else
    char slash = '/';
#endif
    string dirtofile;
    vector <string> &pliki = *(new vector <string>);
    for (auto &p:fs::directory_iterator(fs::current_path())) {
        if (fs::is_directory(p)) {
            dirtofile = (p.path()).u8string() + slash + namefile;
            //cout<<dirtofile<<endl;
            if (fs::exists(dirtofile)) {
                pliki.push_back(dirtofile);

            }
        } else
            continue;
    }
    return pliki;
}


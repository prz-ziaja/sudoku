#include "getsudoku_filesystem.h"
#include "map_sudoku.h"

int main() {
    string namefile;
    //cout<<"Podaj nazwe plikow do wyszukiwania w podfolderach:"<<endl;
    getline(cin, namefile);      //z linii wczytuje po jakiej nazwie szukac plikow z nierozwiazanymi sudoku
    if (namefile.size() == 0)
        namefile = "nierozwiazane-sudoku";
    vector <string> &filelist = getSudoku(namefile);//wektor sciezek do plikow z sudoku
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
    delete &filelist;
}




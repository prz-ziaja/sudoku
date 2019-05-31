#include "getsudoku_filesystem.h"

namespace fs=std::experimental::filesystem;

vector <string> &getSudoku(string namefile) {
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
            if (fs::exists(dirtofile)) {
                pliki.push_back(dirtofile);

            }
        } else
            continue;
    }
    return pliki;
}

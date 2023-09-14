#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include <map>
#include "src/Sudoku.h"

using boost::filesystem::directory_iterator;
using boost::filesystem::is_directory;
using boost::filesystem::extension;
using namespace std;

int main() {
    string path = "assignments";
    directory_iterator d_i(path);
    map<string, string> files;
    while(d_i != directory_iterator{}){
        if(is_directory(*d_i)){
            continue;
        }
        else if(extension(*d_i) == ".txt"){
            try {
                Sudoku test(d_i->path().string());
                files.insert({
                    d_i->path().filename().string(),
                    d_i->path().string()
                });
            }
            catch(logic_error& invalid_sudoku){}
        }
        d_i++;
    }
    cout << "The following files were found:" << endl;
    for(auto &file: files){
        cout << "    " << file.first << endl;
    }
    cout << endl << "Select one to solve: ";
    string input;
    cin >> input;
    while(files.find(input) == files.end()){
        cout << "Invalid input \"" << input << "\", please input one of the files listed above." << endl;
        cout << "Select one to solve: ";
        cin >> input;
    }
    Sudoku s(files[input]);
    s.autoSolve();
    cout << s;
}
//
// Created by axelmans on 11/09/23.
//

#ifndef SUDOKUSOLVER_SUDOKU_H
#define SUDOKUSOLVER_SUDOKU_H

#include <string>
#include <array>
#include <set>
#include <ostream>

using namespace std;

class Sudoku {

public:

    explicit Sudoku(const string&);

    static bool validateFile(const string&);

    bool invalid();

    set<int> possible(const int&, const int&);

    void autoSolve();

    friend ostream& operator<<(ostream&, Sudoku&);

private:

    // Use 0's to indicate empty spaces
    array<array<int, 9>, 9> grid{0};

};


#endif //SUDOKUSOLVER_SUDOKU_H

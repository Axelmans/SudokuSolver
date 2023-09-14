//
// Created by axelmans on 11/09/23.
//

#include "Sudoku.h"
#include <algorithm>
#include <fstream>

Sudoku::Sudoku(const string &filename) {
    try {
        // Only allow construction from valid files.
        if (!validateFile(filename)) {
            throw logic_error("Invalid file!");
        }
        // Construct.
        ifstream input(filename);
        string line;
        int r = 0;
        int c = 0;
        while (getline(input, line)) {
            for (char &number: line) {
                // Ignore spaces.
                if (number == ' ') {
                    continue;
                }
                // X = Empty Spot; Use 0 as placeholder.
                else if (tolower(number) == 'x') {
                    grid[r][c] = 0;
                }
                else {
                    grid[r][c] = stoi(string(1, number));
                }
                c += 1;
            }
            c = 0;
            r += 1;
        }
        // Sudoku should be valid.
        if (invalid()) {
            throw logic_error("Invalid Sudoku!");
        }
    }
    // Catch any exceptions that might cause construction to fail.
    catch(logic_error& invalid){
        throw invalid;
    }
}

bool Sudoku::validateFile(const string &filename) {
    ifstream input(filename);
    string line;
    int lines = 0;
    while(getline(input, line)){
        // Line should at least have 9 characters (digits/X).
        if(line.size() < 9 || lines >= 9){
            return false;
        }
        // Ignore empty lines
        if(line.empty()){
            continue;
        }
        int digits_on_line = 0;
        for(char& number: line){
            // Spaces are ignored.
            if(number == ' '){
                continue;
            }
            // Invalid characters/More than 9 digits = Not Allowed.
            if((tolower(number) != 'x' && !isdigit(number)) || digits_on_line == 9){
                return false;
            }
            digits_on_line++;
        }
        if(digits_on_line != 9){
            return false;
        }
        lines++;
    }
    return true;
}

/*
 * This function checks if the Sudoku is valid.
 * Valid means no duplicates in any row, column or box.
 */
bool Sudoku::invalid() {
    // Check rows.
    for(int r = 0; r < 9; r++){
        array<int, 9> row = grid[r];
        sort(row.begin(), row.end());
        for(int r_i = 0; r_i < 8; r_i++){
            if(row[r_i] == row[r_i+1] && row[r_i] != 0){
                return true;
            }
        }
    }
    // Check columns.
    for(int c = 0; c < 9; c++){
        array<int, 9> column{};
        for(int c_i = 0; c_i < 9; c_i++){
            column[c_i] = grid[c_i][c];
        }
        sort(column.begin(), column.end());
        for(int c_i = 0; c_i < 8; c_i++){
            if(column[c_i] == column[c_i+1] && column[c_i] != 0){
                return true;
            }
        }
    }
    // Check boxes.
    for(int b_r = 0; b_r < 3; b_r++){
        for(int b_c = 0; b_c < 3; b_c++){
            array<int, 9> box{
                grid[3*b_r][3*b_c],
                grid[3*b_r][3*b_c+1],
                grid[3*b_r][3*b_c+2],
                grid[3*b_r+1][3*b_c],
                grid[3*b_r+1][3*b_c+1],
                grid[3*b_r+1][3*b_c+2],
                grid[3*b_r+2][3*b_c],
                grid[3*b_r+2][3*b_c+1],
                grid[3*b_r+2][3*b_c+2]
            };
            sort(box.begin(), box.end());
            for(int b_i = 0; b_i < 8; b_i++){
                if(box[b_i] == box[b_i+1] && box[b_i] != 0){
                    return true;
                }
            }
        }
    }
    return false;
}

/*
 * Check which numbers can be filled in on an empty spot on row r and column c.
 */
set<int> Sudoku::possible(const int &r, const int &c) {
    set<int> possible_digits{};
    // It's easier to check which numbers are not possible first.
    set<int> impossible_digits{};
    // Check rows and columns.
    for(int i = 0; i < 9; i++){
        impossible_digits.insert(grid[r][i]);
        impossible_digits.insert(grid[i][c]);
    }
    // Check the box in which the spot is located.
    for(int b_r = r/3*3; b_r < r/3*3+3; b_r++){
        for(int b_c = c/3*3; b_c < c/3*3+3; b_c++){
            impossible_digits.insert(grid[b_r][b_c]);
        }
    }
    // Finally, add all numbers that weren't found previously (ignore 0).
    for(int i = 1; i <= 9; i++){
        if(impossible_digits.find(i) == impossible_digits.end()){
            possible_digits.insert(i);
        }
    }
    return possible_digits;
}

/*
 * General idea:
 * 1. Iterate over all spots on the grid.
 * 2. If a spot is empty, call possible(r, c)
 * 3. If the resulting set only contains one number, fill that number in.
 * 4. Repeat steps 1-3 as long as  at least one number got filled in somewhere.
 *
 * Disclaimer: Some assignments might be left slightly unsolved.
 */
void Sudoku::autoSolve() {
    bool progress = true;
    while(progress){
        progress = false;
        for(int r = 0; r < 9; r++){
            for(int c = 0; c < 9; c++){
                if(grid[r][c] == 0) {
                    set<int> possibilities = possible(r, c);
                    if (possibilities.size() == 1) {
                        grid[r][c] = *possibilities.begin();
                        progress = true;
                    }
                }
            }
        }
    }
}

/*
 * This overload allows for easy printing to console.
 */
ostream &operator<<(ostream &o, Sudoku &s) {
    o << string(25, '-') << endl;
    for(int r = 0; r < 9; r++){
        o << "| ";
        for(int c = 0; c < 9; c++){
            if(s.grid[r][c] == 0){
                o << 'X';
            }
            else {
                o << s.grid[r][c];
            }
            if(c%3 == 2){
                o << " |";
            }
            o << ' ';
        }
        o << endl;
        if(r%3 == 2){
            o << string(25, '-') << endl;
        }
    }
    return o;
}

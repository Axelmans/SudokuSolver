# Sudoku Solver 
## General
This program solves any sudoku given by the user.

Sudoku assignments can be provided by valid txt files, syntax will be explained in the usage guide.
## Installation + Setup + Run Guide
Step 1: Download or clone the repository.

Step 2: Run the "run.sh" file

Step 3: There should now be a folder named "build". Go inside it and open it in Terminal/Powershell.

Step 4: In this window, execute: ```./SudokuSolver```

## Usage Guide
The program will look in the "assignments" folder for valid txt files containing sudoku information.

It will print out a list of found valid files, requesting the user to choose one of them.

If the user gives in a valid filename, the file will be read and the sudoku will be solved and printed to console.

A valid file is a simple txt file with 9 lines.
Each line should contain 9 characters, either a digit from 1-9, or an 'X' to indicate an empty spot.
Here's an example of a valid file:

```
6 3 X X X X 5 X 8
X 5 9 X 6 7 X X 4
X X X 4 X 8 6 X X
X X X 7 2 X 3 6 X
2 X 5 9 X 4 X X X
3 X 7 X X 1 X 4 5
X 7 3 5 1 X 9 X 2
X 8 X X X X X 5 X
5 X X X 7 9 X 3 1
```

For convenience, empty lines and spaces are ignored. In addition, 'X' is not case-sensitive.

However, the program will also check if the input sudoku is valid.
Should an input file contain any invalid duplicates, it'll still be deemed invalid.
Make sure to check on this beforehand.

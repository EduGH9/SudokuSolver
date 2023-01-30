#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <cctype>
using namespace std;

vector<vector<int>> secureNumbers;

vector<vector<int>> readData(); //Creates the sudoku with inputs
void showSudoku(vector<vector<int>> sudoku); //Prints the sudoku
void setSecureNumbers(vector<vector<int>> sudoku); //Set the fixed numbers that are on the sudoku
bool check(vector<vector<int>> sudoku, int row, int col, int val); //Checks if [row][col] = val is possible
bool writeSudoku(vector<vector<int>>& sudoku, int row, int col); //Set numbers until it gets a true value

int main()
{
    vector<vector<int>> originalSudoku = readData(); //It builds the sudoku
    cout << "\nOriginal:\n";
    setSecureNumbers(originalSudoku); //Sets the numbers of the original sudoku which cannot be replaced
    showSudoku(originalSudoku); //Prints the original sudoku
    cout << "\n\nSolution:\n";

    bool a = writeSudoku(originalSudoku, 0, 0);
    showSudoku(originalSudoku); //Prints the original sudoku

    return 0;
}


vector<vector<int>> readData() {
    vector<int> r;
    vector<vector<int>> res;
    int a, n = 9;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a;
            r.push_back(a);
        }
        res.push_back(r);
        r.clear();
    }
    return res;
}

void showSudoku(vector<vector<int>> sudoku) {
    int n = 9;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << sudoku[i][j] << ' ';
        }
        cout << '\n';
    }
}

void setSecureNumbers(vector<vector<int>> sudoku) {
    int n = 9;
    vector<int> aux;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (sudoku[i][j] != 0) {
                aux.push_back(i);
                aux.push_back(j);
                secureNumbers.push_back(aux);
                aux.clear();
            }
        }
    }
}

bool check(vector<vector<int>> sudoku, int row, int col, int val) {
    bool res = true;
    int r, c, q;

    for (int i = 0; i < 9; i++) { //Same col?
        if (i != row && sudoku[i][col] == val) {
            res = false;
            break;
        }
    }
    if (res) { //Same row?
        for (int i = 0; i < 9; i++) {
            if (i != col && sudoku[row][i] == val) {
                res = false;
                break;
            }
        }
    }
    if (res) {//Same square?
        r = row / 3;
        c = col / 3;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (sudoku[i + r * 3][j + c * 3] == val) {
                    return false;
                    break;
                }
            }
        }

    }

    return res;
}

bool writeSudoku(vector<vector<int>>& sudoku, int row, int col) {
    if (row == 9) return true;
    if (sudoku[row][col] == 0) {
        for (int i = 1; i <= 9; i++) {
            if (check(sudoku, row, col, i)) {
                sudoku[row][col] = i;
                if (col != 8) {
                    if (writeSudoku(sudoku, row, col + 1)) return true;
                }
                else {
                    if (writeSudoku(sudoku, row + 1, 0)) return true;
                }
                sudoku[row][col] = 0;
            }
        }
    }
    else {
        if (col != 8) return writeSudoku(sudoku, row, col + 1);
        else return writeSudoku(sudoku, row + 1, 0);
    }

    return false;
}

/*
0 0 0 0 0 0 0 0 0 0 0 8 0 0 0 0 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 6 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0

          [X][0] [X][1] [X][2] [X][3] [X][4] [X][5] [X][6] [X][7] [X][8]
    [0][X]  0      0      0      0      0      0      0      0      0
    [1][X]  0      0      8      0      0      0      0      4      0
    [2][X]  0      0      0      0      0      0      0      0      0
    [3][X]  0      0      0      0      0      6      0      0      0
    [4][X]  0      0      0      0      0      0      0      0      0
    [5][X]  0      0      0      0      0      0      0      0      0
    [6][X]  2      0      0      0      0      0      0      0      0
    [7][X]  0      0      0      0      0      0      2      0      0
    [8][X]  0      0      0      0      0      0      0      0      0

    [1][2] = 8

*/
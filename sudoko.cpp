#include <iostream>
#include <vector>

using namespace std;

class Sudoku {
private:
    int grid[9][9]; // The Sudoku grid

public:
    Sudoku(const vector<vector<int>>& initialGrid) {
        // Initialize the Sudoku grid from the provided initial state
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                grid[i][j] = initialGrid[i][j];
            }
        }
    }

    // Function to solve the Sudoku puzzle
    bool solveSudoku() {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (grid[row][col] == 0) { // Find an empty cell
                    for (int num = 1; num <= 9; num++) {
                        if (isSafe(row, col, num)) {
                            grid[row][col] = num; // Attempt to place the number

                            if (solveSudoku()) { // Recursively try to fill the rest
                                return true;
                            } else {
                                grid[row][col] = 0; // Backtrack if it doesn't lead to a solution
                            }
                        }
                    }
                    return false; // No valid number can be placed here, trigger backtracking
                }
            }
        }
        return true; // All cells filled, puzzle solved
    }

    // Function to check if placing 'num' at (row, col) is safe
    bool isSafe(int row, int col, int num) {
        // Check row
        for (int x = 0; x < 9; x++) {
            if (grid[row][x] == num) {
                return false;
            }
        }

        // Check column
        for (int x = 0; x < 9; x++) {
            if (grid[x][col] == num) {
                return false;
            }
        }

        // Check 3x3 box
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i + startRow][j + startCol] == num) {
                    return false;
                }
            }
        }

        return true; // No conflicts, placement is safe
    }

    // Function to print the Sudoku grid
    void printGrid() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    // Example Sudoku puzzle (0 represents empty cells)
    vector<vector<int>> grid = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    Sudoku sudoku(grid);

    if (sudoku.solveSudoku()) {
        cout << "Solved Sudoku:" << endl;
        sudoku.printGrid();
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;



}


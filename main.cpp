#include <fstream>
#include <iostream>
#include <bits/stdc++.h> 

using namespace std;

// UNASSIGNED is for 0 in sudoku
#define UNASSIGNED 0  

// Find UNASSIGNED position in sudoku
bool FindUnassignedLocation(int sudoku[9][9], int &row, int &col);
// Check if I can put new number in the grid of sudoku  
bool isSafe(int sudoku[9][9], int row, int col, int num);  

// Main recursice function, random assign numbers and try to find solution
bool SolveSudoku(int sudoku[9][9])  
{  
    int row, col;  
  
    if (!FindUnassignedLocation(sudoku, row, col))  
    return true; 
  
    for (int num = 1; num <= 9; num++)  
    {  
        if (isSafe(sudoku, row, col, num))  
        {  
            sudoku[row][col] = num;  
  
            if (SolveSudoku(sudoku))  
                return true;  

            sudoku[row][col] = UNASSIGNED;  
        }  
    }  
    return false;
}

void vypis(int sudoku[9][9]){
    for(int i = 0; i < 9; i++){
            for(int j = 0; j< 9; j++)
            {
             cout << sudoku[i][j] << " ";
            }
        cout << endl;
        }
}

bool FindUnassignedLocation(int sudoku[9][9], int &row, int &col)  
{  
    for (row = 0; row < 9; row++)  
        for (col = 0; col < 9; col++)  
            if (sudoku[row][col] == UNASSIGNED)  
                return true;  
    return false;  
}  
  

bool UsedInRow(int sudoku[9][9], int row, int num)  
{  
    for (int col = 0; col < 9; col++)  
        if (sudoku[row][col] == num)  
            return true;  
    return false;  
}  
  
bool UsedInCol(int sudoku[9][9], int col, int num)  
{  
    for (int row = 0; row < 9; row++)  
        if (sudoku[row][col] == num)  
            return true;  
    return false;  
}  
  
bool UsedInBox(int sudoku[9][9], int boxStartRow, int boxStartCol, int num)  
{  
    for (int row = 0; row < 3; row++)  
        for (int col = 0; col < 3; col++)  
            if (sudoku[row + boxStartRow][col + boxStartCol] == num)  
                return true;  
    return false;  
}  

bool isSafe(int sudoku[9][9], int row, int col, int num)  
{  
    /* Check if 'num' is not already placed in  
    current row, current column and current 3x3 box */
    return !UsedInRow(sudoku, row, num) &&  
           !UsedInCol(sudoku, col, num) &&  
           !UsedInBox(sudoku, row - row % 3 ,  
                      col - col % 3, num) &&  
            sudoku[row][col] == UNASSIGNED;  
}  



int main(){
    int sudoku[9][9];
    ifstream file("sudoku.txt");
    if(file.is_open())
    {
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j< 9; j++)
            {
             file >> sudoku[i][j];
            }
        }
    }

    vypis(sudoku);
    cout << endl;

    if (SolveSudoku(sudoku) == true)  
        vypis(sudoku); 
    else
        cout << "No solution exists";  
    
}
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;

// output sudoku board
void print_sudoku(vector<vector<int>>&board){
    cout << '\n';
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout << board[i][j];
            if(j==8)continue;
            if((j+1)%3 == 0)cout << "  ||  ";
            else{cout << " | ";}
        }
        if(i==8)continue;
        if((i+1)%3 != 0)cout << "\n---------------------------------------\n";
        else{cout << "\n\n---------------------------------------\n---------------------------------------\n\n";}
    }
    cout << '\n';
}


// Determine wheter current sudoku board is valid or not
bool isValidState(vector<vector<int>>board, int i, int j, int num){
    
    // check for similar number in column and row	
    for(int k = 0;k<9;k++){
        if(board[i][k]==num||board[k][j]==num)return false;
    }

    // check for similar number in a group
    int y = i/3 * 3, x = j/3 * 3;
    for(int p = y;p<y+3;p++){
        for(int q = x;q<x+3;q++){
            if(board[p][q]==num){
                return false;
            }
        }
    }
    return true;
    
}


// Solve using backtracking algorithm
bool solveSudokuRecursive(vector<vector<int>>board, vector<vector<int>> &ans, bool verbose){ 
	
    // if verbose option is on, then show the algorithm step by step (print the sudoku board each step).
    if(verbose){
        cout << "\nCurrent step:\n";
        print_sudoku(board);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    // Iterate over all position, try all possible number and backtrack if no valid number is found
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
		
            if(board[i][j] != 0)continue;

            for(int num = 1;num<=9;num++){
		    
                bool valid = isValidState(board, i, j, num);
		    
                if(!valid && num == 9)return false;
                else if(!valid)continue;
                else{
                    board[i][j] = num;
			
                    if(solveSudokuRecursive(board, ans, verbose)){
                        return true;
                    }
			    
                    else{
                        board[i][j] = 0;
                        if(num == 9)return false;
                        continue;
                    }
			
                }
            }
        }
    }
	
    // if program reaches here there is a solution, assign the solved board to the ans board.
    ans = board;
    return true;
}

// Driver code for the backtracking algoritm, also handle final output
void solveSudoku(vector<vector<int>>board, vector<vector<int>> &ans, bool verbose){

    // Print initial (unsolved) sudoku board condition.
    cout << "\nInitial sudoku board: \n";
    print_sudoku(board);

    if(solveSudokuRecursive(board, ans, verbose)){  // A solution has been found
        cout << "\nSolution: \n\n";
        print_sudoku(ans);
    }

    else{  // No solution is found
        cout << "No valid solution exist!\n";
    }
    cout << '\n';
}

// Show manual page for user guide.
void show_manual(){
    printf("\nManual page:\n\nAutomatic sudoku solver using backtracking algorithm.\n");
    printf("\n Usage: \n");
    printf("\n \"./sudoku file.txt\" (without quotes)\n");
    printf("\nYou can add a verbose options with '-v' to see step by step process, \nfor example:\n");
    printf("\n \"./sudoku -v file.txt\" (without quotes)\n");
    printf("\n");
    printf("With file.txt as a properly formatted sudoku in a 9x9 number.\n \nFor example:\n");
    printf("6 0 0 1 0 7 0 0 4\n0 0 5 0 4 0 0 0 0\n0 2 7 0 6 0 0 0 0\n0 3 0 0 0 5 0 7 0\n0 9 0 0 3 0 0 0 2\n0 0 0 2 0 0 0 3 0\n0 0 0 0 0 6 0 0 5\n0 0 0 0 5 1 0 0 6\n2 0 0 4 0 0 8 0 0\n");
    printf("\nwhere zero represents an empty cell in the board.\n");
    printf("\nNote: file.txt is not space or newline sensitive, which mean you can add\nan extra space or newline and it would still be valid\nas long as it has 9 x 9 number.\n");
    printf("\n");
}


int main(int argc, char *argv[]){

    // handle passed arguments
    if(argc == 1){
        show_manual();
        exit(1);
    }  
    
    if((argc == 3 && (argv[1][0] != '-' || argv[1][1] != 'v')) || argc > 3){
        cout << "\nInvalid Usage\n\n";
        show_manual();
        exit(1);
    }

    bool verbose = false;
    if(argc == 3)verbose = true;


    // handle file from user
    ifstream file;
    file.open((argc == 2 ? argv[1] : argv[2]));
    string temp, input;

    if(!file){
        cout << "File doesn't exist!\n";
        show_manual();
        exit(1);
    }

    while(!file.eof()) {
	    getline(file, temp);
	    input += temp + "\n";
    }


    // form a sudoku board from user file
    vector<vector<int>>sudokuBoard(9, vector<int>(9,0));
    cout << input << '\n';
    int i = 0, j = 0;
    for(char c : input){
        if(c < '0' || c > '9')continue;

        if(i == 8 && j == 8){
            break;
        }

        sudokuBoard[i][j] = (c-'0');
        
        j++;
        if(j == 9){
            j = 0;
            i++;
        } 
    }

    if(i != 8 || j != 8){
        cout << "Sudoku board is not formatted properly!\n";
        exit(1);
    }

    auto startTime = chrono::high_resolution_clock::now(); // start of runtime

    // start backtracking algorithm
    solveSudoku(sudokuBoard, sudokuBoard, verbose);

    auto endTime = chrono::high_resolution_clock::now(); // end of runtime
    auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime); // total runtime duration in milliseconds

    // output runtime
    cout << "Elapsed time: " << duration.count() << " ms\n";

}

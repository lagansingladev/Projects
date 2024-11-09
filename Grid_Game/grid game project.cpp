#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int BOARD_SIZE = 4;
const int MIN_NUMBER = -10;
const int MAX_NUMBER = 10;

// Function to generate a random number between min and max (inclusive)
int generateRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Function to fill the board with random numbers and set the goal tile
void fillBoard(int board[BOARD_SIZE][BOARD_SIZE], int& goalRow, int& goalCol) {
    srand(time(0)); // Seed the random number generator with current time

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = generateRandomNumber(MIN_NUMBER, MAX_NUMBER);
        }
    }

    goalRow = generateRandomNumber(0, BOARD_SIZE - 1);
    goalCol = generateRandomNumber(0, BOARD_SIZE - 1);
    board[goalRow][goalCol] = generateRandomNumber(11, 20); // Set the goal tile
}

// Function to reveal the tiles on the board
void revealTiles(const int board[BOARD_SIZE][BOARD_SIZE], const bool revealed[BOARD_SIZE][BOARD_SIZE], int goalRow, int goalCol) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (i == goalRow && j == goalCol) {
                std::cout << "G ";
            } else if (revealed[i][j]) {
                std::cout << board[i][j] << " ";
            } else {
                std::cout << "* ";
            }
        }
        std::cout << std::endl;
    }
}

// Function to get the start position from the user
void getStartPosition(int& startRow, int& startCol, int goalRow, int goalCol) {
    do {
        std::cout << "Enter the row and column numbers to start the game: ";
        std::cin >> startRow >> startCol;
        
        

        if (startRow == goalRow && startCol == goalCol) {
            std::cout << "Invalid start position! Please choose a different tile." << std::endl;
        
        }
    } while (startRow == goalRow && startCol == goalCol);
}

// Function to move the position up
void moveUp(int& row,int& iflag) {
    if (row > 0) {
        row--;
         iflag=1;
    }
    else
    {
        iflag=0;
       std::cout << "Invalid Input" << std::endl;//Input is out of bounds 
    }
    
}

// Function to move the position down
void moveDown(int& row,int& iflag) {
    if (row < BOARD_SIZE - 1) {
        row++;
        iflag=1;
    }
    else
    {
        iflag=0;
        std::cout << "Invalid Input" << std::endl;//Input is out of bounds
    }
    
}

// Function to move the position left
void moveLeft(int& col,int& iflag) {
    if (col > 0) {
        col--;
        iflag=1;
    }
    else
    {
        iflag=0;
        std::cout << "Invalid Input" << std::endl;//Input is out of bounds
    }
   
}

// Function to move the position right
void moveRight(int& col,int& iflag) {
    if (col < BOARD_SIZE - 1) {
        col++;
        iflag=1;
    }
    else
    {
        iflag=0;
        std::cout << "Invalid Input" << std::endl;//Input is out of bounds
    }
    
}

// Function to check if the total of visited tiles falls within the range of -2 to 2
bool checkGoal(const int board[BOARD_SIZE][BOARD_SIZE], const bool revealed[BOARD_SIZE][BOARD_SIZE], int goalRow, int goalCol) {
    int sum = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (revealed[i][j]) {
                sum += board[i][j];
            }
        }
    }

    return sum >= -2 && sum <= 2;
}

int main() {
    int flag=1;
    int iflag=1;
    int board[BOARD_SIZE][BOARD_SIZE];
    bool revealed[BOARD_SIZE][BOARD_SIZE] = { false };
    int goalRow, goalCol;
    std::vector<std::string> attempts;

    fillBoard(board, goalRow, goalCol);

    std::cout << "Welcome to the board game!" << std::endl;

    do {
        int startRow, startCol;
        int currentRow, currentCol;
        int moveCount = 0;
        int sum = 0;

        revealTiles(board, revealed, goalRow, goalCol);
        getStartPosition(startRow, startCol, goalRow, goalCol);
        
        if(startRow>3 || startCol>3  || startRow<0 || startCol<0)
        {
            std::cout << "Invalid Input" << std::endl;//Input is out of bounds
            flag=0;
            break;
        }
        
        
        currentRow = startRow;
        currentCol = startCol;
        revealed[currentRow][currentCol] = true;
        sum += board[currentRow][currentCol];
        revealTiles(board, revealed, goalRow, goalCol);
        while (currentRow != goalRow || currentCol != goalCol) {
            std::string move;

            std::cout << "Current sum: " << sum << std::endl;
            std::cout << "Enter your move (up, down, left, right):";
            std::cin >> move;

            if (move == "up") {
                moveUp(currentRow,iflag);
            } else if (move == "down") {
                moveDown(currentRow,iflag);
            } else if (move == "left") {
                moveLeft(currentCol,iflag);
            } else if (move == "right") {
                moveRight(currentCol,iflag);
            } 
            else {
                std::cout << "Invalid move! Please try again." << std::endl;
                continue;
            }
            
        
            
         

            if (currentRow == goalRow && currentCol == goalCol) {
                if(sum>=-2 && sum<=2)
                {
                   std::cout << "Congratulations! You reached the goal tile." << std::endl;
                break; 
                }
                else
                {
                 std::cout << "Failure!Sum is not between [-2,2]" << std::endl;   
                }
                
                break;
            }

if(iflag==1)
{
            if (revealed[currentRow][currentCol]) {
                std::cout << "You have already visited this tile. Please choose a different move." << std::endl;
            } else {
                revealed[currentRow][currentCol] = true;
                sum += board[currentRow][currentCol];
                moveCount++;
            }
}

            revealTiles(board, revealed, goalRow, goalCol);
        }

        if (checkGoal(board, revealed, goalRow, goalCol)) {
            attempts.push_back("Success");
        } else {
            attempts.push_back("Failure");
        }

        std::cout << "Total moves: " << moveCount << std::endl;

        std::cout << "Do you want to play again? (yes/no): ";
        std::string playAgain;
        std::cin >> playAgain;

        if (playAgain != "yes") {
            break;
        }

        // Reset the board and revealed tiles for the next game
        fillBoard(board, goalRow, goalCol);
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                revealed[i][j] = false;
            }
        }
    } while (true);

   if(flag==1)
   {
    std::cout << "Game Over! Here are your attempts:" << std::endl;
    for (int i = 0; i < attempts.size(); i++) {
        std::cout << "Attempt " << i + 1 << ": " << attempts[i] << std::endl;
    }
   }

    return 0;
}

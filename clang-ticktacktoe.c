#include <stdio.h>

#define X -1
#define O -2

int board[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

//declare some protos
void printBoard(int l_board[]);
int drawCheck(int l_board[]);
int winCheck(int l_board[]);
int putInBoard(int l_board[], int pos, int newVal);
int minimax(int l_board[], int depth, int isMax);
void aiMove(int l_board[]);


int main() {
    int board[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int currentPlayer = 1; // 1 for player, 0 for AI

    while (!winCheck(board) && !drawCheck(board)) {
        printBoard(board);

        if (currentPlayer) {
            // Player's turn
            int position;
            printf("Enter the position to place your mark (a number between 1-9): ");
            scanf("%d", &position);

            if (putInBoard(board, position, 'X')) {
                currentPlayer = 0; // Switch to AI's turn
            } else {
                printf("Invalid move. Try again.\n");
            }
        } else {
            // AI's turn
            aiMove(board);
            currentPlayer = 1; // Switch to player's turn
        }
    }

    printBoard(board);

    if (winCheck(board)) {
        printf("Game over! %s wins!\n", currentPlayer ? "Player" : "AI");
    } else {
        printf("It's a draw!\n");
    }

    return 0;
}








// Function to print the board
// board should be a 3x3 grid
void printBoard(int l_board[]) {
    printf("\n");
    printf(" %c | %c | %c\n", l_board[0], l_board[1], l_board[2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", l_board[3], l_board[4], l_board[5]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", l_board[6], l_board[7], l_board[8]);
    printf("\n");
}

// Function to check if the game is a draw
// board should be a 3x3 grid
int drawCheck(int l_board[]) {
    for (int i = 0; i < 9; ++i) { //9 is the max number of moves we can make on a 3x3 board
        if (l_board[i] != 'X' && l_board[i] != 'O') {
            // If any position is not filled, the game is not a draw
            return 0;
        }
    }
    // All positions are filled, indicating a draw
    return 1;
}

// Function to check if someone has won
// board should be a 3x3 grid
int winCheck(int l_board[]) {
    // Check rows
    for (int i = 0; i < 9; i += 3) {
        if (l_board[i] == l_board[i + 1] && l_board[i + 1] == l_board[i + 2]) {
            return 1; // Row win
        }
    }

    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (l_board[i] == l_board[i + 3] && l_board[i + 3] == l_board[i + 6]) {
            return 1; // Column win
        }
    }

    // Check diagonals
    if ((l_board[0] == l_board[4] && l_board[4] == l_board[8]) ||
        (l_board[2] == l_board[4] && l_board[4] == l_board[6])) {
        return 1; // Diagonal win
    }

    return 0; // No win yet
}

// Function to make a move
int putInBoard(int l_board[], int pos, int newVal) {
    if (pos < 1 || pos > 9) {
        // Invalid position
        return 0;
    }

    // Convert position to array index
    int index = pos - 1;

    if (l_board[index] == 'X' || l_board[index] == 'O') {
        // Position already occupied
        return 0;
    }

    // Update the board with the new value
    l_board[index] = newVal;
    return 1; // Successful move
}

// Minimax algorithm for player-AI move. uses Minimax alg to determine the best move (recursively evaluates all possible moves to find the optimal AI move)
// Assuming the board is a 3x3 grid
int minimax(int l_board[], int depth, int isMax) {
    // Base cases: check for terminal states (win, draw, or depth limit)
    if (winCheck(l_board)) {
        return isMax ? -1 : 1; // If AI wins, return -1; if player wins, return 1
    }
    if (drawCheck(l_board) || depth == 0) {
        return 0; // Game is a draw or reached depth limit
    }

    // Recursive case: evaluate all possible moves
    int bestScore = isMax ? -1000 : 1000;
    for (int i = 0; i < 9; ++i) {
        if (l_board[i] != 'X' && l_board[i] != 'O') {
            // Empty position, make a move
            char originalValue = l_board[i];
            l_board[i] = isMax ? 'O' : 'X';

            // Recurse with the updated board
            int score = minimax(l_board, depth - 1, !isMax);

            // Undo the move
            l_board[i] = originalValue;

            // Update bestScore based on the current move
            if ((isMax && score > bestScore) || (!isMax && score < bestScore)) {
                bestScore = score;
            }
        }
    }
    return bestScore;
}

// AI's turn
void aiMove(int l_board[]) {
    int bestScore = -1000;
    int bestMove = -1;

    for (int i = 0; i < 9; ++i) {
        if (l_board[i] != 'X' && l_board[i] != 'O') {
            char originalValue = l_board[i];
            l_board[i] = 'O';

            int score = minimax(l_board, 9, 0); // Depth set to 9 (full board)
            l_board[i] = originalValue;

            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }

    if (bestMove != -1) {
        l_board[bestMove] = 'O'; // Make the best move
    }
}

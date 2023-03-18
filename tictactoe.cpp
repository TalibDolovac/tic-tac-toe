#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int BOARD_SIZE = 3;
char board[BOARD_SIZE][BOARD_SIZE];

void display_board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool is_valid_move(int row, int col) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return false;
    }
    if (board[row][col] != ' ') {
        return false;
    }
    return true;
}

bool has_won(char symbol) {
    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
            return true;
        }
    }
    // Check columns
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[0][j] == symbol && board[1][j] == symbol && board[2][j] == symbol) {
            return true;
        }
    }
    // Check diagonals
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) {
        return true;
    }
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) {
        return true;
    }
    return false;
}

bool is_board_full() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void computer_move() {
    srand(time(NULL));
    int row, col;
    do {
        row = rand() % BOARD_SIZE;
        col = rand() % BOARD_SIZE;
    } while (!is_valid_move(row, col));
    board[row][col] = 'O';
}

void score(int user_score, int computer_score) {
	
	cout << "Your score:" << user_score << endl << endl;
	cout << "computer score:" << computer_score << endl << endl;
	
}

int main() {
    // Initialize board with empty spaces
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
    char user_symbol = 'X';
    int user_score = 0;
    char computer_symbol = 'O';
    int computer_score = 0;
    bool user_turn = true;
    bool play_again = true; // added variable for user to choose whether to play again
    do {
        while (true) {
            // Display board
            display_board();
            // Take user input
            int row, col;
            if (user_turn) {
                cout << "Enter row (1-3): ";
                cin >> row;
                cout << "Enter column (1-3): ";
                cin >> col;
                row--;
                col--;
                if (!is_valid_move(row, col)) {
                    cout << "Invalid move, try again." << endl;
                    continue;
                }
                board[row][col] = user_symbol;
            } else {
                // Implement computer's turn
                cout << "Computer's turn." << endl;
                // Loop until a valid move is found
                while (true) {
                    // Generate random row and column
                    row = rand() % BOARD_SIZE;
                    col = rand() % BOARD_SIZE;
                    // Check if move is valid
                    if (is_valid_move(row, col)) {
                        board[row][col] = computer_symbol;
                        break;
                    }
                }
            }
            // Check for win or tie
            if (has_won(user_symbol)) {
                user_score++;
                display_board();
                cout << "You win!" << endl;
                score(user_score, computer_score);
                break;
            }
            if (has_won(computer_symbol)) {
                computer_score++;
                display_board();
                cout << "Computer wins!" << endl;
                score(user_score, computer_score);
                break;
            }
            if (is_board_full()) {
                display_board();
                cout << "It's a tie!" << endl;
                score(user_score, computer_score);
                break;
            }
            // Alternate turns
            user_turn = !user_turn;
        }
        // Ask the user if they want to play again
        cout << "Do you want to play again? (Y/N): ";
        char answer;
        cin >> answer;
        if (answer != 'Y' && answer != 'y') {
            play_again = false;
        }
        // Reset the board and scores for a new game
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                board[i][j] = ' ';
            }
        }
        
        user_turn = true;
    } while (play_again);
    return 0;
} 

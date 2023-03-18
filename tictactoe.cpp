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
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
            return true;
        }
    }
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[0][j] == symbol && board[1][j] == symbol && board[2][j] == symbol) {
            return true;
        }
    }
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
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
    char user_symbol;
    int user_score = 0;
    char computer_symbol;
    int computer_score = 0;
    bool user_turn = true;
    bool play_again = true; 

    while(true) {
        cout << "What symbol do you want: ";
        cin >> user_symbol;

        cout << "What computer symbol do you want: ";
        cin >> computer_symbol; 

        if(user_symbol != computer_symbol) {
            break;
        } else {
            cout << "Error: Symbols must be different. Please try again." << endl;
        }
    }

    user_symbol = toupper(user_symbol); 
    computer_symbol = toupper(computer_symbol);

    do {
        while (true) {
            display_board();
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
                cout << "Computer's turn." << endl;
                 while (true) {
                   row = rand() % BOARD_SIZE;
                    col = rand() % BOARD_SIZE;
                    if (is_valid_move(row, col)) {
                        board[row][col] = computer_symbol;
                        break;
                    }
                }
            }
          
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
           
            user_turn = !user_turn;
        }
        cout << "Do you want to play again? (Y/N): ";
        char answer;
        cin >> answer;
        if (answer != 'Y' && answer != 'y') {
            play_again = false;
        }
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                board[i][j] = ' ';
            }
        }
        
        user_turn = true;
    } while (play_again);
    return 0;
} 

#include <iostream>
using namespace std;

char board[9] = {'1','2','3','4','5','6','7','8','9'};
char player = 'O'; // Human is 'O', AI is 'X'

void drawBoard() {
    cout << "\n";
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
    cout << "-----------\n";
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
    cout << "-----------\n";
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;
    cout << "\n";
}

bool isMoveValid(int move) {
    if (move < 1 || move > 9) return false;
    return board[move-1] != 'X' && board[move-1] != 'O';
}

bool checkWin(char player) {
    // Check rows
    for (int i = 0; i < 9; i += 3) {
        if (board[i] == player && board[i+1] == player && board[i+2] == player)
            return true;
    }
    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[i] == player && board[i+3] == player && board[i+6] == player)
            return true;
    }
    // Check diagonals
    if (board[0] == player && board[4] == player && board[8] == player) return true;
    if (board[2] == player && board[4] == player && board[6] == player) return true;
    return false;
}

bool isBoardFull() {
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') return false;
    }
    return true;
}

void aiMove() {
    cout << "AI is thinking...\n";
    
    // Simple AI logic:
    // 1. Try to win
    // 2. Block player
    // 3. Take center
    // 4. Take any available spot
    
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            board[i] = 'X';
            if (checkWin('X')) return;
            board[i] = i+'1'; // Undo move
        }
    }
    
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            board[i] = 'O';
            if (checkWin('O')) {
                board[i] = 'X'; // Block player
                return;
            }
            board[i] = i+'1'; // Undo move
        }
    }
    
    if (board[4] == '5') {
        board[4] = 'X';
        return;
    }
    
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            board[i] = 'X';
            return;
        }
    }
}

int main() {
    cout << "Welcome to Tic-Tac-Toe!\n";
    cout << "You're O vs AI (X). AI goes first.\n";
    cout << "Enter numbers 1-9 to make your move.\n";
    
    while (true) {
        // AI move first
        aiMove();
        drawBoard();
        
        if (checkWin('X')) {
            cout << "AI wins! Better luck next time!\n";
            break;
        }
        if (isBoardFull()) {
            cout << "It's a tie!\n";
            break;
        }
        
        // Player move
        int move;
        while (true) {
            cout << "Your turn (O). Enter position (1-9): ";
            cin >> move;
            
            if (isMoveValid(move)) {
                board[move-1] = 'O';
                break;
            }
            cout << "Invalid move. Try again.\n";
        }
        
        drawBoard();
        
        if (checkWin('O')) {
            cout << "You win! Great job!\n";
            break;
        }
        if (isBoardFull()) {
            cout << "It's a tie!\n";
            break;
        }
    }
    
    cout << "Game over. Thanks for playing!\n";
    return 0;
}

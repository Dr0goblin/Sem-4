def print_board(board):
    """Print the current game board"""
    print("\n")
    for i in range(3):
        print(f" {board[i*3]} | {board[i*3+1]} | {board[i*3+2]} ")
        if i < 2:
            print("-----------")
    print("\n")

def check_winner(board):
    """Check if there's a winner or if the game is a tie"""
    # Check rows
    for i in range(0, 9, 3):
        if board[i] == board[i+1] == board[i+2] != " ":
            return board[i]
    
    # Check columns
    for i in range(3):
        if board[i] == board[i+3] == board[i+6] != " ":
            return board[i]
    
    # Check diagonals
    if board[0] == board[4] == board[8] != " ":
        return board[0]
    if board[2] == board[4] == board[6] != " ":
        return board[2]
    
    # Check for tie
    if " " not in board:
        return "Tie"
    
    return None

def ai_move(board):
    """Simple AI that follows basic rules"""
    # Try to win first
    for i in range(9):
        if board[i] == " ":
            board[i] = "X"
            if check_winner(board) == "X":
                return
            board[i] = " "
    
    # Block player if they can win
    for i in range(9):
        if board[i] == " ":
            board[i] = "O"
            if check_winner(board) == "O":
                board[i] = "X"
                return
            board[i] = " "
    
    # Take center if available
    if board[4] == " ":
        board[4] = "X"
        return
    
    # Take any available corner
    for i in [0, 2, 6, 8]:
        if board[i] == " ":
            board[i] = "X"
            return
    
    # Take any available side
    for i in [1, 3, 5, 7]:
        if board[i] == " ":
            board[i] = "X"
            return

def play_game():
    """Main game loop"""
    board = [" "] * 9
    print("Welcome to Tic-Tac-Toe!")
    print("You're O vs the AI (X). The AI goes first.")
    print("Enter numbers 1-9 to make your move (1=top-left, 9=bottom-right)\n")
    
    # Show position reference
    print("Position numbers:")
    print_board(["1", "2", "3", "4", "5", "6", "7", "8", "9"])
    
    while True:
        # AI's turn
        print("AI's move (X):")
        ai_move(board)
        print_board(board)
        
        # Check if AI won
        winner = check_winner(board)
        if winner == "X":
            print("AI wins! Better luck next time!")
            break
        if winner == "Tie":
            print("It's a tie!")
            break
            
        # Player's turn
        while True:
            try:
                move = int(input("Your move (O). Enter position (1-9): ")) - 1
                if 0 <= move <= 8 and board[move] == " ":
                    board[move] = "O"
                    break
                print("Invalid move. Try again.")
            except ValueError:
                print("Please enter a number 1-9.")
        
        print_board(board)
        
        # Check if player won
        winner = check_winner(board)
        if winner == "O":
            print("You win! Great job!")
            break
        if winner == "Tie":
            print("It's a tie!")
            break

if __name__ == "__main__":
    play_game()
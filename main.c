#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Define the game board and player symbols
char board[3][3];
const char player = 'X';
const char computer = 'O';

// Function declarations
void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

// Main function
int main() {
	// Variables to store the winner and user response to play again
	char winner = ' ';
	char response;

	do {
		// Reset the game state
		winner = ' ';
		response = ' ';

		// Initialize the game board
		resetBoard();

		// Main game loop
		while (winner == ' ' && checkFreeSpaces() != 0) {
			// Print the current state of the board
			printBoard();

			// Player's move
			playerMove();
			winner = checkWinner();
			if (winner != ' ' || checkFreeSpaces() == 0) {
				break;
			}

			// Computer's move
			computerMove();
			winner = checkWinner();
			if (winner != ' ' || checkFreeSpaces() == 0) {
				break;
			}
		}

		// Print the final state of the board and the winner
		printBoard();
		printWinner(winner);

		// Ask the user if they want to play again
		printf("\nPlay again? (y/n): ");
		fflush(stdin);
		scanf("%c", &response);
		response = toupper(response);

	} while (response == 'Y');

	printf("\nThanks for playing!\n");

	return 0;
}

// Function to reset the game board
void resetBoard() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = ' ';
		}
	}
}

// Function to print the game board
void printBoard() {
	printf("   1   2   3\n");
	printf("1  %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
	printf("  ---|---|---\n");
	printf("2  %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
	printf("  ---|---|---\n");
	printf("3  %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
}

// Function to check the number of free spaces on the board
int checkFreeSpaces() {
	int freeSpaces = 9;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] != ' ') {
				freeSpaces--;
			}
		}
	}
	return freeSpaces;
}

// Function for the player's move
void playerMove() {
	int x, y;

	printf("Your turn, enter row (1-3) and column (1-3): ");
	scanf("%d %d", &x, &y);
	x--;
	y--;

	printf("\n");

	// Check for valid move
	if (x < 0 || x > 2 || y < 0 || y > 2 || board[x][y] != ' ') {
		printf("Invalid Move!\n");
		playerMove(); // Ask for input again
	} else {
		board[x][y] = player; // Set player's move on the board
	}
}

// Function for the computer's move
void computerMove() {
	int x, y;
	srand(time(NULL));

	if (checkFreeSpaces() > 0) {
		// Randomly select a move for the computer
		do {
			x = rand() % 3;
			y = rand() % 3;
		} while (board[x][y] != ' ');

		board[x][y] = computer; // Set computer's move on the board
	} else {
		printWinner(' '); // Handle the case of a draw
	}
}

// Function to check if there is a winner
char checkWinner() {
	for (int i = 0; i < 3; ++i) {
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
			return board[i][0];
		}
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
			return board[0][i];
		}
		if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
			return board[0][0];
		}
		if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
			return board[0][2];
		}
	}

	return ' '; // No winner yet
}

// Function to print the winner
void printWinner(char winner) {
	if (winner == player) {
		printf("You won!\n");
	} else if (winner == computer) {
		printf("You lost!\n");
	} else {
		printf("Draw!\n");
	}
}
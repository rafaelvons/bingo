#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
const int BOARD_SIZE = 5;

struct BingoCard {
    int numbers[BOARD_SIZE][BOARD_SIZE];
};

struct BingoGame {
    int drawnNumbers[BOARD_SIZE * BOARD_SIZE];
    int drawnCount;
    BingoCard playerCard;
};

void initializeGame(BingoGame &game) {
    // Initialize player's Bingo card
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            game.playerCard.numbers[i][j] = rand() % 15 + 1; // Generate random numbers (1-15)
        }
    }

    // Initialize drawn numbers
    game.drawnCount = 0;
}

int drawNumber(BingoGame &game) {
    // Draw a random number and ensure it hasn't been drawn before
    int drawnNumber;
    bool alreadyDrawn;

    do {
        alreadyDrawn = false;
        drawnNumber = rand() % 15 + 1; // Generate random numbers (1-15)

        for (int i = 0; i < game.drawnCount; ++i) {
            if (game.drawnNumbers[i] == drawnNumber) {
                alreadyDrawn = true;
                break;
            }
        }
    } while (alreadyDrawn);

    // Record the drawn number
    game.drawnNumbers[game.drawnCount++] = drawnNumber;

    return drawnNumber;
}

void updateCard(BingoGame &game, int drawnNumber) {
    // Update player's Bingo card after a number is drawn
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (game.playerCard.numbers[i][j] == drawnNumber) {
                game.playerCard.numbers[i][j] = 0; // Mark the drawn number on the card
            }
        }
    }
}

bool checkWinner(const BingoCard &card) {
    // Check if the player has achieved a winning pattern or filled the entire Bingo card
 // Check rows and columns
    for (int i = 0; i < BOARD_SIZE; ++i) {
        bool rowWin = true;
        bool colWin = true;

        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (card.numbers[i][j] != 0) {
                rowWin = false;
            }

            if (card.numbers[j][i] != 0) {
                colWin = false;
            }
        }

        if (rowWin || colWin) {
            return true;
        }
    }

    // Check diagonals
    bool diag1Win = true;
    bool diag2Win = true;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (card.numbers[i][i] != 0) {
            diag1Win = false;
        }

        if (card.numbers[i][BOARD_SIZE - 1 - i] != 0) {
            diag2Win = false;
        }
    }

    if (diag1Win || diag2Win) {
        return true;
    }

    return false;
   
}

void displayCard(const BingoCard &card) {
    // Display the player's Bingo card
    cout << "Player's Bingo Card:" << endl;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << card.numbers[i][j] << "\t";
        }
        cout <<" "<<endl;
    }

    cout <<" " <<endl;
}

void playBingo() {
    // Main function to organize the Bingo game
    BingoGame game;
    initializeGame(game);

    while (!checkWinner(game.playerCard)) {
        // Display game status
        displayCard(game.playerCard);

        // Draw a number
        int drawnNumber = drawNumber(game);
        cout << "Number drawn: " << drawnNumber << endl;

        // Update Bingo card
        updateCard(game, drawnNumber);
    }

    // Display the winner
    cout << "Bingo! You're a winner!" << endl;
}

int main() {
	system("cls");
	cout <<"======================================" << endl;
	cout << "Selamat Datang di Permainan Bingo!" << endl;\
	cout <<"======================================" << endl;
    // Set seed for the rand() function
    srand(static_cast<unsigned int>(time(nullptr)));

    // Start the Bingo game
    playBingo();

    return 0;
}

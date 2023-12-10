#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

const int BOARD_SIZE = 5;

struct BingoCard {
    int numbers[BOARD_SIZE][BOARD_SIZE];
};

struct BingoPlayer {
    string name;
    BingoCard card;
};

struct BingoGame {
    int drawnNumbers[BOARD_SIZE * BOARD_SIZE];
    int drawnCount;
    BingoPlayer* players;
    int numPlayers;
};

void pressEnterToContinue() {
    cout << "Press Enter to continue..." <<endl;
    cin.get();
}

void initializeGame(BingoGame &game) {
    
    cout << "Enter the number of players: ";
    cin >> game.numPlayers;

   
    game.players = new BingoPlayer[game.numPlayers];

    // Initialize players' Bingo cards
    for (int k = 0; k < game.numPlayers; ++k) {
        cout << "Enter the name of Player " << k + 1 << ": ";
        cin >> game.players[k].name;

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                game.players[k].card.numbers[i][j] = rand() % 15 + 1; 
            }
        }
    }

    
    game.drawnCount = 0;
}

int drawNumber(BingoGame &game) {
    
    int drawnNumber;
    bool alreadyDrawn;

    do {
        alreadyDrawn = false;
        drawnNumber = rand() % 15 + 1; 

        for (int i = 0; i < game.drawnCount; ++i) {
            if (game.drawnNumbers[i] == drawnNumber) {
                alreadyDrawn = true;
                break;
            }
        }
    } while (alreadyDrawn);

    
    game.drawnNumbers[game.drawnCount++] = drawnNumber;

    return drawnNumber;
}

void updateCard(BingoCard &card, int drawnNumber) {
    
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (card.numbers[i][j] == drawnNumber) {
                card.numbers[i][j] = 0; 
            }
        }
    }
}

bool checkWinner(const BingoCard &card) {
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
    cout << "Player's Bingo Card:" << endl;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << card.numbers[i][j] << "\t";
        }
        cout << endl;
    }

    cout << endl;
}

void playBingo() {
    
    BingoGame game;
    initializeGame(game);

    int turnsBeforeClear = game.numPlayers; 
    int currentTurn = 0;

    while (true) {
        // Display game status for each player
        for (int k = 0; k < game.numPlayers; ++k) {
            cout << "Player " << game.players[k].name << "'s turn:" << endl;
            pressEnterToContinue(); 
            displayCard(game.players[k].card);

            
            int drawnNumber = drawNumber(game);
            cout << "Number drawn: " << drawnNumber << endl;

            
            updateCard(game.players[k].card, drawnNumber);

           
            displayCard(game.players[k].card);

            
            if (checkWinner(game.players[k].card)) {
                cout << "Bingo! " << game.players[k].name << " is a winner!" << endl;
                return;
            }

            currentTurn++;
            
            // Clear the screen after a specified number of turns
            if (currentTurn % turnsBeforeClear == 0) {
                pressEnterToContinue();
                system("cls");
            }
        }
    }
}



int main() {
    
    system("cls");
	cout <<"======================================================================" << endl;
	cout << "                   Selamat Datang di Permainan Bingo!                " << endl;
	cout <<"======================================================================" << endl;
    srand(static_cast<unsigned int>(time(nullptr)));

    
    playBingo();

    return 0;
}

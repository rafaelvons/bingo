#include <iostream>  // Library untuk input/output
#include <cstdlib>   // Library utilitas umum
#include <ctime>     // Library C Time untuk pengacakan angka
#include <limits>    // Library batas numerik

using namespace std;  // Menggunakan namespace standar

const int BOARD_SIZE = 5;  // Konstanta untuk merepresentasikan ukuran papan Bingo

// Struktur untuk merepresentasikan kartu Bingo
struct BingoCard {
    int numbers[BOARD_SIZE][BOARD_SIZE];  // Array 2D untuk menyimpan angka kartu Bingo
};

// Struktur untuk merepresentasikan pemain Bingo
struct BingoPlayer {
    string name;    // Nama pemain
    BingoCard card;  // Kartu Bingo pemain
};

// Struktur untuk merepresentasikan permainan Bingo secara keseluruhan
struct BingoGame {
    int drawnNumbers[BOARD_SIZE * BOARD_SIZE];  // Array untuk menyimpan angka yang sudah ditarik
    int drawnCount;                             // Jumlah angka yang sudah ditarik
    BingoPlayer* players;                       // Array pemain
    int numPlayers;                             // Jumlah pemain
};

// Fungsi untuk meminta pengguna menekan Enter untuk melanjutkan
void pressEnterToContinue() {
    cout << "Tekan Untuk Melanjutkan..." << endl;
    cin.get();
}

// Fungsi untuk menginisialisasi permainan Bingo
void initializeGame(BingoGame &game) {
    // Meminta pengguna untuk jumlah pemain
    cout << "Masukkan Jumlah Pemain: ";
    cin >> game.numPlayers;

    // Mengalokasikan memori dinamis untuk pemain
    game.players = new BingoPlayer[game.numPlayers];

    // Menginisialisasi kartu Bingo pemain dengan angka acak
    for (int k = 0; k < game.numPlayers; ++k) {
        cout << "Masukkan Nama Pemain Ke-" << k + 1 << ": ";
        cin >> game.players[k].name;

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                game.players[k].card.numbers[i][j] = rand() % 15 + 1; 
            }
        }
    }

    // Menginisialisasi jumlah angka yang sudah ditarik
    game.drawnCount = 0;
}

// Fungsi untuk menarik nomor Bingo secara acak
int drawNumber(BingoGame &game) {
    int drawnNumber;
    bool alreadyDrawn;

    do {
        // Menghasilkan nomor acak
        alreadyDrawn = false;
        drawnNumber = rand() % 15 + 1; 

        // Memeriksa apakah nomor sudah pernah ditarik sebelumnya
        for (int i = 0; i < game.drawnCount; ++i) {
            if (game.drawnNumbers[i] == drawnNumber) {
                alreadyDrawn = true;
                break;
            }
        }
    } while (alreadyDrawn);

    // Menyimpan nomor yang sudah ditarik
    game.drawnNumbers[game.drawnCount++] = drawnNumber;

    return drawnNumber;
}

// Fungsi untuk memperbarui kartu pemain setelah nomor ditarik
void updateCard(BingoCard &card, int drawnNumber) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (card.numbers[i][j] == drawnNumber) {
                card.numbers[i][j] = 0; 
            }
        }
    }
}

// Fungsi untuk memeriksa apakah pemain sudah menang
bool checkWinner(const BingoCard &card) {
    // Melakukan iterasi baris pada kartu Bingo untuk memeriksa kemenangan dalam baris atau kolom
    for (int i = 0; i < BOARD_SIZE; ++i) {
        bool rowWin = true;
        bool colWin = true;

    // Iterasi kolom untuk memeriksa setiap elemen dalam baris
    for (int j = 0; j < BOARD_SIZE; ++j) {
        // Memeriksa apakah elemen tidak sama dengan 0 (belum dicoret)
        if (card.numbers[i][j] != 0) {
            rowWin = false;  // Jika ada elemen yang tidak 0, maka tidak ada kemenangan dalam baris
        }

        // Memeriksa apakah elemen dalam kolom tidak sama dengan 0
        if (card.numbers[j][i] != 0) {
            colWin = false;  // Jika ada elemen yang tidak 0, maka tidak ada kemenangan dalam kolom
        }
    }

    // Memeriksa apakah ada kemenangan dalam baris atau kolom
    if (rowWin || colWin) {
        return true;  // Jika ada kemenangan dalam baris atau kolom, mengembalikan true
    }
}

// Melakukan iterasi untuk memeriksa kemenangan diagonal
bool diag1Win = true;
bool diag2Win = true;

for (int i = 0; i < BOARD_SIZE; ++i) {
    // Memeriksa elemen diagonal pertama
    if (card.numbers[i][i] != 0) {
        diag1Win = false;  // Jika ada elemen yang tidak 0, maka tidak ada kemenangan dalam diagonal pertama
    }

    // Memeriksa elemen diagonal kedua
    if (card.numbers[i][BOARD_SIZE - 1 - i] != 0) {
        diag2Win = false;  // Jika ada elemen yang tidak 0, maka tidak ada kemenangan dalam diagonal kedua
    }
}

// Memeriksa apakah ada kemenangan dalam diagonal
if (diag1Win || diag2Win) {
    return true;  // Jika ada kemenangan dalam diagonal, mengembalikan true
}

// Jika tidak ada kemenangan dalam baris, kolom, atau diagonal, mengembalikan false
return false;

}

// Fungsi untuk menampilkan kartu Bingo pemain
void displayCard(const BingoCard &card) {
    cout << "Kartu Bingo Pemain:" << endl;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << card.numbers[i][j] << "\t";
        }
        cout << endl;
    }

    cout << endl;
}



// Fungsi utama yang mengatur seluruh alur permainan Bingo
void playBingo() {
    BingoGame game;
    initializeGame(game);

    int turnsBeforeClear = game.numPlayers; 
    int currentTurn = 0;

    while (true) {
        // Menampilkan status permainan untuk setiap pemain
        for (int k = 0; k < game.numPlayers; ++k) {
            cout << "Sekarang Adalah Giliran Pemain " << game.players[k].name << "!" << endl;
            pressEnterToContinue(); 
            displayCard(game.players[k].card);

            // Menarik nomor secara acak
            int drawnNumber = drawNumber(game);
            cout << "Angka Yang Ditarik: " << drawnNumber << endl;

            // Memperbarui kartu pemain
            updateCard(game.players[k].card, drawnNumber);

            // Menampilkan kartu pemain yang sudah diperbarui
            displayCard(game.players[k].card);

            // Memeriksa apakah pemain sudah menang
            if (checkWinner(game.players[k].card)) {
                cout << "Bingo!, " << game.players[k].name << " Adalah Pemenangnya. YEEEEEE" << endl;
                return;
            }

            currentTurn++;

            // Membersihkan layar setelah sejumlah putaran tertentu
            if (currentTurn % turnsBeforeClear == 0) {
                pressEnterToContinue();
                system("cls");
            }
        }
    }
}

int main() {
    // Membersihkan layar dan menampilkan pesan selamat datang
    system("cls");
	cout <<"======================================================================" << endl;
	cout << "                   Selamat Datang di Permainan Bingo!                " << endl;\
	cout <<"======================================================================" << endl;
    srand(static_cast<unsigned int>(time(nullptr)));

    // Memulai permainan Bingo
    playBingo();

    return 0;
}

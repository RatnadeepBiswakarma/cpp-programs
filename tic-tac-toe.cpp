#include <ctime>
#include <iostream>
#include <string>

using namespace std;

class Board {
 public:
  Board() {
    for (int i = 0; i < 9; i++) {
      slots[i] = to_string(i);
    }
    string players[2] = {"X", "O"};
    srand(time(NULL));
    whoseTurn = players[rand() % 2];
    renderBoard();
    promptForTurn();
  }

 private:
  string whoseTurn;
  int selectedSlotIndex;
  string userInput;
  int numberOfSlots = 9;
  string slots[9] = {};

  bool hasSameValue(string value, int pos1, int pos2, int pos3) {
    return slots[pos1] == value && slots[pos1] == slots[pos2] &&
           slots[pos1] == slots[pos3];
  }

  bool noSlotLeft() {
    int count = 0;
    for (int i = 0; i < 9; i++) {
      if (isPositionTaken(i)) {
        count++;
      }
    }

    return count == 9;
  }

  bool hasWon(string symbol) {
    return (hasSameValue(symbol, 0, 1, 2) || hasSameValue(symbol, 3, 4, 5) ||
            hasSameValue(symbol, 6, 7, 8) || hasSameValue(symbol, 0, 3, 6) ||
            hasSameValue(symbol, 1, 4, 7) || hasSameValue(symbol, 2, 5, 8) ||
            hasSameValue(symbol, 0, 4, 8) || hasSameValue(symbol, 2, 4, 6));
  }

  void renderBoard() {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
      if (i == 1 || i == 4 || i == 7) {
        cout << " | " << slots[i] << " | ";
      } else {
        cout << slots[i];
      }
      if (i == 2 || i == 5 || i == 8) {
        cout << '\n';
      }
    }
  }

  void endGame(bool isTie) {
    if (isTie) {
      cout << "It's a tie!\n";
    } else {
      cout << "Game Over! " << whoseTurn << " won the game!\n";
    }

    cout << "Start a new game? (Y/N)\t";
    string response;
    cin >> response;

    if (response == "Y" || response == "y") {
      system("clear");
      Board myBoard;
    } else {
      cout << "Bye for now!\n";
    }
  }

  bool isPositionTaken(int index) {
    return (slots[index] == "X" || slots[index] == "O");
  }

  void fillSlot(int index) {
    slots[index] = whoseTurn;
    system("clear");
    renderBoard();

    if (hasWon(whoseTurn)) {
      endGame(false);
    } else if (noSlotLeft()) {
      endGame(true);
    } else {
      if (whoseTurn == "X") {
        whoseTurn = "O";
      } else {
        whoseTurn = "X";
      }

      promptForTurn();
    }
  }

  void promptForTurn() {
    cout << whoseTurn << "'s turn, select position from available slots:\t";
    cin >> selectedSlotIndex;

    while (isPositionTaken(selectedSlotIndex)) {
      cout << "That position is already taken by `" << slots[selectedSlotIndex]
           << "` select position from available slots: \t";

      cin >> selectedSlotIndex;

      if (!isPositionTaken(selectedSlotIndex)) {
        fillSlot(selectedSlotIndex);
      }
    }

    fillSlot(selectedSlotIndex);
  }
};

int main() {
  system("clear");
  Board myBoard;
  return 0;
}

/**
*
* Solution to course project # 6
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Христо Щерев
* @idnumber 1MI0600584
* @compiler GCC
*
* Main file for the Queens game project
*
*/

#include <fstream>
#include <iostream>

using namespace std;


const int MAX_ROW = 20;
const int MAX_COL = 20;
const int MAX_MOVES = 400;
const int DIRECTIONS_COUNT = 8;
const int MAX_CMD_SIZE = 100;
const int MAX_FILENAME_SIZE = 100;

bool areStringsEqual(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return false;
        }
        i++;
    }
    return (s1[i] == '\0' && s2[i] == '\0');
}

void printHelp() {
    cout << "Available commands:" << endl;
    cout << " new N M       -> Start new game (N x M)" << endl;
    cout << " play x y      -> Place a queen at (x, y)" << endl;
    cout << " free          -> List all valid moves" << endl;
    cout << " show          -> Display the board" << endl;
    cout << " save <file>   -> Save game to file" << endl;
    cout << " load <file>   -> Load game from file" << endl;
    cout << " back          -> Undo last move" << endl;
    cout << " turn          -> Show who is next" << endl;
    cout << " help          -> Show this menu" << endl;
    cout << " exit          -> Exit the game" << endl;
}

void printMatrix(char matrix[MAX_ROW][MAX_COL], int row, int col) {
    cout << "   ";
    for (int j = 0; j < col; j++) {
        if (j < 10) {
            cout << j << "  ";
        }
        else {
            cout << j << " ";
        }
    }
    cout << endl;

    for (int i = 0; i < row; i++) {
        if (i < 10) {
            cout << i << "  ";
        }
        else {
            cout << i << " ";
        }

        for (int j = 0; j < col; j++) {
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
}

void printFreeCells(char matrix[MAX_ROW][MAX_COL], int row, int col) {
    int count = 0;
    cout << "Free cells: ";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] == '.') {
                cout << "(" << i << "," << j << ") ";
                count++;
            }
        }
    }
    if (count == 0) {
        cout << "None";
    }
    cout << endl;
}

bool hasValidMoves(char matrix[MAX_ROW][MAX_COL], int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] == '.') {
                return true;
            }
        }
    }
    return false;
}

void clearBoard(char matrix[MAX_ROW][MAX_COL], int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix[i][j] = '.';
        }
    }
}

void markTerritory(char matrix[MAX_ROW][MAX_COL], int queenRow, int queenCol, int row, int col) {
    int rowChange[] = { 1, -1, 0, 0, -1, -1, 1, 1 };
    int colChange[] = { 0, 0, 1, -1, 1, -1, 1, -1 };

    for (int i = 0; i < DIRECTIONS_COUNT; i++) {
        int currentRow = queenRow + rowChange[i];
        int currentCol = queenCol + colChange[i];

        while (currentRow >= 0 && currentRow < row && currentCol >= 0 && currentCol < col) {
            if (matrix[currentRow][currentCol] == '.') {
                matrix[currentRow][currentCol] = '*';
            }
            currentRow += rowChange[i];
            currentCol += colChange[i];
        }
    }
}

void reconstructBoard(char matrix[MAX_ROW][MAX_COL], int row, int col,
    int histR[], int histC[], char histP[], int histCount) {
    clearBoard(matrix, row, col);
    for (int i = 0; i < histCount; i++) {
        int r = histR[i];
        int c = histC[i];
        char player = histP[i];
        matrix[r][c] = player;
        markTerritory(matrix, r, c, row, col);
    }
}

void saveGame(char matrix[MAX_ROW][MAX_COL], int row, int col, int turnCounter,
    int histR[], int histC[], char histP[], int histCount, const char* filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not save to file!" << endl;
        return;
    }

    file << row << " " << col << " " << turnCounter << " " << histCount << endl;
    for (int i = 0; i < histCount; i++) {
        file << histR[i] << " " << histC[i] << " " << histP[i] << endl;
    }

    file.close();
    cout << "Game saved successfully." << endl;
}

bool loadGame(char matrix[MAX_ROW][MAX_COL], int& row, int& col, int& turnCounter,
    int histR[], int histC[], char histP[], int& histCount, const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file!" << endl;
        return false;
    }

    file >> row >> col >> turnCounter >> histCount;
    if (row > MAX_ROW || col > MAX_COL) {
        cout << "Error: Saved board size is too big!" << endl;
        file.close();
        return false;
    }

    clearBoard(matrix, row, col);
    for (int i = 0; i < histCount; i++) {
        file >> histR[i] >> histC[i] >> histP[i];
    }
    reconstructBoard(matrix, row, col, histR, histC, histP, histCount);

    file.close();
    cout << "Game loaded successfully." << endl;
    return true;
}

bool tryPlaceQueen(char matrix[MAX_ROW][MAX_COL], int row, int col, int r, int c, char player,
    int histR[], int histC[], char histP[], int& histCount) {
    if (r < 0 || r >= row || c < 0 || c >= col) {
        cout << "Error: Coordinates out of bounds!" << endl;
        return false;
    }
    if (matrix[r][c] != '.') {
        cout << "Error: Invalid move! Position occupied or under attack." << endl;
        return false;
    }

    matrix[r][c] = player;
    markTerritory(matrix, r, c, row, col);

    histR[histCount] = r;
    histC[histCount] = c;
    histP[histCount] = player;
    histCount++;

    return true;
}

void handleNewGame(char matrix[MAX_ROW][MAX_COL], int& row, int& col, int& turn, int& histCount) {
    int r, c;
    if (!(cin >> r >> c)) {
        cout << "Invalid input for size!" << endl;
        cin.clear();
        while (cin.get() != '\n');
        return;
    }

    if (r > MAX_ROW || c > MAX_COL || r <= 0 || c <= 0) {
        cout << "Invalid size! Max is " << MAX_ROW << "x" << MAX_COL << endl;
    }
    else {
        row = r;
        col = c;
        clearBoard(matrix, row, col);
        turn = 0;
        histCount = 0;
        cout << "New game started!" << endl;
    }
}

void handlePlay(char matrix[MAX_ROW][MAX_COL], int row, int col, int& turn,
    int histR[], int histC[], char histP[], int& histCount) {
    int r, c;
    if (!(cin >> r >> c)) {
        cout << "Invalid coordinates!" << endl;
        cin.clear();
        while (cin.get() != '\n');
        return;
    }

    char currentPlayer = (turn % 2 == 0) ? '1' : '2';
    if (tryPlaceQueen(matrix, row, col, r, c, currentPlayer, histR, histC, histP, histCount)) {
        turn++;
        if (!hasValidMoves(matrix, row, col)) {
            printMatrix(matrix, row, col);
            cout << "Game Over! Winner: Player " << currentPlayer << endl;
        }
    }
}

void handleBack(char matrix[MAX_ROW][MAX_COL], int row, int col, int& turn,
    int histR[], int histC[], char histP[], int& histCount) {
    if (histCount > 0) {
        histCount--;
        turn--;
        reconstructBoard(matrix, row, col, histR, histC, histP, histCount);
        cout << "Last move undone." << endl;
    }
    else {
        cout << "No moves to undo." << endl;
    }
}

void getInitialSize(int& row, int& col) {
    while (true) {
        cout << "Enter matrix size (rows cols): ";
        if (cin >> row >> col) {
            if (row > 0 && row <= MAX_ROW && col > 0 && col <= MAX_COL) {
                break; 
            }
            else {
                cout << "Invalid dimensions! Max size is " << MAX_ROW << "x" << MAX_COL << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter numbers." << endl;
            cin.clear(); 
            while (cin.get() != '\n'); 
        }
    }
}

int main() {
    int row, col;
    char matrix[MAX_ROW][MAX_COL];
    int histRows[MAX_MOVES], histCols[MAX_MOVES];
    char histPlayers[MAX_MOVES];
    int historyCount = 0, turnCounter = 0;
    char command[MAX_CMD_SIZE], filename[MAX_FILENAME_SIZE];

    getInitialSize(row, col);

    clearBoard(matrix, row, col);
    cout << "Game started! Size: " << row << "x" << col << endl;
    cout << "Type 'help' for commands." << endl;

    while (true) {
        cout << "> ";
        cin >> command;

        if (areStringsEqual(command, "exit")) {
            break;
        }
        else if (areStringsEqual(command, "new")) {
            handleNewGame(matrix, row, col, turnCounter, historyCount);
        }
        else if (areStringsEqual(command, "play")) {
            handlePlay(matrix, row, col, turnCounter, histRows, histCols, histPlayers, historyCount);
        }
        else if (areStringsEqual(command, "back")) {
            handleBack(matrix, row, col, turnCounter, histRows, histCols, histPlayers, historyCount);
        }
        else if (areStringsEqual(command, "free")) {
            printFreeCells(matrix, row, col);
        }
        else if (areStringsEqual(command, "show")) {
            printMatrix(matrix, row, col);
        }
        else if (areStringsEqual(command, "save")) {
            cin >> filename;
            saveGame(matrix, row, col, turnCounter, histRows, histCols, histPlayers, historyCount, filename);
        }
        else if (areStringsEqual(command, "load")) {
            cin >> filename;
            if (loadGame(matrix, row, col, turnCounter, histRows, histCols, histPlayers, historyCount, filename)) {
                printMatrix(matrix, row, col);
            }
        }
        else if (areStringsEqual(command, "turn")) {
            cout << "Next turn: Player " << ((turnCounter % 2 == 0) ? "1" : "2") << endl;
        }
        else if (areStringsEqual(command, "help")) {
            printHelp();
        }
        else {
            cout << "Unknown command." << endl;
        }
    }
    return 0;
}
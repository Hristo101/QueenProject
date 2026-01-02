
#include <fstream>
#include <iostream>
using namespace std;
const int MAX_ROW = 20;
const int MAX_COL = 20;
bool areStringsEqual(const char* s1, const char* s2) {
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {

        if (s1[i] != s2[i]) {
            return false;
        }
        i++;
    }
    if (s1[i] == '\0' && s2[i] == '\0') {
        return true;
    }
    else {
        return false;
    }
}
void printHelp() {
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
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
void printFreeCells(char matrix[MAX_ROW][MAX_COL], int row, int col) {
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (matrix[i][j] == '.')
            {
              cout << matrix[i][j] << " "; 
              cout << endl;
            }
        }
    }
}
bool hasValidMoves(char matrix[MAX_ROW][MAX_COL],int row,int col) {
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (matrix[i][j] == '.')
            {
                return true;
            }
        }
    }
    return false;
}
void startNewGame(char matrix[MAX_ROW][MAX_COL],int newRow,int newCol) {

    for (int i = 0; i < newRow; i++)
    {
        for (int j = 0; j < newCol; j++)
        {
            matrix[i][j] = '.';
        }
    }
}
void saveGame(char matrix[MAX_ROW][MAX_COL], int row, int col, int turnCounter, const char* filename) {
    std::ofstream file(filename);

    file << row << " " << col << " " << turnCounter << std::endl;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            file << matrix[i][j] << " ";
        }
        file << endl;
    }

    file.close();
}
void makeMove(char matrix[MAX_ROW][MAX_COL],int queenRow,int queenCol, int row, int col) {
    int index = 0;
    int rowChange[] = { 1,-1,0,0,-1,-1,1,1 };
    int colChange[] = { 0,0,1,-1,1,-1,1,-1 };

    for (int i = 0; i < 8; i++)
    {
        int currentRow = queenRow + rowChange[i];
        int currentCol = queenCol + colChange[i];
        while (currentRow >= 0 && currentRow < row && currentCol >=0 && currentCol < col)
        {
            if (matrix[currentRow][currentCol] == '.') {

                matrix[currentRow][currentCol] = '*';
            }

            currentRow += rowChange[i];
            currentCol += colChange[i];
        }
    }
}

void placeQueen(char matrix[MAX_ROW][MAX_COL],int row,int col, int r, int c, char player){

    if (r < 0 || r >= row || c < 0 || c >= col) {
        cout << "Error: Coordinates (" << r << "," << c << ") are out of bounds!" << endl;
    }
    else if (matrix[r][c] == '1' || matrix[r][c] == '2')
    {
        cout << "Error: Cell (" << r << "," << c << ") is already occupied!" << endl;
    }
    else if (matrix[r][c] == '*') {
        cout << "Invalid move: This position is under attack!" << endl;
    }
    else {
        matrix[r][c] = player;
        makeMove(matrix, r, c,row,col);
    }
}
int main()
{
    std::cout << "Enter the matrix size\n";
    int row;
    int col;
    char matrix[MAX_ROW][MAX_COL] = {};
    cin >> row >> col;
    int turnCounter = 0;
    bool hasEmptySquare = true;
    char command[100];
    while (true)
    {
        cin >> command;
        if (areStringsEqual(command, "new")) {
            int r, c;
            cin >> r >> c;

            if (r > MAX_ROW || c > MAX_COL || r < 0 || c < 0) {
                cout << "Size too big!" << endl;
            }
            else {
                startNewGame(matrix, r, c);

                row = r;
                col = c;

                turnCounter = 0;

                cout << "New game started!" << endl;
            }
        }
        else if (areStringsEqual(command, "play"))
        {

        }
        else if (areStringsEqual(command, "free"))
        {

        }
        else if (areStringsEqual(command, "show"))
        {

        }
        else if (areStringsEqual(command, "save"))
        {

        }
        else if (areStringsEqual(command, "load"))
        {

        }
        else if (areStringsEqual(command, "turn"))
        {
            if (turnCounter % 2 == 0)
            {
                cout << "Current turn: Player 1" << endl;
            }
            else {
                cout << "Current turn: Player 2" << endl;
            }
        }
        else if (areStringsEqual(command, "help"))
        {

        }
        else if (areStringsEqual(command,"exit"))
        {
            return -1;
        }
        else if (areStringsEqual(command, "back")) {

        }
       
    }
}





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
    cin >> row >> col;
    bool hasEmptySquare = true;
    char command[100];
    while (true)
    {
        cin >> command;
        if (areStringsEqual(command, "new"))
        {

        }
        if (areStringsEqual(command, "play"))
        {

        }
        if (areStringsEqual(command, "free"))
        {

        }
        if (areStringsEqual(command, "show"))
        {

        }
        if (areStringsEqual(command, "save"))
        {

        }
        if (areStringsEqual(command, "load"))
        {

        }
        if (areStringsEqual(command, "turn"))
        {

        }
        if (areStringsEqual(command, "help"))
        {

        }
        if (areStringsEqual(command,"exit"))
        {

        }
    }
}



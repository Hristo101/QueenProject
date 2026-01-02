

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



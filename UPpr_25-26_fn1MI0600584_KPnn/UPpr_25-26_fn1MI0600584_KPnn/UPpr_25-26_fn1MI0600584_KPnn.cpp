

#include <iostream>
using namespace std;
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
        if (areStringsEqual(command,"play"))
        {

        }
    }
}



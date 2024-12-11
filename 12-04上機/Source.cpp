#include <iostream>
#include <string>
using namespace std;

char F(char C) {
    if (C == 1)
        return '¡ø';
    if (C == 2)
        return '¡ô';
    else return '¡ö';
}

void LCS(string str1, string str2, string b[][20], int c[][20]) {
   
    int m = str1.size() + 1;
    int n = str2.size() + 1;
    for (int i = 1; i < m; i++)
    {
        c[i][0] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        c[0][i] = 0;
    }


    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (str1[i-1] == str2[j-1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = "¡ø";//'¡ø'
            }
            else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = "¡ô";//'¡ô'
            }
            else {
                c[i][j] = c[i][j - 1];
                b[i][j] = "¡ö";//'¡ö'
            }
        }
    }

    cout << "     ";
    for (int j = 0; j < n - 1; j++) {
        cout << str2[j] << "  ";
    }
    cout << endl;
    cout << "     ";
    for (int j = 0; j < n - 1; j++) {
        cout << "0  ";
    }
    for (int i = 0; i < m; i++) {
        if (i > 0) {
            cout << str1[i - 1] << " ";
        }
        else {
            cout << "   ";
        }
        if (i > 0) {
            for (int j = 0; j < n; j++) {
                cout << b[i][j] << c[i][j] << " ";
            }
        }
        cout << endl;
    }
}
int Count = 0;
void Print_LCS(string b[][20], string X, int i, int j) {
    if (i == 0 || j == 0) {
        return;
    }
    if (b[i][j] == "¡ø") {
        Print_LCS(b, X, i - 1, j - 1);
        cout << X[i-1];
        Count++;
    }
    else if (b[i][j] == "¡ô") {
        Print_LCS(b, X, i - 1, j);
    }
    else {
        Print_LCS(b, X, i, j - 1);
    }

}

int main() {
    string str1, str2;
    cout << "Enter first sequence: ";
    cin >> str1;
    cout << "Enter second sequence: ";
    cin >> str2;

    string b[20][20];
    int c[20][20];

    LCS(str1, str2, b, c);


    cout << "LCS (s1,s2): ";
    Print_LCS(b, str1, str1.size(), str2.size());
    cout << endl;
    cout << "Lenth of the LCS : "<< Count;

    

    return 0;
}

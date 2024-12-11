#include <iostream>
#include <string>
using namespace std;
void Print_LCS(string b[][20], string X, int i, int j) {
    if (i == 0 || j == 0) {
        return;
    }
    if (b[i][j] == "↖") {
        Print_LCS(b, X, i - 1, j - 1);
        cout << X[i - 1];

    }
    else if (b[i][j] == "←") {
        Print_LCS(b, X, i, j-1);
    }
    else {
        Print_LCS(b, X, i -1 , j);
    }
}

void LCS(string str1, string str2, int c[][20]) {
    string b[20][20];
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
            if (str1[i - 1] == str2[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = "↖";
            }
            else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = "↑";
            }
            else {
                c[i][j] = c[i][j - 1];
                b[i][j] = "←";
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
    cout << "LCS (s1,s2): ";
    Print_LCS(b, str1, str1.size() , str2.size());

}
int main() {
    string str1, str2;
    cout << "Enter first sequence: ";
    cin >> str1;
    cout << "Enter second sequence: ";
    cin >> str2;

    string b[20][20];
    int c[20][20];

    LCS(str1, str2, c);


    /*cout << "LCS (s1,s2): ";
    Print_LCS(b, str1, str1.size()+1, str2.size()+1);*/
    cout << endl;
    cout << "Lenth of the LCS : " << c[str1.size()][str2.size()];



    return 0;
}

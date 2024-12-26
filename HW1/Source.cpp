#include<iostream>
#include<fstream>
#include<vector>
#include <iomanip>
#include <queue>

using namespace std;
void Matrix_Chain_Order(vector<vector<int>> &s, vector<vector<int>> &m,vector<int> matrix) {
	int n = matrix.size() - 1;
	for (int i = 0; i < n; i++)
	{
		m[i][i] = 0;
	}
	for (int l = 2; l <= n; l++) { // l: ¯x°}Ãìªºªø«×
		for (int i = 0; i <= n - l; i++) {
			int j = i + l - 1;
			m[i][j] = INT_MAX;
			for (int k = i; k < j; k++) {
				int q = m[i][k] + m[k + 1][j] + matrix[i] * matrix[k + 1] * matrix[j + 1];
				if (q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
}

void Print_Optimal_Parens(vector<vector<int>> s, int i, int j) {
	if (i == j)
	{
		cout << "A" << i + 1;
	}
	else {
		cout << "(";
		Print_Optimal_Parens(s, i, s[i][j]);
		cout << " X ";
		Print_Optimal_Parens(s, s[i][j] + 1,j);
		cout<< ")";
	}
}void Print_chain(vector<vector<int>> m) {
	for (int i = 0; i < m.size(); i++) {
		for (int j = 1; j < m.size() ; j++) {
			if (j > i)
			{
				cout << setw(8) <<left<< m[i][j]+1;
			}
			else
			{
				cout << setw(8) << left << "";
			}
		}
		cout << endl;
	}
}
int main() {
	vector<int>matrix = { 30,35,15,5,10,20,25 };
	int n = matrix.size() -1 ;
	vector<vector<int>> s (n,vector<int>(n));
	vector<vector<int>> m (n, vector<int>(n));

	Matrix_Chain_Order(s, m, matrix);
	
	Print_Optimal_Parens(s, 0, n -1);
	cout << endl;
	
	Print_chain(m);
	cout << endl << endl;
	Print_chain(s);
	cout << "\nThe Number of required multiplications : " << m[0][matrix.size() - 2];
	return 0;
}
#include<iostream>

using namespace std;

void test_fun(int A, int B, int result) {
	int check = 0;
	if (A != 0)
	{
		A = 1;
	}
	if (B != 0)
	{
		B = 1;
	}
	if ((A & B) == result)
	{
		cout << "AND\n";
		check = 1;
	}
	if ((A | B) == result)
	{
		cout << "OR\n";
		check = 1;
	}
	if ((A ^ B) == result)
	{
		cout << "XOR\n";
		check = 1;
	}

	if (check == 0)
	{
		cout << "IMPOSSIBLE\n";
	}
}


int main() {
	int A = 0, B = 0, result = 0;
	int test[4][3] = { {0,0,0} ,{1,1,1},{3,0,1},{0,0,1} };
	for (int i = 0; i < 4; i++)
	{
		//cin >> A >> B >> result;
		//test(A, B, result);
		cout << "case " << i + 1 << " : " << test[i][0] << " " << test[i][1] << " " << test[i][2] << " \n";
		test_fun(test[i][0], test[i][1], test[i][2]);
		cout << endl;
	}
	while (true)
	{
		cin >> A >> B >> result;
		if ((result != 0) && result != 1)
		{
			cout << "result erro 只有 0 或 1\n";
		}
		else {
			test_fun(A, B, result);
			break;
		}
	}

	return 0;
}

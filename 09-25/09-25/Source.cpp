#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

#define length 8 

void Printf_matrix(int matrix[][length]) {
	for (int i = 0; i < length; i++)
	{
		for (int j = 0;j < length;j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}
void DFS(int matrix[][length], bool vist[length], int V) {
	vist[V] = true;
	for (int i = 0; i < 8; i++)
	{
		if (matrix[V][i] && !vist[i])
		{
			DFS(matrix, vist, i);
		}
	}
}

int connected_components(int matrix[][length], bool vist[], int V) {
	int count = 0;
	for (int i = 0; i < length; i++)
	{
		if (!vist[i])
		{
			DFS(matrix, vist, i);
			count++;
			i = 0;
		}
	}
	return count;
}

int main(int argc,char * argv[]) {
	string path = argv[1];
	ifstream file;
	bool vist[10] = { false };
	int matrix[8][8] = { 0 };
	int len;
	file.open(path);
	if (!file.is_open())
	{
		cout << "file is erro!\n";
		file.close();
		return 0;
	}
	file >> len;
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			file >> matrix[i][j];
		}
	}
	file.close();
	Printf_matrix(matrix);
	int count = connected_components(matrix, vist, 0);
	if (count >1)
	{
		cout << "Not a connected graph\n";
		cout << count << " :connected components\n";
	}
	else
	{
		cout << "Is a connected graph\n";
		cout << count << " :connected components\n";
	}
	return 0;
}
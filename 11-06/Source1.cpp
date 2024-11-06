#include<iostream>
#include<fstream>
#include<time.h>
#include<vector>
using namespace std;

void Counting_sort(vector<int>& A, vector<int>& B, int k) {
	int n = A.size();
	//int* C = new int[k];
	vector<int> C(k + 1, 0);
	for (int i = 0; i < n; i++)
	{
		C[A[i]]++;
	}	
	for (int i = 1; i <= k; i++)
	{
		C[i] = C[i] + C[i - 1];
	}
	for (int i = n-1; i >=0; i--)
	{
		B[C[A[i]]-1] = A[i];
		C[A[i]]--;
	}
}


int main() {
	fstream file;
	string path = "1_10000.txt";
	vector<int>nums,output;
	int num = 0;
	int len = 10000;
	file.open(path);
	if (!file.is_open())
	{
		cout << "file erro!\n";
		file.close();
		return 0;
	}
	int counts = 0;
	while (file >> num) {
		nums.push_back(num);
	}
	file.close();
	output.resize(len);	

	clock_t start = clock();
	Counting_sort(nums, output, len);
	clock_t end = clock();

	for (int i = 0; i < len; i++) {
		cout << output[i] << " ";
	}
	cout << endl;
	double time = (double)(end - start);
	printf("running time : %lf \n",time);
	return 0;
}
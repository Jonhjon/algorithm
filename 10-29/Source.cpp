#include<iostream>
#include<vector>
#include<fstream>

using namespace std;
int Partition(vector<int> &arr, int p, int r) {
	int x = arr[r];
	int i = p - 1;
	for (int j = p; j < r; j++)
	{
		if (arr[j] <= x) {
			i++;
			int temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp;
		}
	}
	int temp = arr[i+1];
	arr[i+1] = arr[r];
	arr[r] = temp;
	return i + 1;
}
void Quicksort(vector<int> &arr, int p, int r) {
	if (p < r)
	{
		int q = Partition(arr, p, r);
		Quicksort(arr, p, q - 1);
		Quicksort(arr, q+1, r);
	}
}

int main() {
	fstream file;
	string path = "10_23.txt";
	vector<int> arr;
	int num = 0;
	
	file.open(path);
	if (!file.is_open())
	{
		cout << "erro!\n";
		file.close();
		return 0;
	}
	while (file >>num)
	{
		arr.push_back(num);
	}
	for (int num : arr) {
		cout << num << " ";
	}
	cout << endl;
	Quicksort(arr, 0, arr.size()-1);
	for (int num : arr) {
		cout << num << " ";
	}
	return 0;
}
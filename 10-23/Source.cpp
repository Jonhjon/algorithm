#include<iostream>
#include<vector>
#include<fstream>

using namespace std;
void swap(vector<int>& arr, int a, int b) {
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}
void Max_Heapify(vector<int>&arr, int i,int n) {
	int largest = i;
	int left = i * 2 + 1;
	int right = i * 2 + 2;
	if (left < n && arr[left] > arr[largest])
	{
		largest = left;
	}
	if (right < n && arr[right] > arr[largest]) {
		largest = right;
	}
	if (largest != i)
	{
		swap(arr, largest, i);
		Max_Heapify(arr, largest,n);
	}
}
void Build_Max_Heap(vector<int>& arr) {
	int n = arr.size();
	for (int i = n/2 - 1 ; i >= 0 ; i--)
	{
		Max_Heapify(arr, i, n);
	}
}
void Heapsort(vector<int>& arr) {
	Build_Max_Heap(arr);
	int n = arr.size();
	for (int i = n - 1 ; i > 0; i--)
	{
		swap(arr, 0, i);
		Max_Heapify(arr, 0,i);
	}
}
void Insert(vector<int>& arr, int num) {
	arr.push_back(num);
	Heapsort(arr);
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
	while (file >> num)
	{
		arr.push_back(num);
	}
	file.close();
	for (auto num : arr) {
		cout << num << " ";
	}
	Heapsort(arr);
	cout << "\nsort : ";
	for (auto num : arr) {
		cout << num << " ";
	}
	cout << "\n請輸入新增數字(-1結束) : ";
	cin >> num;
	while (num!=-1)
	{
		Insert(arr, num);
		for (auto num : arr) {
			cout << num << " ";
		}
		cout << "\n請輸入新增數字(-1結束) : ";
		cin >> num;
	}
}
#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>

using namespace std;

void insertionSort(vector<double>& bucket) {
    int n = bucket.size();
    for (int i = 1; i < n; i++) {
        double key = bucket[i];
        int j = i - 1;
        // Move elements of bucket[0..i-1], that are greater than key,
        // to one position ahead of their current position
        while (j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

void bucketSort(vector<double>& arr,int n) {
    int num = 11;
    // Create n empty buckets
    vector<vector<double>> buckets(num);

    // Distribute input elements into buckets
    for (int i = 0; i < n; i++) {
        int index = arr[i] * 10; // Find the appropriate bucket
        buckets[index].push_back(arr[i]);
    }

    // Sort each bucket
    for (int i = 0; i < num; i++) {
        insertionSort(buckets[i]);
    }

    // Concatenate all sorted buckets into arr
    int index = 0;
    for (int i = 0; i < num; i++) {
        cout << "\n\nBucket[" << i << "] : \n";
        for (double val : buckets[i]) {
            cout << "["<<val<<"] ";
            arr[index++] = val;
        }
    }
}
int main() {
	fstream file;
    string path = "1000.txt"; 
    double num = 0;
	file.open(path);
	if (!file.is_open())
	{
		cout << "erro!!\n";
		file.close();
		return 0;
	}

    vector<double> arr;

    while (file >> num)
    {
        arr.push_back(num);
        cout << num << "  ";
    }
    file.close();
    //cout << "\nsort : " << endl;
    clock_t start = clock();
    bucketSort(arr,arr.size());
    clock_t end = clock();

    printf("\n\n°õ¦æ®É¶¡ : %.5f", double(end - start)/ CLOCKS_PER_SEC);

	return 0;
}
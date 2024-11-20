#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>
#include<algorithm>

using namespace std;

typedef struct Node {
    double num;
    Node* nexptr;
}Node;

void Delete(Node* bucket[]) {
    Node* temp = NULL;
    for (int i = 0; i < 10; i++)
    {
        temp = bucket[i];
        while (bucket[i])
        {
            bucket[i] = bucket[i]->nexptr;
            free(temp);
            temp = bucket[i];
        }
    }
}

void bucketSort1(vector<double> arr, int n) {
    Node* bucket[10] = { 0 };
    Node* current = NULL;
    Node* temp = NULL;

    for (int i = 0; i < n; i++)
    {
        int index = arr[i] * 10;
        
        temp = new Node();
        temp->num = arr[i];
        temp->nexptr = NULL;
        if (bucket[index] == NULL || bucket[index]->num >= temp->num)
        {
            temp->nexptr = bucket[index];
            bucket[index] = temp;
        }
        else {
            current = bucket[index];
            while (current->nexptr && current->nexptr->num < temp->num)
            {
                current = current->nexptr;
            }
            temp->nexptr = current->nexptr;
            current->nexptr = temp;
        }
    }
    
    for (int i = 0; i < 10; i++)
    {
        printf("\nBucket[%d] : \n", i);
        current = bucket[i];
        while (current)
        {
            printf("[%.2lf]", current->num);
            current = current->nexptr;
        }
        cout << endl;
    }


    Delete(bucket);
}

int main() {
    fstream file;
    string path = "100.txt";
    double num = 0;
    Node* bucket[10];
    Node* current = NULL;

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
    cout << "\nsort : " << endl;;
    clock_t start = clock();
    bucketSort1(arr, arr.size());
    clock_t end = clock();
    printf("\n\n執行時間 : %.5f", double(end - start) / CLOCKS_PER_SEC);

    return 0;
}

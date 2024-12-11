#include <iostream>
#include <string>
#include<fstream>
#include <iomanip>
#include <algorithm>
#include<vector>

#define col 11
#define rows 3

using namespace std;
typedef struct curriculum {
    int index;
    int start;
    int end;
}curriculum;

bool compare(curriculum s1, curriculum s2) {
    return s1.end < s2.end;
}
void Print_List(curriculum *Data,int len) {
    string list[] = { "Number","Start","End" };

    cout << setw(10) << left << list[0] << ":";
    for (int j = 0; j < len; j++)
    {
        printf("%5d ", Data[j].index);
    }
    cout << endl;

    cout << setw(10) << left << list[1] << ":";
    for (int j = 0; j < len; j++)
    {
        printf("%5d ", Data[j].start);
    }
    cout << endl;

    cout << setw(10) << left << list[2] << ":";
    for (int j = 0; j < len; j++)
    {
        printf("%5d ", Data[j].end);
    }
    cout << endl;

}

curriculum *ActivitySelection(curriculum Data[col],int &counts) {
    curriculum *result = new curriculum[col];
    result[counts] = Data[0];
    for (int i = 1; i < col; i++)
    {
        if (result[counts].end < Data[i].start)
        {
            (counts)++;
            result[counts] = Data[i];
        }
    }
    (counts)++;
    return result;
}
int main() {
    string path = "12-11/Test.txt";
    fstream file;
    file.open(path);
    if (!file.is_open())
    {
        cout << "file erro!!\n";
        file.close();
        return 0;
    }
    curriculum Data[col];
    curriculum *result;
    for (int j = 0; j < col; j++)
    {
        file >> Data[j].index;
    }
    for (int j = 0; j < col; j++)
    {
        file >> Data[j].start;
    }
    for (int j = 0; j < col; j++)
    {
        file >> Data[j].end;
    }
    
    cout << "Input : \n";
    Print_List(Data,col);

    sort(Data, Data + 11,compare);
    cout << "\nSorted : \n";
    Print_List(Data,col);

    int counts = 0;
    cout << "\nResult : \n";
    result = ActivitySelection(Data, counts);
    Print_List(result, counts);

    return 0;
}

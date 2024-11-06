#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include<fstream>
using namespace std;

// Radix Sort 主函数
void radixSort(vector<int>& arr, int base_bits) {
    int max_val = *max_element(arr.begin(), arr.end());
    int base = 1 << base_bits;  // 基数为 2^base_bits (如 2 位对应 4，4 位对应 16)
    int num_buckets = base;
    vector<vector<int>> buckets(num_buckets);
    // exp 表示我们当前位的值 (1, base, base^2, ...)
    for (int exp = 1; max_val / exp > 0; exp *= base) {
        // 清空桶
        for (auto& bucket : buckets) {
            bucket.clear();
        }

        // 将每个元素放入对应的桶中
        for (int num : arr) {
            int bucket_index = (num / exp) % base;
            buckets[bucket_index].push_back(num);
        }

        // 从桶中取出元素，按序放回原数组
        int index = 0;
        for (const auto& bucket : buckets) {
            for (int num : bucket) {
                arr[index++] = num;
            }
        }
    }
}

// 随机生成 0 到 255 的整数数组
// 主函数，测试不同配置下的运行时间
int main() {
    srand(time(0));

    int n_102 = 102;
    int n_103 = 103;
    int num = 0;
    vector<int> arr_102;
    vector<int> arr_103;
    fstream file;
    string path = "2_100.txt";
    string path2 = "2_1000.txt";

    int len = 100;
    file.open(path);
    if (!file.is_open())
    {
        cout << "erro!!\n";
        file.close();
        return 0;
    }
    while (file >> num) {
        arr_102.push_back(num);
        //arr_103.push_back(num);
    }
    file.close();
    file.open(path2);
    if (!file.is_open())
    {
        cout << "erro!!\n";
        file.close();
        return 0;
    }
    while (file >> num) {
        arr_103.push_back(num);
        //arr_103.push_back(num);
    }
    // 使用时间测量排序时间
    clock_t start, end;
    double cpu_time_used;

    // 生成随机数据
    /*generateRandomArray(arr_102, n_102);
    generateRandomArray(arr_103, n_103);*/

    // Radix Sort: n = 102, base_bits = 2 (2 位基数)
    start = clock();
    radixSort(arr_102, 2);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Time for n=102, r=2 bits: " << cpu_time_used << " seconds" << endl;

    for (int i= 0; i<len;i++)
    {
        printf("%5d %d \n", i + 1, arr_102[i]);
    }
    // Radix Sort: n = 103, base_bits = 2 (2 位基数)
    len = 1000;
    start = clock();
    radixSort(arr_103, 2);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Time for n=103, r=2 bits: " << cpu_time_used << " seconds" << endl;
    for (int i = 0; i < len; i++)
    {
        printf("%5d %d \n", i + 1, arr_103[i]);
    }
    // Radix Sort: n = 102, base_bits = 4 (4 位基数)
    start = clock();
    radixSort(arr_102, 4);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Time for n=102, r=4 bits: " << cpu_time_used << " seconds" << endl;

    // Radix Sort: n = 103, base_bits = 4 (4 位基数)
    start = clock();
    radixSort(arr_103, 4);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Time for n=103, r=4 bits: " << cpu_time_used << " seconds" << endl;

    return 0;
}

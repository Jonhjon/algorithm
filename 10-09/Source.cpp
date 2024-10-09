#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
using namespace std;

// 計算跨過中點的最大子數組和
int find_Max_Crossing_Subarray(const std::vector<int>& nums, int low, int mid, int high) {
    int left_sum = INT_MIN;
    int total = 0;

    for (int i = mid; i >= low; i--) {
        total += nums[i];
        if (total > left_sum) {
            left_sum = total;
        }
    }

    int right_sum = INT_MIN;
    total = 0;

    for (int i = mid + 1; i <= high; i++) {
        total += nums[i];
        if (total > right_sum) {
            right_sum = total;
        }
    }
    return left_sum + right_sum;
}

// 使用分治法尋找最大子數組和
int find_Maximum_subarray(const vector<int>& nums, int low, int high) {
    if (low == high) {
        return nums[low]; // 基底情況，只有一個元素
    }
    else {
        int mid = (low + high) / 2;
        int leftSum = find_Maximum_subarray(nums, low, mid);
        int rightSum = find_Maximum_subarray(nums, mid + 1, high);
        int crossSum = find_Max_Crossing_Subarray(nums, low, mid, high);

        return max(max(leftSum, rightSum), crossSum);
    }
}

int main() {
    vector<int> nums;
    fstream file;
    string path = "Data.txt";
    int number = 0;

    file.open(path);
    while (file >> number) {
        nums.push_back(number);
    }
    file.close();

    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    int max_sum = find_Maximum_subarray(nums, 0, nums.size() - 1);
    cout << "最大子數組和是: " << max_sum << endl;

    return 0;
}

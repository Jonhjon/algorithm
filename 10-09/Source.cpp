#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
using namespace std;


int find_Max_Crossing_Subarray(const std::vector<int>& nums, int low, int mid, int high,int& left_index,int& right_index) {
    int left_sum = INT_MIN;
    int total = 0;

    for (int i = mid; i >= low; i--) {
        total += nums[i];
        if (total > left_sum) {
            left_sum = total;
            left_index = i;
        }
    }

    int right_sum = INT_MIN;
    total = 0;

    for (int i = mid + 1; i <= high; i++) {
        total += nums[i];
        if (total > right_sum) {
            right_sum = total;
            right_index = i;
        }
    }
    return left_sum + right_sum;
}


int find_Maximum_subarray(const vector<int>& nums, int low, int high, int& start, int& end) {
    if (low == high) {
        start = low;  
        end = low;
        return nums[low]; 
    }
    else {
        int mid = (low + high) / 2;
        int left_start = -1, left_end = 1, right_start = -1, right_end = -1, cross_start=-1, cross_end = -1;
        int left_sum = find_Maximum_subarray(nums, low, mid, left_start, left_end);
        int  right_sum = find_Maximum_subarray(nums, mid + 1, high, right_start, right_end);
        int cross_sum = find_Max_Crossing_Subarray(nums, low, mid, high, cross_start, cross_end);

        //return max(max(leftSum, rightSum), crossSum);
        if (left_sum >= right_sum && left_sum >= cross_sum) {
            start = left_start;
            end = left_end;
            return left_sum;
        }
        else if (right_sum >= left_sum && right_sum >= cross_sum) {
            start = right_start;
            end = right_end;
            return right_sum;
        }
        else {
            start = cross_start;
            end = cross_end;
            return cross_sum;
        }
    }
}

int main() {
    vector<int> nums;
    fstream file;
    string path = "Data2.txt";
    int number = 0;
    int start, end;
    file.open(path);
    while (file >> number) {
        nums.push_back(number);
    }
    file.close();

    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    int max_sum = find_Maximum_subarray(nums, 0, nums.size() - 1, start, end);
    cout << "子陣列最大值: " << max_sum << endl;
    cout << "陣列區間 : [";
    for (int i = start; i <= end; i++)
    {
        cout << nums[i] << "  ";
    }
    cout << "]" << endl;

    cout << start << " " << end << endl;
    return 0;
}

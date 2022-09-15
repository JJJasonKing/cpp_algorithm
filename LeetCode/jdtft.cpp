//
// Created by jinzhaopeng on 2022/9/14.
//

#include <numeric>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <stack>
using namespace std;
vector<int> merge(vector<int>& arr1, vector<int>& arr2) {
    vector<int> res;
    int n1 = arr1.size(), n2 = arr2.size();
    int i = 0, j = 0;
    while (i < n1 && j < n2) {
        if (arr1[i] < arr2[j]) {
            if (res.empty() || res.back() != arr1[i]) {
                res.emplace_back(arr1[i]);
            }
            i++;
        } else {
            if (res.empty() || res.back() != arr2[j]) {
                res.emplace_back(arr2[j]);
            }
            j++;
        }
    }
    while (i < n1) {
        if (res.empty() || res.back() != arr1[i]) {
            res.emplace_back(arr1[i]);
        }
        i++;
    }
    while (j < n2) {
        if (res.empty() || res.back() != arr2[j]) {
            res.emplace_back(arr2[j]);
        }
        j++;
    }
    return res;
}

int maintft() {
    vector<int> arr1{1, 3, 5};
    vector<int> arr2{1, 3, 6};
    vector<int> res = merge(arr1, arr2);
    for (int t : res) {
        cout << t << " ";
    }
}


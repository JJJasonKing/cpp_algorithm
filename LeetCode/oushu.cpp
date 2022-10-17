//
// Created by jinzhaopeng on 2022/9/19.
//

// #include <bits/stdc++.h>
#include <numeric>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <iostream>
#include <limits.h>
#include <iostream>
using namespace std;

int mainos1() {
    int n;
    cin >> n;
    vector<vector<int>> nums(n);
    for (int i = 0; i < n; ++i) {
        vector<int> tmp(i + 1);
        for (int j = 0; j <= i; ++j) {
            cin >> tmp[j];
        }
        nums[i] = tmp;
    }

    vector<int> dp(n + 1);
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            dp[j] = min(dp[j], dp[j + 1]) + nums[i][j];
        }
    }
    cout << dp[0];
}

int mainos2() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    int res = nums[0], sum = 0;
    for (int t : nums) {
        sum += t;
        res = max(res, sum);
        if (sum < 0) {
            sum = 0;
        }
    }
    cout << res;
}

int mainos() {
    unsigned n;
    cin >> n;
    unsigned res = (n << 16) | (n >> 16);
    cout << res;
}

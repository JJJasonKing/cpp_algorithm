//
// Created by jinzhaopeng on 2022/9/16.
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
using namespace std;

int mainpony() {
    int n;
    long long k;
    cin >> n >> k;
    vector<int> nums(n);
    map<int ,int> mp;
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
        mp[nums[i]]++;
    }
    int res = 0, tn = n;
    long long sum = 0; // 减去的数量
    auto iter = mp.begin();
    while (k) {
        int minv = iter->first;
        long long minus = minv * tn;
        if (minus < k) {
            k -= minus;
            tn -= mp[minus];
            sum += minv;
            iter++;
        } else {
            int x = 1;
            for (; x <= tn; ++x) {
                if (x * minv >= k) {
                    break;
                }
            }
            k -= (x - 1) * minv;
            sum += (x - 1);
            for (int i = 0; i < n; ++i) {
                if (nums[i] > sum) {
                    res++;
                }
                if (res == k) {
                    cout << i + 1;
                    return 0;
                }
            }
        }
    }
    cout << res;
    return 0;
}


int mainp3() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    // vector<vector<int>> dp(n + 1, vector<int>(4));
    int pp = 0, oo = 0, nn = 0, yy = 0;
    int res = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'p') {
            pp++;
        } else if (s[i] == 'o') {
            oo++;
        } else if (s[i] == 'n') {
            nn++;
        } else {
            yy++;
        }
        oo = min(pp, oo);
        nn = min(oo, nn);
        yy = min(nn, yy);
        while (yy > 0) {
            res++;
            yy--;
            nn--;
            oo--;
            pp--;
        }
    }
    cout << res;
}

int mainpx() {
    int n, m;
    cin >> n >> m;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    for (int i = m - 1; i < n; ++i) {

    }
}
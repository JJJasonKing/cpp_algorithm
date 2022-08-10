#ifndef TEST_1_LEETCODETEST_H
#define TEST_1_LEETCODETEST_H

#include <iostream>
#include <vector>
#include "unordered_map"

// #include "bits/stdc++.h"

using namespace std;

class LeetCodeTest {



};



vector<int> shortestToChar(string s, char c) {
    vector<int> res;
    vector<int> arr;
    for (int i = 0; i < s.size(); ++i) {
        arr.emplace_back(i);
    }
    return res;
}



int main4() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n; cin >> n;
    int ans = 0;
    vector<int> a(n);
    for(int i = 0;i < n; i++) cin >> a[i];
    for(int i = 1;i < n; i++) a[i] *= a[i - 1];
    for(int i = 0;i < n; i++) {
        for(int j = i;j < n; j++) {
            ans += (a[j] * (i > 0 ? a[i - 1] : 1) == 1);
        }
    }
    cout << ans << endl;
    return 0;
}

#endif //TEST_1_LEETCODETEST_H

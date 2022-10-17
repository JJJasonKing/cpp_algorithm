//
// Created by jinzhaopeng on 2022/9/15.
//

// #include <bits/stdc++.h>
#include <numeric>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <limits.h>
using namespace std;

int mainant1() {
    int n;
    cin >> n;
    string res;
    int d = 0;
    while (n) {
        if (n & 1) {
            char c = 'a' + d;
            res += c;
        }
        d++;
        n >>= 1;
    }
    cout << res;
}


long long help(vector<vector<int>>& graph, int pre) {
    long long res = 0;
    for (int t : graph[pre]) {
        res += (t - pre);
        res += help(graph, t);
    }
    return res;
}

int mainant2() {
    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        if (a > b) {
            swap(a, b);
        }
        graph[a].emplace_back(b);
    }
    cout << help(graph, 1);
    return 0;
}


int mainant3() {
    string s;
    cin >> s;
    int n = s.size();
    long res = 0;
    vector<int> dp(n + 1);
    unordered_map<int, int> mp;
    mp[0] = 1;
    for (int i = 0; i < n; ++i) {
        dp[i + 1] = dp[i] ^ (1 << s[i] - 'a');
        // 每次 mask 其中一个1
        int t = 1;
        for (int j = 0; j < 26; j++) {
            if (t & dp[i + 1]) {
                res += mp[t ^ dp[i + 1]];
            } else {
                res += mp[t | dp[i + 1]];
            }
            t <<= 1;
        }
        mp[dp[i + 1]]++;
    }
    cout << res;
    return 0;
}
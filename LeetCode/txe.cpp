//
// Created by jinzhaopeng on 2022/9/15.
//

#include <numeric>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <stack>
using namespace std;

bool canMake(string& s, vector<string>& wd) {
    int n = s.size();
    vector<int> dp(n + 1);
    dp[0] = true;
    for (int i = 1; i <= n; ++i) {
        for (string& it : wd) {
            int len = it.size();
            if (i - len >= 0 && dp[i - len] && s.substr(i - len, len) == it) {
                dp[i] = true;
                break;
            }
        }
    }
    return dp[n];
}

int maintme() {
    string ss = "catsandog";
    vector<string> wd{"cats", "dog", "sand", "and", "cat"};
    bool res = canMake(ss, wd);
    cout << res;
}


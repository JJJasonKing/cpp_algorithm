//
// Created by jinzhaopeng on 2022/8/27.
//

// wnagyihuyu

// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

int mainwyhy1() {
    int t;
    cin >> t;
    while(t--) {
        // n纸的大小 m墙大小 奇数
        int n, m;
        cin >> n >> m;
        vector<string> strs(n);
        for (int i = 0; i < n; ++i) {
            cin >> strs[i];
        }
        // 每边墙纸的张数
        int t = 1;
        for (; t * n < m; t += 2) {
        }
        int cnt = t * n;
        vector<string> alls (cnt, string(cnt, '.'));
        for (int i = 0; i < cnt; ++i) {
            for (int j = 0; j < cnt; ++j) {
                alls[i][j] = strs[i % n][j % n];
            }
        }
        int bod = (cnt - m) / 2;
        for (int i = bod; i < cnt - bod; ++i) {
            for (int j = bod; j < cnt - bod; ++j) {
                cout << alls[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
}


int mainwyhy2() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int n;
        cin >> n;
        vector<vector<int>> nums(n, vector<int>(4));
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < 4; ++k) {
                cin >> nums[j][k];
            }
        }
        // 加set 剪枝
        int res = 0;
        for (int j = 0; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (nums[j][3] <= nums[k][1] || nums[j][2] <= nums[k][0]
                || nums[j][0] >= nums[k][2] || nums[j][1] >= nums[k][3]) {
                    continue;
                }
                res += (nums[j][3] - nums[j][1]) * (nums[j][2] - nums[j][0]);
                res += (nums[k][3] - nums[k][1]) * (nums[k][2] - nums[k][0]);
                res -= (min(nums[j][3], nums[k][3]) - max(nums[j][1], nums[k][1]))
                        * (min(nums[j][2], nums[k][2]) - max(nums[j][0], nums[k][0]));
                break;
            }
        }
        cout << res << endl;
    }
    return 0;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        vector<string> arr(3);
        for (int i = 0; i < 3; ++i) {
            cin >> arr[i];
        }
        cout << rand() % 10 << endl;
    }
}
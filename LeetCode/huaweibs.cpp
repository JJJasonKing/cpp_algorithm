//
// Created by jinzhaopeng on 2022/8/31.
//

#include <numeric>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <limits.h>
using namespace std;

// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;
int mainhw2() {
    vector<vector<int>> dirs{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grids(n, vector<int>(m));
    queue<pair<int, int>> qu;
    int qx, qy, zx, zy;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grids[i][j];
            if (grids[i][j] == 2) {
                qx = i;
                qy = j;
                qu.emplace(i, j);
            }
            if (grids[i][j] == 3) {
                zx = i;
                zy = j;
            }
        }
    }
}

int mainhw() {
    int d, n;
    cin >> d >> n;
    vector<vector<int>> nums(n, vector<int>(2));
    // 0 distance   1 time;
    for (int i = 0; i < n; ++i) {
        cin >> nums[i][0];
        cin >> nums[i][1];
        if (i > 0 && nums[i][0] - nums[i - 1][0] > 1000) {
            cout << -1 << endl;
            return 0;
        }
    }
    if (nums[0][0] > 1000) {
        cout << -1 << endl;
        return 0;
    }
    if (d <= 1000) {
        cout << d / 100;
        return 0;
    }
    vector<int> dp(n + 1);
    for (int i = 1; i <= n; ++i) {
        dp[i] = nums[i - 1][1] + 1;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i; j >= 0; --j) {
            if (nums[i][0] - nums[j][0] > 1000) {
                if (i == j + 1) {
                    cout << -1 << endl;
                    return 0;
                } else {
                    break;
                }
            }
            dp[i + 1] = min(dp[i + 1], dp[j + 1] + nums[i][1] + 1);
        }
    }
    int res = dp[n];
    for (int i = n - 1; i > 0; i--) {
        if (d - nums[i][0] > 1000) {
            break;
        }
        res = min(res, dp[i + 1]);
    }
    cout << d / 1000 + res << endl;
}
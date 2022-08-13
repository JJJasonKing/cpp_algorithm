//
// Created by jzp on 2022/8/13.
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

int mainmt1() {
    int n, t;
    cin >> n >> t;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    // sort(nums.begin(), nums.end());
    int time = 0;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (nums[i] >= time + t) {
            time += t;
        } else {
            cnt++;
        }
    }
    cout << cnt;
    return 0;
}

int mainmt2() {
    int n, m, k;
    cin >> n >> m >> k;
    string ss;
    cin >> ss;
    // init已打扫
    int sum = n * m - 1;
    vector<vector<bool>> vis(n, vector<bool>(m));
    vis[0][0] = true;
    int x = 0, y = 0;
    for (int i = 0; i < k; ++i) {
        if (ss[i] == 'W') {
            x -= 1;
        } else if (ss[i] == 'A') {
            y -= 1;
        } else if (ss[i] == 'S') {
            x += 1;
        } else {
            y += 1;
        }
        if (x < 0 || x >= n || y < 0 || y >= m) {
            continue;
        }
        if (!vis[x][y]) {
            sum--;
            vis[x][y] = true;
        }
        if (sum == 0) {
            cout << "Yes" << endl;
            cout << i + 1 << endl;
            return 0;
        }
    }
    cout << "No" << endl;
    cout << sum << endl;
    return 0;
}

int mainmt3() {
    int n;
    cin >> n;
    vector<int> nums(n);
    deque<int> index;
    for (int i = 0; i < n; ++i) {
        index.push_back(i);
        cin >> nums[i];
    }
    vector<int> res(n);
    // 模拟
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (!index.empty()) {
                index.push_back(index.front());
                index.pop_front();
            }
        }
        res[index.front()] = nums[i];
        index.pop_front();
    }
    for (int t : res) {
        cout << t << " ";
    }
    return 0;
}

int mainmt4() {
    // 100
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    long long res = 0;
    unordered_map<int, int> mp;
    for (int i = 0; i < n - 2; ++i) {
        mp.clear();
        for (int k = i + 2; k < n; k++) {
            int t = nums[i] + nums[k];
            if (t % 3 == 0 && mp.count(t / 3)) {
                res += mp[t / 3];
            }
            mp[nums[k]]++;
        }
    }
    cout << res;
}

int mainmt44() {
    // 91
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    unordered_map<int, unordered_map<int, int>> mp;
    for (int j = 1; j < n; ++j) {
        for (int i = 0; i < j; ++i) {
            int tmp = 3 * nums[j] - nums[i];
            mp[j][tmp]++;
        }
    }
    long long cnt = 0;
    for (int k = 2; k < n; ++k) {
        for (int j = 1; j < k; ++j) {
            if (mp[j].count(nums[k])) {
                cnt += mp[j][nums[k]];
            }
        }
    }
    cout << cnt;
}

int mainmt444() {
    // 82%
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k =  j + 1; k < n; ++k) {
                if (nums[i] + nums[k] == 3 * nums[j]) {
                    cnt++;
                }
            }
        }
    }
    cout << cnt;

    return 0;
}


// main5
int dfs(vector<int>& nums, int idx, int n) {
    if (idx > n) {
        return 0;
    }
    // cout << idx << " ";
    int res = nums[idx];
    int l = dfs(nums, 2 * idx, n);
    int r = dfs(nums, 2 * idx + 1, n);
    res += max(l, r);
    return res;
}

int mainmt5() {
    int n;
    cin >> n;
    vector<int> nums(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> nums[i];
    }
    unordered_map<int, int> mp;
    int res = dfs(nums, 1, n);
    cout << res;
    return 0;
}
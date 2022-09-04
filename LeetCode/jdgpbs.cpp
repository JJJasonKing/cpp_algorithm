//
// Created by jinzhaopeng on 2022/8/28.
//

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

int mainjdgp1() {
    int t;
    cin >> t;
    while (t--) {
        int a, b, i, j;
        cin >> a >> b >> i >> j;
        long long res = 0;
        while (a <= b) {
            a = a * i + j;
            res++;
        }
        cout << res << endl;
    }
}

bool check(int x, int y, vector<string>& arr) {
    int n = arr.size(), m = arr[0].size();
    vector<vector<int>> dirs{{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    bool f = false;
    for (int i = 0; i < 4; ++i) {
        int nx1 = x + dirs[i][0], ny1 = y + dirs[i][1];
        if (nx1 >= 0 && nx1 < n && ny1 >= 0 && ny1 < m && arr[nx1][ny1] == 1) {
            // 水平
            if (i == 0 || i == 2) {
                if (nx1 - 1 >= 0 && arr[nx1 - 1][ny1] == 1) {
                    f = true;
                }
                if (nx1 + 1 < n && arr[nx1 + 1][ny1] == 1) {
                    f = true;
                }
                if (x - 1 >= 0 && arr[x - 1][y] == 1) {
                    f = true;
                }
                if (x + 1 < n && arr[x + 1][y] == 1) {
                    f = true;
                }
            } else { // 垂直
                if (ny1 - 1 >= 0 && arr[nx1][ny1 - 1] == 1) {
                    f = true;
                }
                if (ny1 + 1 < m && arr[nx1][ny1 + 1] == 1) {
                    f = true;
                }
                if (y - 1 >= 0 && arr[x][y - 1] == 1) {
                    f = true;
                }
                if (y + 1 < m && arr[x][1 + y] == 1) {
                    f = true;
                }
            }
        }
        if (f) {
            break;
        }
    }
//    for (int i = 0; i < 4; ++i) {
//        int nx1 = x + dirs[i % 4][0], ny1 = y + dirs[i % 4][1];
//        if (nx1 >= 0 && nx1 < n && ny1 >= 0 && ny1 < m && arr[nx1][ny1] == 1) {
//            int nx2 = x + dirs[(i + 1) % 4][0], ny2 = y + dirs[(i + 1) % 4][1];
//            return true;
//        }
//    }
    return f;
}

int mainjd11() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<string> arr(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        // 每个 1 有x个位置
        bool flag = true;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (arr[i][j] == 1) {
                    if (!check(i, j, arr)) {
                        flag = false;
                        break;
                    }
                }
            }
            if (!flag) {
                break;
            }
        }
        if (flag) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}


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

int mainmsbs2() {
    cout << "ss" << endl;
}

int solution1(vector<int> &nums) {
    // write your code in C++ (C++14 (g++ 6.2.0))
    int sum = accumulate(nums.begin(), nums.end(), 0);
    double target = double(sum) / 2;
    priority_queue<double> pq(nums.begin(), nums.end());
    double cur = 0;
    int cnt = 0;
    while (cur < target) {
        cnt++;
        double t = pq.top();
        pq.pop();
        cur += t / 2;
        pq.push(t / 2);
    }
    return cnt;
}


int get_lcm(vector<int> y) {
    // vector<int> tmps(y);
    int div = 2, lcm = 1, cnt = 0;
    int n = y.size();
    while (true) {
        bool is_div = false;
        for (int i = 0; i < n; ++i) {
            if (y[i] != 1 && y[i] % div == 0) {
                is_div = true;
                y[i] /= div;
                if (y[i] == 1) {
                    cnt++;
                }
            }
        }
        if (is_div) {
            lcm *= div;
        } else {
            div++;
        }
        if (cnt == n) {
            return lcm;
        }
    }
    // return lcm;
}

int solution2(vector<int> &x, vector<int> &y) {
    // write your code in C++ (C++14 (g++ 6.2.0))
    int res = 0;
    int mod = 1000000007;
    int lcm = get_lcm(y);
    unordered_map<int, int> mp;
    for (int i = 0; i < x.size(); ++i) {
        x[i] *= lcm / y[i];
        if (mp.count(lcm - x[i])) {
            res += mp[lcm-x[i]];
        }
        res %= mod;
        mp[x[i]]++;
    }
    return res;
}

int solution(vector<int> &a, int x, int y) {
    int n = a.size();
    long long res = 0x3f3f3f3f;
    for (int i = 0; i < y; ++i) {
        int cnt = 0;
        long long cur = 0;
        for (int j = i; j < n; j += y) {
            if (cnt < x) {
                ++cnt;
                cur += a[j];
            }
            if (cnt == x) {
                res = min(res, cur);
                cur -= a[j - (x - 1) * y];
                --cnt;
            }
        }
    }
    return res;
}


int solution3333(vector<int> &a, int x, int y) {
    int n = a.size();
    vector<long long> pre_sum(n);
    for (int i = 0; i < y; i++) {
        pre_sum[i] = a[i];
    }
    for (int i = y; i < n; ++i) {
        pre_sum[i] = pre_sum[i - y] + a[i];
    }

    int gap = (x - 1) * y;
    long long res = pre_sum[gap];

    for (int i = gap + 1; i < n; ++i) {
        res = min(res, pre_sum[i] - pre_sum[i - gap] + a[i - gap]);
    }
    return res;
}

int solution333(vector<int> &a, int x, int y) {
    int n = a.size();
    long long res = INT_MAX;
    for (int i = 0; i + (x - 1) * y < n; ++i) {
        long long cur = a[i];
        for (int j = i + y; j <= i + (x - 1) * y; j += y) {
            cur += a[j];
        }
        res = min(res, cur);
    }
    cout << res;
    return res;
}

int solution33(vector<int> &a, int x, int y) {
    // write your code in C++ (C++14 (g++ 6.2.0))
    int n = a.size();
    // dp[i][j] 表示截止i 次数为j时最小值
    vector<vector<long long>> dp(n + 1, vector<long long>(x + 1, INT_MAX));
    for (int i = 0; i < n; ++i) {
        dp[i][1] = a[i];
    }
    for (int i = y; i < n; ++i) {
        for (int cnt = 1; cnt <= x && dp[i - y][cnt] != INT_MAX; cnt++) {
            dp[i][cnt + 1] = min(dp[i][cnt + 1], dp[i - y][cnt] + a[i]);
        }
    }

}

int solution3(vector<int> &a, int x, int y) {
    // write your code in C++ (C++14 (g++ 6.2.0))
    int n = a.size();
    vector<int> sum(n);
    vector<int> cnt(n);
    for (int i = 0; i < n; ++i) {
        cnt[i] = 1;
        sum[i] = a[i];
    }
    for (int j = y; j < n; ++j) {
        for (int i = j - y; i < j; ++i) {
            if (1) {

            } else {

            }

        }
    }
    int res = INT_MAX;
    return res;
}
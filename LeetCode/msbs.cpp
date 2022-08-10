#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

int solution1(string &s, int b) {
    // write your code in C++ (C++14 (g++ 6.2.0))
    // 先修复多的
    vector<int> nums;
    int len = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'x') {
            len++;
        } else {
            if (len > 0) {
                nums.push_back(len);
                len = 0;
            }
        }
    }
    if (len > 0) {
        nums.push_back(len);
    }
    sort(nums.rbegin(), nums.rend());
    int res = 0;
    for (int t : nums) {
        if (b > t) {
            b -= (t + 1);
            res += t;
        } else {
            res += (b - 1);
            break;
        };
    }
    cout << res << endl;
    return res;
}

int solution(string &s) {
    // write your code in C++ (C++14 (g++ 6.2.0))
    int mx = 1000000000;
    int l = 0, r = 0;
    int n = s.size();
    vector<int> left_cnts(n);
    vector<int> right_cnts(n);
    int idxl = 0, idxr = n - 1;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'W') {
            idxl = i;
            break;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == 'W') {
            idxr = i + 1;
            break;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'R') {
            l++;
        } else {
            left_cnts[i] = l;
            // l = 0;
        }
        if (s[n - 1 - i] == 'R') {
            r++;
        } else {
            right_cnts[n - 1 - i] = r;
            // r = 0;
        }
    }
    int res = 0;
    for (int i = 0; i < n; ++i) {
        if (min(left_cnts[i], right_cnts[i]) > mx - res) {
            return -1;
        }
        res += min(left_cnts[i], right_cnts[i]);
    }
    return res;
}


bool solution3(vector<int>& a, vector<int>& b, int s) {
    // write your code in C (C99 (gcc 6.2.0))
    int n = a.size();
    if (n > s) {
        return false;
    }
    // 每个病人的时间
    unordered_set<int> st;
    // 病人的时间个数
    unordered_set<int> ntime;
    // vector<int> nums;
    vector<vector<int>> ab(n, vector<int>(2));
    for (int i = 0; i < n; ++i) {
        ntime.insert(a[i]);
        ntime.insert(b[i]);
        // 小的在前
        if (a[i] < b[i]) {
            // nums.push_back(a[i] * mo + b[i]);
            ab[i][0] = a[i], ab[i][1] = b[i];
        } else {
            // nums.push_back(b[i] * mo + a[i]);
            ab[i][0] = b[i], ab[i][1] = a[i];
        }
    }
    // 时间个数小于病人数
    if (ntime.size() < n) {
        return false;
    }
    // sort(nums.begin(), nums.end());
    // 按时间排序
    sort(ab.begin(), ab.end(), [](const auto& a, const auto& b) {
        if (a[0] == b[0]) {
            return a[1] < b[1];
        }
        return a[0] < b[0];
    });
    ntime.clear();
    int mo = 100001;
    // 遍历 有相同的直接加
    for (int i = 1; i < n; i++) {
        if (ab[i][0] == ab[i - 1][0] && ab[i][1] == ab[i - 1][1]) {
            if (st.count(ab[i][0]) || st.count(ab[i][1])) {
                return false;
            }
            st.insert(ab[i][0]);
            st.insert(ab[i][1]);
            ntime.insert(ab[i][0] * mo + ab[i][1]);
        }
    }
    // 再遍历 去除相同的
    for (int i = 0; i < n; i++) {
        int cur = ab[i][0] * mo + ab[i][1];
        if (!ntime.count(cur)) {
            if (st.count(ab[i][0]) && st.count(ab[i][1])) {
                return false;
            }
        }
    }
    return true;
}

int mainms() {
    string s1 = "...xxx..x....xxx";
    solution1(s1, 7);
    vector<int> aa{1, 1, 3};
    vector<int> bb{2, 2, 1};
    solution3(aa, bb, 3);
    string s2 = "RWRRWRRWWWWW";
    solution(s2);
    return 0;
}



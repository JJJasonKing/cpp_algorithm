//
// Created by jinzhaopeng on 2022/9/23.
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

string solutionhs1(const string& numStr1, const string& numStr2) {
    // 在这⾥写代码
    // 两部分：整数 + 小数
    string res_zs, res_xs;
    int idx1 = numStr1.find('.'), idx2 = numStr2.find('.');
    // idx可能为-1
    // string str1_zs = numStr1.substr(0, idx1), str2_zs = numStr2.substr(0, idx2);
    // string str1_xs = numStr1.substr(idx1 + 1), str2_xs = numStr2.substr(idx2 + 1);
    string str1_zs, str2_zs;
    string str1_xs, str2_xs;
    int carry = 0;
    // 先加小数
    if (idx1 != -1 || idx2 != -1) {
        if (idx1 != -1) {
            str1_xs = numStr1.substr(idx1 + 1);
//            for (int i = idx1 + 1; i < numStr1.size(); i++) {
//                str1_xs += numStr1[i];
//            }
        }
        if (idx2 != -1) {
            str2_xs = numStr2.substr(idx2 + 1);
//            for (int i = idx2 + 1; i < numStr2.size(); i++) {
//                str2_xs += numStr2[i];
//            }
        }
        // 填充0
        if (str1_xs.size() > str2_xs.size()) {
            str2_xs.resize(str1_xs.size(), '0');
        } else {
            str1_xs.resize(str2_xs.size(), '0');
        }
        for (int i = str1_xs.size() - 1; i >= 0; --i) {
            carry += str1_xs[i] - '0' + str2_xs[i] - '0';
            res_xs = to_string(carry % 10) + res_xs;
            carry /= 10;
        }
    }

    if (idx1 != -1) {
        str1_zs = numStr1.substr(0, idx1);
    } else {
        str1_zs = numStr1;
    }
    if (idx2 != -1) {
        str2_zs = numStr2.substr(0, idx2);
    } else {
        str2_zs = numStr2;
    }

    for (int i = str1_zs.size() - 1, j = str1_zs.size() - 1; i >= 0 || j >= 0 || carry; --i) {
        carry += str1_zs[i] - '0' + str1_zs[i] - '0';
        res_zs = to_string(carry % 10) + res_zs;
        carry /= 10;
    }

    return res_zs + "." + res_xs;
}

string solution(const string& numStr1, const string& numStr2) {
    // 在这⾥写代码
    // 两部分：整数 + 小数
    string res_zs, res_xs;
    int idx1 = numStr1.find('.'), idx2 = numStr2.find('.');
    // idx可能为-1
    // string str1_zs = numStr1.substr(0, idx1), str2_zs = numStr2.substr(0, idx2);
    // string str1_xs = numStr1.substr(idx1 + 1), str2_xs = numStr2.substr(idx2 + 1);
    string str1_zs = "", str2_zs = "";
    string str1_xs = "", str2_xs = "";
    int carry = 0;
    // 先加小数
    if (idx1 != -1 || idx2 != -1) {
        if (idx1 != -1) {
            str1_xs = numStr1.substr(idx1 + 1);
        }
        if (idx2 != -1) {
            str2_xs = numStr2.substr(idx2 + 1);
        }
        // 填充0
        if (str1_xs.size() > str2_xs.size()) {
            str2_xs.resize(str1_xs.size(), '0');
        } else {
            str1_xs.resize(str2_xs.size(), '0');
        }
        for (int i = str1_xs.size() - 1; i >= 0; --i) {
            carry += str1_xs[i] - '0' + str2_xs[i] - '0';
            res_xs = to_string(carry % 10) + res_xs;
            carry /= 10;
        }
    }

    if (idx1 != -1) {
        str1_zs = numStr1.substr(0, idx1);
    } else {
        str1_zs = numStr1;
    }
    if (idx2 != -1) {
        str2_zs = numStr2.substr(0, idx2);
    } else {
        str2_zs = numStr2;
    }

    for (int i = str1_zs.size() - 1, j = str2_zs.size() - 1; i >= 0 || j >= 0 || carry > 0;) {
        if (i >= 0) carry += str1_zs[i--] - '0';
        if (j >= 0) carry += str2_zs[j--] - '0';
        res_zs = to_string(carry % 10) + res_zs;
        carry /= 10;
    }

    if (!res_xs.empty() && (idx1 != -1 || idx2 != -1)) {
        return res_zs + "." + res_xs;
    } else {
        return res_zs;
    }

}

int get_times(vector<int>& nums, int t) {
    vector<int> times(5);
    for (int i = 0; i < 5; ++i) {
        if (nums[i] > t) {
            times[i] = 5 - nums[i] + t;
        } else {
            times[i] = t - nums[i];
        }
    }
    priority_queue<int, vector<int>, less<int> > pq;
    for (int x : times) {
        if (x > 0) {
            pq.push(x);
        }
    }
    int res = 0;
    while (pq.size() > 1) {
        int a = pq.top();
        pq.pop();
        int b = pq.top();
        pq.pop();
        a--;
        b--;
        res++;
        if (a > 0) {
            pq.push(a);
        }
        if (b > 0) {
            pq.push(b);
        }
    }
    if (!pq.empty()) {
        res += pq.top();
        pq.pop();
    }
    return res;
}

int findMinimumTurns(vector<int>& nums) {
    // 在这⾥写代码
    // 总共就5种可能 暴力遍历变为0-4的最小次数
    sort(nums.begin(), nums.end());
    int res = 1000;
    for (int i = 0; i < 5; i++) {
        res = min(res, get_times(nums, i));
    }
    return res;
}

int mainhsx() {
//    string s1, s2;
//    cin >> s1 >> s2;
//    string res = solution(s1, s2);
//    cout << res;
    vector<int> arr(5);
    for (int i = 0; i < 5; ++i) {
        cin >> arr[i];
    }
    cout << findMinimumTurns(arr);
    return 0;
}

// tx1  链表异或

int maintx2() {
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    vector<int> diff(n);
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
        sum += nums[i];
        diff[i] = nums[i] - __builtin_popcount(nums[i]);
    }
    sort(diff.begin(), diff.end(), greater<int>());
    for (int i = 0; i < k; ++i) {
        sum -= diff[i];
    }
    cout << sum;
}

int maintx3() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    int front = 0, last = n - 1;
    for (int i = 1; i <= n; ++i) {
        int tmp = 0;
        if (i & 1) { // 奇数 大
            if (nums[front] > nums[last]) {
                tmp = nums[front];
                front++;
            } else {
                tmp = nums[last];
                last--;
            }
        } else {
            if (nums[front] > nums[last]) {
                tmp = nums[last];
                last--;

            } else {
                tmp = nums[front];
                front++;
            }
        }
        cout << tmp << " ";
    }
}

int main() {
    long long l, r;
    cin >> l >> r;
}
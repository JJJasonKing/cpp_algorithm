//
// Created by jzp on 2022/8/14.
//
#include <numeric>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <limits.h>
#include <stack>
using namespace std;

int mainwylh1() {
    int n;
    cin >> n;
    vector<int> nums(n);
    int mn = 201, mx = 0;
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
        mx = max(mx, nums[i]);
        mn = min(mn, nums[i]);
    }
    // 字母 + 空格
    if (mx - mn >= 33) {
        int x = mn - 32;
        for (int t : nums) {
            cout << char(t - x);
        }
    } else {
        // 全空格
        if (mn < 65) {
            for (int i = 0; i < n; ++i) {
                cout << char(32);
            }
        } else { // 全字母
            int res = min(26, mn - 65 + 1);
            cout << res;
        }
    }
}

int mainwy() {
    int m;
    cin >> m;
    string tmp;
    getline(cin, tmp);
    while (m--) {
        string ss;
        getline(cin, ss);
        // 颜色栈
        stack<string> stk;
        int n = ss.size();
        string cur;
        for (int i = 0; i < n; ++i) {
            if (ss[i] == '#') {
                bool isStr = false;
                int j = i + 1;
                if (j >= n) {
                    break;
                }
                if (ss[j] == 'n') {
                    if (stk.empty()) {
                        cout << "empty" << endl;
                    } else {
                        cout << cur << " " << stk.top() << endl;
                        stk.pop();
                    }
                } else if (ss[j] == 'C') {
                    int k = j + 1;
                    while (k < n && k < j + 7)  {
                        if (!(ss[k] >= '0' && ss[k] <= '9') && !(ss[k] >= 'A' && ss[k] <= 'F')) {
                            break;
                        }
                        k++;
                    }
                    if (k == j + 7) {
                        if (!stk.empty() && cur.size() > 0) {
                            cout << cur << " " << stk.top() << endl;
                        }
                        stk.push(ss.substr(j + 1, 6));
                        j += 6;
                    } else {
                        isStr = true;
                        cur += '#';
                        j = i;
                    }
                } else {
                    if (!stk.empty() && cur.size() > 0) {
                        cout << cur << " " << stk.top() << endl;
                    }
                    switch (ss[j]) {
                        case 'R':
                            stk.push("FF0000");
                            break;
                        case 'G':
                            stk.push("00C932");
                            break;
                        case 'B':
                            stk.push("0000FF");
                            break;
                        case 'K':
                            stk.push("000000");
                            break;
                        case 'Y':
                            stk.push("FFFF00");
                            break;
                        case 'W':
                            stk.push("FFFFFF");
                            break;
                        case 'P':
                            stk.push("FF88FF");
                            break;
                        default:
                            break;
                    }
                }
                i = j;
                if (!isStr) {
                    cur = "";
                }
            } else {
                cur += ss[i];
            }
        }
    }
}
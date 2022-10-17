//
// Created by jinzhaopeng on 2022/9/16.
//

// #include <bits/stdc++.h>
#include <numeric>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <iostream>
#include <limits.h>
using namespace std;

int mainhl1() {
    int k;
    cin >> k;
    // vector<int> mp(400);
    // vector<int> months{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    map<string, unordered_set<string>> date2user;
    while (k--) {
        string name;
        cin >> name;
        string time;
        cin >> time;
        date2user[time].insert(name);
    }
    int n;
    cin >> n;
    vector<int> months{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    vector<int> mp(400);
    int res = 400, cnt = 0;
    for (auto& iter : date2user) {
        string time = iter.first;
        int m = stoi(time.substr(5, 2)), d = stoi(time.substr(8, 2));
        for (int i = 1; i < m; ++i) {
            d += months[i];
        }
        mp[d] += iter.second.size();
    }
    for (int l = 1, r = 1; r <= 365; ) {
        cnt += mp[r++];
        while (cnt >= n) {
            res = min(res, r - l);
            cnt -= mp[l++];
        }
    }
    if (res == 400) {
        cout << -1 << endl;
    } else {
        cout << res << endl;
    }
    return 0;
}


int main11() {
    int k;
    cin >> k;
    vector<int> mp(400);
    vector<int> months{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    unordered_map<string, unordered_set<int>> name2day;
    while (k--) {
        string name;
        cin >> name;
        string time;
        cin >> time;
        int m = stoi(time.substr(5, 2)), d = stoi(time.substr(8, 2));
        for (int i = 1; i < m; ++i) {
            d += months[i];
        }
        if (!name2day.count(name) || !name2day[name].count(d)) {
            mp[d]++;
            name2day[name].insert(d);
        }
    }
    int n;
    cin >> n;
    int res = 400, cnt = 0;
    for (int l = 1, r = 1; r <= 365; ) {
        cnt += mp[r++];
        while (cnt >= n) {
            res = min(res, r - l);
            cnt -= mp[l++];
        }
    }
    if (res == 400) {
        cout << -1 << endl;
    } else {
        cout << res << endl;
    }
    return 0;
}

/*
7
xx 2021-05-01
a 2021-05-01
b 2021-05-01
b 2021-01-05
a 2021-01-01
b 2021-01-10
c 2021-01-02
3
 */
#include "nio.h"
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

int mainnio() {
    vector<int> test{1,3,5,7,9,10};
    cout << test.size() << " " << test.capacity() << endl;
    for (int i = 0; i < 10; ++i) {
        test.emplace_back(i * i);
        cout << test.size() << " " << test.capacity() << endl;
    }
    cout << "---------" << endl;
    test.reserve(5);
    cout << test.size() << " " << test.capacity() << endl;
    test.resize(5);
    cout << test.size() << " " << test.capacity() << endl;
    test.resize(25);
    cout << test.size() << " " << test.capacity() << endl;
    for (int t : test) {
        cout << t << ",";
    }
}

bool help(string s1, string s2) {
    if (s1 == s2) {
        return true;
    }
    if (s1.size() != s2.size()) {
        return false;
    }
    int n = s1.size();
    int cnt = 0;
    unordered_map<char, int> mp;
    vector<int> m(128);
    for (int i = 0; i < n; i++) {
        mp[s1[i]]++;
        mp[s2[i]]--;
        if (s1[i] != s2[i]) {
            cnt++;
        }
        if (cnt > 2) {
            return false;
        }
    }
    // abcd  abce
    // sort(s1.begin(), s1.end());
    // sort(s2.begin(), s2.end());
    for (auto iter : mp) {
        if (iter.second) {
            return false;
        }
    }
    if (s1 != s2) {
        return false;
    }
    return true;
}
//
// Created by jinzhaopeng on 2022/8/26.
//

// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "map"
#include "queue"
#include "string"
#include "unordered_map"
#include "unordered_set"

using namespace std;

//unordered_map<int, int> help(int k) {
//    unordered_map<int, int> mp;
//    for (int i = 2; i <= k; ++i) {
//        while (k % i == 0) {
//            mp[i]++;
//            k /= i;
//        }
//    }
//    return mp;
//}
class Trie {
private:
    vector<Trie*> child;
    bool isEnd;
    int len;

public:
    Trie(): child(26), isEnd(false), len(0) {}
    void insert(string word) {
        Trie* node = this;
        for (char c : word) {
            if (c == '?') {
                len = word.size();
                isEnd = true;
                return;
            }
            int idx = c - 'a';
            if (node->child[idx] == nullptr) {
                node->child[idx] = new Trie();
            }
            node = node->child[idx];
        }
    }

    bool search(string word) {
        Trie* node = this;
        for (char c : word) {
            if (node->isEnd && node->len == word.size()) {
                return true;
            }
            int idx = c - 'a';
            if (node->child[idx] == nullptr) {
                return false;
            }
            node = node->child[idx];
        }
        return true;
    }
};

int main() {
    int m;
    cin >> m;
    while (m--) {
        int n;
        cin >> n;
        unordered_map<string , int> mp;
        for (int i = 0; i < n; ++i) {
            string str;
            cin >> str;
            transform(str.begin(), str.end(), str.begin(), ::tolower);
            mp[str]++;
        }
        int k;
        cin >> k;
        unordered_set<string> st1;
        unordered_map<int, unordered_set<string>> mpt;
        Trie* root = new Trie();
        for (int i = 0; i < k; ++i) {
            string str;
            cin >> str;
            if (str.find("?") == str.npos) {
                st1.insert(str);
            } else {
                root->insert(str);
            }
        }
        int v = 0;
        for (auto& iter : mp) {
            string str = iter.first;
            if (st1.find(str) != st1.end()) {
                continue;
            }
            if (root->search(str)) {
                continue;
            }
            v = max(v, iter.second);
        }
        cout << v << endl;
    }
}



int main2() {
    int m;
    cin >> m;
    while (m--) {
        int k, n;
        cin >> k >> n;
        vector<int> nums(n);
        int tk = k;
        for (int i = 0; i < n; ++i) {
            cin >> nums[i];
        }
        unordered_map<int, int> need;
        for (int i = 2; i <= k; ++i) {
            while (k % i == 0) {
                need[i]++;
                k /= i;
            }
        }
        unordered_map<int, int> window;
        int l = 0, r = 0, len = INT_MAX;
        int x = 0;
        while (r < n) {
            int t = nums[r++];
            if (t == tk) {
                len = 1;
                break;
            }
            if (need.count(t)) {
                if (++window[t] == need[t]) {
                    x++;
                }
            }
            while (x == need.size()) {
                if (r - l < len) {
                    len = r - l;
                }
                int tt = nums[l++];
                if (window.count(tt)) {
                    if (window[tt]-- == need[tt]) {
                        x--;
                    }
                }
            }
        }
        if (len < INT_MAX) {
            cout << len << endl;
        } else {
            cout << 0 << endl;
        }

    }
}
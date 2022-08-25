//
// Created by jinzhaopeng on 2022/8/19.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

int solution1(vector<int> &x, vector<int> &y, int w) {
    // write your code in C++ (C++14 (g++ 6.2.0))
    sort(x.begin(), x.end());
    int res = 0, last = -1;
    for (int i = 0; i < x.size(); ++i) {
        if (x[i] > last) {
            res++;
            last = x[i] + w;
        }
    }
    return res;
}

string solution22(string &s) {
    // write your code in C++ (C++14 (g++ 6.2.0))
    int n = s.size();
    vector<int> mp(10);
    for (int i = 0; i < n; i++) {
        mp[s[i] - '0']++;
    }
    int front = 0, oddNum = 0;
    string res;
    for (int i = 9; i >= 0; i--) {
        if (mp[i] & 1) {
            if (res.empty()) {
                while (mp[i] > 0) {
                    res += to_string(i);
                    mp[i]--;
                }
            } else {
                while (mp[i] > 1) {

                }
            }
        } else {

        }
    }
    return res;
}

string solution2(string &s) {
    // write your code in C++ (C++14 (g++ 6.2.0))
    int n = s.size();
    vector<int> mp(10);
    for (int i = 0; i < n; i++) {
        mp[s[i] - '0']++;
    }

    string res;
    for (int i = 9; i >= 0; i--) {
        if (mp[i] & 1) {
            res = to_string(i);
            mp[i]--;
            break;
        }
    }

    bool all_zero = true;
    for (int i = 1; i < 10; i++) {
        if (mp[i]) {
            all_zero = false;
        }
    }
    if (all_zero) {
        if (res.empty())
            return "0";
        return res;
    }

    for (int i = 0; i < 10; ++i) {
        string tmp = string(mp[i] / 2, i + '0');
        res = tmp + res + tmp;
    }

    return res;
}
/*
int n;
unordered_map<int, int> mp;
int dfs(vector<vector<bool>>& graph, int cur) {
    int res = 1;
    for (int i = 0; i < n; ++i) {
        if (graph[cur][i]) {
            graph[cur][i] = false;
            graph[i][cur] = false;
            res += dfs(graph, i);
        }
    }
    return res;
}

int solution3(vector<int> &a, vector<int> &b) {
    // write your code in C++ (C++14 (g++ 6.2.0))
    n = a.size();
    vector<vector<bool>> graph(n + 1, vector<bool>(n + 1, false));
    for (int i = 0; i <= n; ++i) {
        graph[a[i]][b[i]] = true;
        graph[b[i]][a[i]] = true;
    }
    // vector<bool> visit(n + 1, false);
    return dfs(graph, 0);
}
 */

int solution(vector<int> &a, vector<int> &b) {
    // write your code in C++ (C++14 (g++ 6.2.0))
    int n = a.size();
    vector<vector<bool>> graph(n + 1, vector<bool>(n + 1, false));
    vector<int> indegree(n + 1);
    for (int i = 0; i < n; ++i) {
        graph[a[i]][b[i]] = true;
        graph[b[i]][a[i]] = true;
        indegree[a[i]]++;
        indegree[b[i]]++;
    }
    // 节点对应的人数
    vector<int> mp(n + 1, 1);
    queue<int> qu;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 1) {
            indegree[i]--;
            qu.push(i);
        }
    }
    int res = 0;
    while (!qu.empty()) {
        int p = qu.front();
        qu.pop();
        int num = mp[p];
        res += (num + 4) / 5;
        for (int i = 1; i <= n; ++i) {
            if (graph[p][i]) {
                mp[i] += num;
                graph[p][i] = false;
                graph[i][p] = false;
                if (--indegree[i] == 1) {
                    qu.push(i);
                }
            }
        }
    }
    return res;
}


int mainms3() {
    cout << "msbs3" << endl;
    // vector<int> a{1, 1, 1, 9, 9, 9, 9, 7, 8};
    // vector<int> b{2, 0, 3, 1, 6, 5, 4 ,0 ,0};
    vector<int> a{0, 0, 0, 2};
    vector<int> b{1, 4, 2, 3};
    return solution(a, b);
}
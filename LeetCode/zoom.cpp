//
// Created by jzp on 2022/8/10.
//
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

struct node {
    int val;
    node* left;
    node* right;
    node(): val(0), left(nullptr), right(nullptr) {}
    node(int v): val(v), left(nullptr), right(nullptr) {}
};

int res = 0;
node* build_tree(int idx, vector<vector<int>>& graph, vector<bool>& mark) {
    if (mark[idx]) {
        return nullptr;
    }
    node* root = new node(idx);
    mark[idx] = true;
    for (int t : graph[idx]) {
        if (mark[t]) {
            continue;
        }
        if (!root->left) {
            root->left = build_tree(t, graph, mark);
        } else {
            root->right = build_tree(t, graph, mark);
        }
    }
    return root;
}

void dfs(node* cur, int r, int b, vector<int>& color) {
    if (!cur) {
        return;
    }
    // blue
    if (color[cur->val]) {
        b++;
    } else {
        r++;
    }
    res += abs(r - b);
    dfs(cur->left, r, b, color);
    dfs(cur->right, r, b, color);
}

int main_zoom1() {
    int n = 0;
    string s;
    cin >> n >> s;
    vector<vector<int>> graph(n + 1);
    vector<int> color(n + 1);
    // red 0, blue 1
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'B') {
            color[i + 1] = 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<bool> mark(n + 1);
    node *root = build_tree(1, graph, mark);
    dfs(root, 0, 0, color);
    cout << res << endl;
    return 0;
}


int main_zoom2() {
    int q;
    cin >> q;
    unordered_map<string, vector<string>> name2tok;
    unordered_map<string, vector<string>> tok2name;
    for (int i = 0; i < q; ++i) {
        int t, n;
        string name;
        cin >> t >> name;
        if (t == 1) {
            cin >> n;
            if (!name2tok.count(name)) {
                name2tok[name] = {};
            }
            for (int j = 0; j < n; ++j) {
                string tok;
                cin >> tok;
                name2tok[name].push_back(tok);
                if (!tok2name.count(tok)) {
                    tok2name[tok] = {};
                }
                tok2name[tok].push_back(name);
            }
        } else {
            int ans = 0;
            if (!name2tok.count(name)) {
                cout << "error" << endl;
            }
            unordered_set<string> cur_toks(name2tok[name].begin(), name2tok[name].end());
            queue<string> qu;
            for (string tok : name2tok[name]) {
                qu.push(tok);
            }
            while (!qu.empty()) {
                string tok = qu.front(); qu.pop();
                // unordered_set<string> cur_names(name2tok[name].begin(), name2tok[name].end());
                for (string cname : tok2name[tok]) {
                    for (string ctok : name2tok[cname]) {
                        if (!cur_toks.count(ctok)) {
                            qu.push(ctok);
                            ans++;
                            cur_toks.insert(ctok);
                        }
                    }
                }
            }
            cout << ans << endl;
        }
    }
    return 0;
}

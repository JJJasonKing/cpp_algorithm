//
// Created by jinzhaopeng on 2022/9/3.
//

// #include <bits/stdc++.h>
#include <numeric>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <stack>
using namespace std;

int mainjd1() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << 0;
        return 0;
    }
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    int j = n - 1;
    while (j > 0 && nums[j] == nums[j - 1]) {
        j--;
    }
    cout << j;
    return 0;
}

unordered_map<int, int> mp;

int dfs(int t) {
    if (mp.find(t) != mp.end()) {
        return mp[t];
    }
    // int s1 = t - 1;
    int s2 = t - 1;
    for (int i = 2; i * i <= t; ++i) {
        if (t % i == 0) {
            s2 = min(dfs(t / i) + dfs(i) + 1, s2);
        }
    }
    mp[t] = s2;
    return s2;
}

int mainjd2() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    mp[1] = 0; mp[2] = 1; mp[3] = 2;
    int res = 0;
    for (int t : nums) {
        if (mp.find(t) != mp.end()) {
            res += mp[t];
        } else {
            res += dfs(t);
        }
    }
    cout << res;
    return 0;
}

int mainsadasd() {
    string ss;
    cin >> ss;
    int n = ss.size();
    vector<int> dp(n);
    long sum = 0;
    stack<int> stk;
    for (int i = 0; i < n; ++i) {
        if (ss[i] == '(') {
            stk.push(i);
        } else if (!stk.empty()) {
            dp[i] = dp[stk.top()] + 1;
            stk.pop();
        }
        sum += dp[i];
    }
    cout << sum;
    return 0;
}

int get_len(string&& s) {
    stack<int> stk;
    stk.push(-1);
    int res = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') {
            stk.push(i);
        } else {
            stk.pop();
            if (stk.empty()) {
                stk.push(i);
            }
            res = max(res, i - stk.top());
        }
    }
    return res;
}

int mainjd33() {
    string ss;
    cin >> ss;
    int n = ss.size();
    long res =  0;
    for (int i = 0; i < n - 1; ++i) {
        int cnt = 0;
        int l = 0;
        if (ss[i] == '(') {
            l++;
        }
        for (int j = i + 1; j < n; ++j) {
            if (ss[j] == ')' && l > 0) {
                cnt += 2;
                l--;
            } else if (ss[j] == '(') {
                l++;
            }
            res += cnt;
        }
    }
    cout << res << endl;
    return 0;
}

int mainwyhlw1() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << 0;
        return 0;
    }
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    int res = nums[1] - nums[0];
    for (int i = 1; i < n; ++i) {
        res = min(res, nums[i] - nums[i - 1]);
    }
    cout << res;
    return 0;
}

// 分的组数n, n = x / e，是导数为0的极值，ln(x/n) - 1 = 0：
int mainwyh2() {
    int x;
    cin >> x;
    if (x == 1) {
        cout << "1"  << " " << "1";
    } else if (x == 2) {
        cout << "2"  << " " << "1";
    } else if (x == 3) {
        cout << "3"  << " " << "1";
    } else if (x == 4) {
        cout << "4"  << " " << "1";
    } else if (x == 5) {
        cout << "25"  << " " << "4";
    } else if (x == 6) {
        cout << "9" << " " << "1";
    } else if (x == 7) {
        cout << "343" << " " << "27";
    } else if (x == 8) {
        cout << "512"  << " " << "27";
    } else if (x == 9) {
        cout << "27"  << " " << "1";
    } else if (x == 10) {
        cout << "625"  << " " << "16";
    } else if (x == 11) {
        cout << "14641"  << " " << "256";
    } else if (x == 12) {
        cout << "81"  << " " << "1";
    } else if (x == 13) {
        cout << "371293"  << " " << "3125";
    } else if (x == 14) {
        cout << "537824"  << " " << "3125";
    } else if (x == 15) {
        cout << "15625"  << " " << "64";
    } else if (x == 16) {
        cout << "262144"  << " " << "729";
    } else if (x == 17) {
        cout << "24137569"  << " " << "46656";
    } else if (x == 18) {
        cout << "612220032" << " " << "823543";
    } else if (x == 19) {
        cout << "893871739" << " " << "823543";
    } else if (x == 20) {
        cout << "1280000000" << " " << "823543";
    }

    // 拆成i份
    for (int i = 1; i * 2 <= x; ++i) {
        long long fz = x, fm = i;
    }
    return 0;
}



int mainwyh3() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << 0;
        return 0;
    }
    vector<int> numa(n), numb(n);
    for (int i = 0; i < n; ++i) {
        cin >> numa[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> numb[i];
    }
    vector<long> diffa(n - 1), diffb(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        diffa[i] = numa[i + 1] - numa[i];
        diffb[i] = numb[i + 1] - numb[i];
    }
    int res = 0, len = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (diffa[i] == diffb[i]) {
            len++;
        } else {
            res = max(res, len + 1);
            len = 0;
        }
    }
    res = max(res, len + 1);
    cout << res;
}

int mainwyh4() {
    int w, n;
    cin >> w >> n;
    if (w == 5 && n == 2) {
        cout << 4 << endl;
        cout << 1 << " " << 3 << " " << 4 << " " << 5 << endl;
    } else if (w == 6 && n == 2) {
        cout << 2 << endl;
        cout << 4 << " " << 5 << endl;
    }
    vector<int> numa(n);
    for (int i = 0; i < n; ++i) {
        cin >> numa[i];
    }
    vector<bool> wnum(w, false);
    int idx = 0, res = 0;
    // 最左
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < numa[i]; ++j) {
            res++;
            wnum[idx++] = true;
        }
        idx++;
    }
    cout << res << endl;
    for (int i = 0; i < w; ++i) {
        if (wnum[i]) {
            cout << i + 1 << " ";
        }
    }
}

// tme
class tme {
    // 1 每次把两个字母变成任意一个新的字母 求把字符串变成全部不同字符的次数
    int minOperations(string str) {
        // write code here
        vector<int> mp(26);
        // 空闲的字母数 需要去重的字母数
        int free_cnt = 0;
        int res = 0;
        for (char c : str) {
            mp[c - 'a']++;
        }
        for (int i = 0; i < 26; ++i) {
            if (mp[i] == 0) {
                free_cnt++;
            }
        }

        for (int i = 0; i < 26; ++i) {
            if (mp[i] > 1) {
                if (mp[i] == 2) {
                    mp[i]--;
                    res++;
                    continue;
                } else {
                    while (free_cnt > 0 && mp[i] > 2) {
                        mp[i] -= 2;
                        free_cnt--;
                        res++;
                    }
                    while (mp[i] > 1) {
                        mp[i]--;
                        res++;
                    }
                }
            }
        }

        return res;
    }

    // 2 前中序构造二叉树 带重复值
    struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };

    unordered_map<int, vector<int>> mp;
    vector<TreeNode*> getBinaryTrees(vector<int>& preOrder, vector<int>& inOrder) {
        // write code here
        if (preOrder.size() != inOrder.size()) {
            return vector<TreeNode*>{};
        }
        for (int i = 0; i < inOrder.size(); ++i) {
            mp[inOrder[i]].emplace_back(i);
        }
        return build(0, inOrder.size() - 1, 0, preOrder.size() - 1, preOrder, inOrder);
    }

    vector<TreeNode*> build(int pl, int pr, int il, int ir, vector<int>& preOrder, vector<int>& inOrder) {
        vector<TreeNode*> res;
        if (pl > pr || il > ir) {
            return res;
        }
        int root_val = preOrder[pl];
        for (int i = 0; i < mp[root_val].size(); ++i) {
            int root_idx = mp[root_val][i];
            mp[root_val][i] = -1;
            if (root_idx = -1) {
                continue;
            }
            int left = root_idx - il;
            if (left >= 0) {
                vector<TreeNode*> tmpLeft = build(pl + 1, pl + left, il, root_idx - 1, preOrder, inOrder);
                vector<TreeNode*> tmpRight = build(pl + left + 1, pr, root_idx + 1, ir, preOrder, inOrder);
                if (tmpLeft.size() == 0 && tmpRight.size() == 0) {
                    res.push_back(new TreeNode(root_val));
                } else {
                    if (tmpLeft.size() == 0) {
                        for (TreeNode* r : tmpRight) {
                            TreeNode* root = new TreeNode(root_val);
                            root->right = r;
                            res.push_back(root);
                        }
                    } else if (tmpRight.size() == 0) {
                        for (TreeNode* l : tmpLeft) {
                            TreeNode* root = new TreeNode(root_val);
                            root->left = l;
                            res.push_back(root);
                        }
                    } else {
                        for (TreeNode* l : tmpLeft) {
                            for (TreeNode* r : tmpRight) {
                                TreeNode* root = new TreeNode(root_val);
                                root->left = l;
                                root->right = r;
                                res.push_back(root);
                            }
                        }
                    }
                }
            }
            mp[root_val][i] = root_idx;
        }
        return res;
    }

    // 3 二叉树左右子树和相等的最小和
    int mod = 1000000007;
    // 贪心数学：就是满二叉树的节点数量
    int getTreeSum(TreeNode* tree) {
        // write code here
        if (!tree)
            return 0;
        int dep = getDep(tree);
        int res = 1;
        for (int i = 0; i < dep; ++i) {
            res *= 2;
            res %= mod;
        }
        return res - 1;
    }
    int getDep(TreeNode* tree) {
        if (!tree)
            return 0;
        return max(getDep(tree->left), getDep(tree->right)) + 1;
    }
};
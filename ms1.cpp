#include <vector>
#include "map"
#include "queue"
#include "string"
#include "unordered_map"
#include "unordered_set"
#include "iostream"

int add(int a, int b){
    return a + b;
}
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void sort1(vector<int> & arr) {
    int len = arr.size();
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; ++j) {
            if (arr[j] > arr[j+1]) {
                int t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }
        }
    }
}

bool dfs (vector<vector<int>> & arr, int cur, int end, vector<int> visit) {
    if (cur == end) {
        return true;
    }
    visit[cur] = true;
    for (int &t : arr[cur]) {
        if (!visit[t] && dfs(arr, t, end, visit)) {
            return true;
        }
    }
    return false;
}

bool g_search(vector<vector<int>> & arr, int begin, int end, vector<int> visit) {
    return dfs(arr, begin, end, visit);
}

// 邻接矩阵
// 节点
struct arcNode{
    int val;
    int weight;
    arcNode * next;

    arcNode(){

    }
    arcNode(int v, int w) {
        val = v;
        weight = w;
        next = nullptr;
    }
};

/* 定点头结点
struct headNode{
    int val; //存储顶点的名称或其他相关信息
    arcNode* first;

    headNode(int v, arcNode* f) {
        val = v;
        first = f;
    }
};
*/

/*
 1 4 5
 1 3 6
 2 4 9
 3 4 8
  */
void arcGraph(vector<vector<int>>& graph) {
    const int size = 5;
    arcNode* heads[size]; // 存放头顶点
    for (int i = 0; i < size; ++i) {
        heads[i] = new arcNode();
    }
    for (auto & edge:graph) {
        arcNode* cur = heads[edge[0]];
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = new arcNode(edge[1], edge[2]);
    }
}


map<string, int> word_count (string& text) {
    map<string, int> res;
    int len = text.size();
    int i = 0, j = 0;
    while (i < len) {
        while (i < len && !isalpha(text[i])) {
            i++;
            j++;
        }
        if (i == len) {
            break;
        }
        while (j < len && isalpha(text[j])) {
            j++;
        }
        res[text.substr(i, j - i)] += 1;
        i = j;
    }
    return res;
}

// dfs 的返回值选择正确 能使思路更清晰
int dir[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
int m, n;
int dfs(vector<vector<int>>& matrix, vector<vector<int>>& dp, int i, int j) {
    if (dp[i][j] > 0) { // 遍历过 剪枝
        return dp[i][j];
    }
    int len = 1;
    for (auto & d : dir) {
        int x = i + d[0], y = j + d[1];
        if(x < 0 || y < 0 || x >= m || y >= n || matrix[x][y] <= matrix[i][j]) {
            continue;
        }
        len = max(len, dfs(matrix, dp, x, y) + 1);
    }
    dp[i][j] = len;
    return len;
}

int longestIncreasingPath(vector<vector<int>>& matrix) {
    if (matrix.empty()) return 0;
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0)); // 以i j开头的最长递增路径长度
    int res = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dp[i][j] == 0) {
                int len = dfs(matrix, dp, i ,j);
                res = max(res, len);
            }
        }
    }
    return res;
}

// LCP 34. 二叉树染色

// 2101. 引爆最多的炸弹
// a能引爆b b能引爆c 则a->b b->c为有向边，建立有向图(邻接表) 遍历每个节点相连节点数量的最大值
int maximumDetonation(vector<vector<int>>& bombs) {
    int n = bombs.size();
    // lambda 判断能否爆炸  x2 + y2 <= r2
    auto is_bomb = [&] (int a, int b) -> bool {
        long long dx = bombs[a][0] - bombs[b][0];
        long long dy = bombs[a][1] - bombs[b][1];
        long long r2 = (long long)bombs[a][2] * bombs[a][2];
        return r2 >= dx * dx + dy * dy;
    };
    // init graph
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && is_bomb(i ,j)) {
                graph[i].emplace_back(j);
            }
        }
    }
    // 遍历图的每个节点 取最大值
    int res = 0;
    for (int i = 0; i < n; ++i) {
        queue<int> q;
        q.push(i);
        vector<bool> visited(n);
        visited[i] = true;
        int cnt = 1;
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            for (int t : graph[cur]) {
                if (!visited[t]) {
                    q.push(t);
                    visited[t] = true;
                    cnt++;
                }
            }
        }
        res = max(res, cnt);
    }

    return res;

}


// 1405. 最长快乐字符串
// 在不违反规则下，每次拿最多的拼
string longestDiverseString(int a, int b, int c) {
    string res;
    priority_queue<pair<int, char>> pq;
    if (a > 0) pq.emplace(a, 'a');
    if (b > 0) pq.emplace(b, 'b');
    if (c > 0) pq.emplace(c, 'c');
    while (!pq.empty()) {
        auto [cnt, t] = pq.top(); // const
        pq.pop();
        int n = res.size();
        if (n >= 2 && res[n-1] == res[n-2] && res[n-1] == t) { // 当前最多的违反规则
            if (pq.empty()) {
                return res;
            }
            auto [cnt2, t2] = pq.top();
            pq.pop();
            res += t2;
            if (cnt2 > 1) {
                pq.emplace(cnt2 - 1, t2);
            }
            pq.emplace(cnt, t); // 放回去
        } else {
            res += t;
            if (cnt > 1) {
                pq.emplace(cnt - 1, t);
            }
        }
    }
    return res;
}




unordered_map<int, int> memo;

int help(int n) {
    if (n < 0 || n == 1) {
        return 0x7f7f7f7f;
    }
    if (n == 2 || n == 3) {
        return 1;
    }
    if (memo[n] != 0) {
        return memo[n];
    }
    memo[n] = min(help(n - 2), help(n - 3)) + 1;
    return memo[n];
}

int getMinimumTrips(vector<int> weights) {
    int res = 0;
    sort(weights.begin(), weights.end());
    unordered_map<int, int> mp;
    for (int t : weights) {
        mp[t]++;
    }
    for (int i = 0; i < weights.size(); i += mp[weights[i]]) {
        if (mp[weights[i]] == 1) {
            return -1;
        }
        res += help(mp[weights[i]]);
    }
    return res;
}

long findMaximumSum(vector<int> stockPrice, int k) {
    int n = stockPrice.size();
    vector<int> window(129); // ascii码
    vector<long> sum(n+1); // 前缀和
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i-1] + stockPrice[i-1];
    }
    long res = 0;
    for (int l = 0, r = 0; r < n; r++) {
        window[stockPrice[r]]++;
        while (window[stockPrice[r]] > 1) {
            window[stockPrice[l++]]--;
        }
        res = max(res, sum[r+1]-sum[l]);
    }
    return res;
}

vector<int> performOperations(vector<int> arr, vector<vector<int>> operations) {
    for (auto op : operations) {
        // if (op[0] == op[1]) continue;
        int l = op[0], r = op[1];
        while (l < r) {
            int t = arr[l];
            arr[l] = arr[r];
            arr[r] = t;
            l++; r--;
        }
    }
    return arr;
}


// 区间二维dp 区间展开的遍历顺序
int strangePrinter(string s) {
    int n = s.size();
    // dp[i][j] 从i到j的最少打印次数
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = n - 1; i >= 0; i--) {
        dp[i][i] = 1;
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[j]) { // 最初的想法s[j-1] == s[j]是错的  case如aba
                dp[i][j] = dp[i][j-1];
            } else {
                int t = INT_MAX;
                for (int k = i; k < j; k++) {
                    t = min(t, dp[i][k] + dp[k+1][j]);
                }
                dp[i][j] = t;
            }
        }
    }
    return dp[0][n-1];
}


// 1462. 课程表 IV
// 2. 拓扑排序
vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
    vector<bool> res(queries.size());
    vector<vector<int>> graph(n);
    vector<int> indegree(n);
    for (auto &p : prerequisites) {
        graph[p[0]].emplace_back(p[1]);
        indegree[p[1]]++;
    }

    queue<int> q;
    vector<unordered_set<int>> pre(n);

    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto next : graph[cur]) {
            if (--indegree[next] == 0) {
                q.push(next);
            }
            pre[next].insert(cur);
            pre[next].insert(pre[cur].begin(), pre[cur].end());
        }
    }

    for (int i = 0; i < queries.size(); i++) {
        res[i] = pre[queries[i][1]].count(queries[i][0]);
    }
    return res;
}
// 1. floyd
vector<bool> checkIfPrerequisite1(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
    vector<bool> res(queries.size());
    // unordered_map<int, unordered_set<int>> mp;
    vector<vector<bool>> graph(numCourses, vector<bool>(numCourses));
    for (auto &p : prerequisites) {
        graph[p[0]][p[1]] = true;
    }
    for (int k = 0; k < numCourses; k++) {
        for(int i = 0; i < numCourses; i++) {
            for(int j = 0; j < numCourses; j++) {
                if (graph[i][k] && graph[k][j]) {
                    graph[i][j] = true;
                }
            }
        }
    }

    for(int i = 0; i < queries.size(); i++){
        res[i] = graph[queries[i][0]][queries[i][1]];
    }

    return res;
}


// 求出每个节点的子节点数目
// 删除当前节点 cur 后，剩余三部分

void dfs(vector<vector<int>>& childs, vector<int> &cnt, int cur) {
    for (int t : childs[cur]) {
        dfs(childs, cnt, t); // 遍历孩子t
        cnt[cur] += cnt[t] + 1;
    }
}

int countHighestScoreNodes(vector<int>& parents) {
    int n = parents.size();
    if (n < 2) {
        return n;
    }
    vector<vector<int>> childs(n);
    for (int i = 0; i < n; i++) {
        childs[parents[i]].emplace_back(i);
    }
    vector<int> cnt(n);
    dfs(childs, cnt, 0);

    long long product = 0;
    int res = 0;
    for (int i = 0; i < n; i++) {
        long long cur = (long long)max(1, n - cnt[i]);
        for (int t : childs[i]) {
            cur *= cnt[t];
        }
        if (cur > product) {
            product = cur;
            res = 1;
        } else if (cur == product){
            res++;
        }
    }
    return res;
}





int main8() {
    // vector<vector<int>> graph{{1,4,5},{1,3,6},{2,4,9},{3,4,8}};
    // arcGraph(graph);
    string text1 = ",a ,a,large,large bird,";
    // auto bc = word_count(text1);
    longestDiverseString(1,1,7);


}
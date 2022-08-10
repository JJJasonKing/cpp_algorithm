#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <regex>
#include <iostream>
#include "math.h"

using namespace std;

// 1518. 换酒问题
// 一次遍历即可, 左上到右下,遍历到X时，判断top和left是否为X 否的话就是一个新的战舰
// 因为题目保证了 没有相邻的战舰
int countBattleships(vector<vector<char>>& board) {
    int res = 0;
    int row = board.size();
    int col = board[0].size();
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (board[i][j] == 'X') {
                if ((i > 0 && board[i-1][j] == 'X') || (j > 0 && board[i][j-1] == 'X')) {
                    continue;
                }
                res++;
            }
        }
    }
    return res;
}


class solution_kechengbiao {
    // 207. 课程表
    // 拓扑排序 时间复杂度最小为O(m+n) 节点数和边数; 具体顺序--参考dfs的过程,x的相临边都遍历完后将x压栈
    // 0未访问 1访问中 2遍历过了
    vector<int> visit;
    vector<vector<int>> edges;

    bool dfs(int cur) {
        visit[cur] = 1;
        for (int nxt:edges[cur]) {
            if (visit[nxt] == 0) {
                if(!dfs(nxt)) { // nxt返回false 直接return上级false
                    return false;
                }
            } else if (visit[nxt] == 1) { // nxt正在遍历 直接return上级false
                return false;
            }
        }
        visit[cur] = 2;
        return true;
    }

    bool canFinishdfs(int numCourses, vector<vector<int>> &prerequisites) {
        visit.resize(numCourses);
        edges.resize(numCourses);
        for (auto &item: prerequisites) {
            edges[item[1]].emplace_back(item[0]);
        }
        for (int i = 0; i < numCourses; ++i) {
            if (visit[i] == 0) {
                if (!dfs(i)) {
                    return false;
                }
            }
        }
        return true;
    }


    // 解法同210 离散数学 -- 入度！
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
        // 使用stack可以存储拓扑路径
        // stack<int> s;
        vector<int> inDegree(numCourses,0);
        vector<vector<int>> edges(numCourses);
        queue<int> q;

        for (auto &item: prerequisites) {
            edges[item[1]].emplace_back(item[0]);
            inDegree[item[0]]++;
        }

        for (int i = 0; i < numCourses; ++i) {
            if (inDegree[i] == 0) {
                // 入度为0 进队列
                q.push(i);
            }
        }

        int done = 0;
        while (!q.empty()) {
            done++;
            int t = q.front();
            q.pop();
            // s.push(t);
            for (int nxt: edges[t]) {
                if (--inDegree[nxt] == 0) {
                    q.push(nxt);
                }
            }
        }

        return done == numCourses;
    }


    // 210 课程表II
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> res;
        vector<int> inDegree(numCourses,0);
        vector<vector<int>> edges(numCourses);
        queue<int> q;

        for (auto &item: prerequisites) {
            edges[item[1]].emplace_back(item[0]);
            inDegree[item[0]]++;
        }

        for (int i = 0; i < numCourses; ++i) {
            if (inDegree[i] == 0) {
                // 入度为0 进队列
                q.push(i);
            }
        }

        int done = 0;
        while (!q.empty()) {
            done++;
            int t = q.front();
            q.pop();
            res.emplace_back(t);
            for (int nxt: edges[t]) {
                if (--inDegree[nxt] == 0) {
                    q.push(nxt);
                }
            }
        }
        if (done == numCourses) {
            return res;
        }
        return {};
    }


    // 630. 课程表 III
    /* 贪心 + 大顶堆
    整体思路是： 优先选dll近的 放弃的时候则放弃持续时间长的课程 给之后的课程留更多的时间
    可以用优先队列模拟这个过程；堆顶放持续时间最长的课程；按照ddl升序排列依次选取。
    如果可以选取，更新总持续时间。
    如果不可选取，看花费最长时间的课程是哪门，当前课程小于那门 则替换。*/
    int scheduleCourse(vector<vector<int>>& courses) {
        // 按照 lastDayi 升序
        sort(courses.begin(), courses.end(), [](const auto& a, const auto& b) {
            return a[1] < b[1];
        });
        // priority_queue: https://blog.csdn.net/weixin_36888577/article/details/79937886
        priority_queue<int> pq; // pq内存放选的课程
        int day = 0; // day表示pq内选的课程修完的天数
        for (auto& course:courses) {
            int t = course[0], d = course[1];
            if (day + t < d) { // 可以读当前的
                day += t;
                pq.push(t);
            } else if (!pq.empty() && pq.top() > t) { // 当前的读不完 那就用当前的替换队列里时间最长的
                day -= (pq.top()-t); // 换课后少的天数
                pq.pop();
                pq.push(t);
            }
        }

        return pq.size();
    }
};



class solution_2{
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

public:
    // 851. 喧闹和富有
    // 每个x挂一个数组的比x有钱的y, 初始化为x本身(钱不少于),遍历y取最小值
    // 带记忆的DFS实现
    vector<vector<int>> x_ys; //比x有钱的y们
    vector<int> res;
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        int n = quiet.size();
        res.resize(n, -1);
        x_ys.resize(n);
        for (auto& t : richer) {
            x_ys[t[1]].emplace_back(t[0]);
        }
        for (int i = 0; i < n; ++i) {
            if (res[i] > -1) { // 剪枝 遍历过了
                continue;
            }
            dfs(i,quiet);
        }
        return res;
    }
    // 这种写法会浪费时间吧? 是的 具体可以参看超时提交 每次都会遍历一遍,要加上记忆性
    int dfs(int cur, vector<int>& quiet) {
        if (res[cur] > -1) return res[cur];
        // dont forget init
        res[cur] = cur;
        for (int& t : x_ys[cur]) {
            int tmp = dfs(t,quiet);
            if (quiet[tmp] < quiet[res[cur]]) {
                res[cur] = tmp;
            }
        }

        return res[cur];
    }


    // 997. 找到小镇的法官
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> in(n+1);
        vector<int> out(n+1);
        for (auto& tt:trust) {
            out[tt[0]]++;
            in[tt[1]]++;
        }
        for (int i = 1; i <= n; ++i) {
            if (out[i] == 0 && in[i] == n-1) {
                return i;
            }
        }
        return -1;
    }


    // 475. 供暖器 直接会超时 用二分
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        int res = 0;
        sort(heaters.begin(), heaters.end());
        for (int& h:houses) {
            // upper_bound查找第一个大于目标值的元素 没有返回size
            int r = upper_bound(heaters.begin(), heaters.end(),h) - heaters.begin();
            int l = r - 1;
            int r_dis = r >= heaters.size() ? INT_MAX : heaters[r] - h;
            int l_dis = l == -1 ? INT_MAX : h - heaters[l];
            res = max(res,min(l_dis,r_dis));
        }
        return res;
    }


    // 686. 重复叠加字符串匹配
    // 覆盖b字符串至少需要 ceil(b/a) 个a字符串, 至多需要 ceil(b/a)+1 个a字符串。// 可用KMP
    int repeatedStringMatch(string a, string b) {
        /*
        if (b == "") {
            return 0;
        }
        vector<int> dica(26);
        vector<int> dicb(26);
        for (char & t:a) {
            dica[t-'a']++;
        }
        for (char & t:b) {
            dicb[t-'a']++;
        }
        int times = 0;
        for (int i = 0; i < 26; ++i) {
            if (dica[i] == 0 && dicb[i] != 0 || dica[i] > dicb[i]) {
                return -1;
            }
            if (dicb[i] == 0) {
                continue;
            }
            times = max(times, int(ceil(floor(dicb[i]/dica[i]))));
        }
        for (int i = 0; i < times; i++) {
            a += a;
        }
        return a.find(b) == -1 ? -1 : times;*/
        string s = a;
        while (s.size() <= b.size()) {
            s += a;
        }
        s += a;

        size_t found = s.find(b);
        if (found == string::npos) return -1;

        return (b.size() + found - 1) / a.size() + 1;
    }


    // 1705. 吃苹果的最大数目
    // 贪心 从最后一天开始算(贪心理想:吃掉的苹果都是最接近过期的)
    int eatenApples3(vector<int>& apples, vector<int>& days) {
        int res = 0;
        vector<bool> eat_day(apples.size() + 20001);
        for (int i = apples.size()-1; i >= 0; --i) {
            for (int j = i + days[i]-1; j >= i && apples[i] > 0; --j) {
                // 第j天还没吃
                if (!eat_day[j]) {
                    apples[i]--;
                    eat_day[j] = true;
                    res++;
                }
            }
        }
        return res;
    }

    typedef pair<int,int> pii;
    // 贪心 + 优先队列, 吃掉的苹果都是最接近过期的
    int eatenApples(vector<int>& apples, vector<int>& days) {
        int res = 0;
        int n = apples.size();
        // pair int1表示第i天腐烂 int2表示苹果数
        priority_queue<pii,vector<pii>, greater<pii>> pq;
        // 注意这种for循环, 配合队列(栈)的使用方式, 因为有两种方式：<n表示在结苹果，队列非空表示还有存货。都不满足才终止。
        for (int i = 0; i < n || !pq.empty(); ++i) {
            // 判断合理数据
            if (i < n && apples[i] > 0 && days[i] > 0) {
                pq.emplace(i + days[i], apples[i]);
            }
            // 清理第i天的烂苹果
            while (!pq.empty() && pq.top().first <= i) {
                pq.pop();
            }
            if (!pq.empty()) {
                auto [x, y] = pq.top();
                pq.pop();
                if (y > 1) {
                    y--;
                    pq.emplace(x, y);
                }
                res++;
            }
        }
        return res;
    }


    // 1609. 奇偶树
    bool isEvenOddTree(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        int level = 0;
        while (!q.empty()) {
            int pre = level % 2 == 0 ? INT_MIN : INT_MAX;
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                TreeNode* cur = q.front();
                q.pop();
                int val = cur->val;
                if (val % 2 == level % 2) {
                    return false;
                }
                if ((level % 2 == 0 && val <= pre) || (level % 2 == 1 && val >= pre)) {
                    return false;
                }
                pre = val;
                if (cur->left) {
                    q.push(cur->left);
                }
                if (cur->right) {
                    q.push(cur->right);
                }
            }
            level++;
        }
        return true;
    }


    // 1044. 最长重复子串
    // 二分法 + 字符串匹配算法 -- Rabin–Karp 把字符串转化为一个hash值 不断滑动窗口
    // 子串长度[0,n) 在这个范围内枚举当前值mid 若存在mid长的重复子串 则更新l=mid+1 否则r=mid-1
    // https://www.cnblogs.com/grandyang/p/14497723.html
    string longestDupSubstring(string S) {
        int n = S.size();
        int l = 0, r = n, mod = 1e7 + 7;
        string res;
        // power 记录每个位置的阶数
        vector<int> power(n,1);
        for (int i = 1; i < n; i++) {
            power[i] = (power[i-1]*26) % mod;
        }
        while (l < r) {
            int mid = l + (r-l)/2;
            // rabinKarp 检查是否存在长度为mid的重复子串
            string cur = rabinKarp(mid, S, power);
            if (cur.size() > res.size()) {
                res = cur;
                l = mid + 1;
            } else {
                // 注意二分的边界 r取不到,所以r=mid
                r = mid;
            }
        }
        return res;
    }

    string rabinKarp(int len, string s, vector<int> power) {
        if (len == 0) return "";
        unordered_map<int, vector<int>> hash;
        int cur = 0, mod = 1e7 + 7;
        for (int i = 0; i < len; ++i) {
            cur = (cur * 26 + s[i]-'a') % mod;
        }
        hash[cur] = {0};
        for (int i = len; i < s.size(); ++i) {
            // 此处不加mod的话，%后可能小于mod
            cur = ((cur - (s[i-len]-'a') * power[len-1]) % mod + mod) % mod;
            cur = (cur * 26 + (s[i]-'a')) % mod;
            if (hash.count(cur)) {
                for (int t : hash[cur]) {
                    if (s.substr(i - len + 1, len) == s.substr(t, len)) {
                        return s.substr(t, len);
                    }
                }
                hash[cur].push_back(i - len + 1);
            } else {
                hash[cur] = {i- len + 1};
            }
        }
        return "";
    }


    // 306. 累加数
    // like842 确定最前面的两个数 后面的数都是确定的 碰到不符合的直接return false;
    // so如何确定前两位 -- 穷举累加
    bool isAdditiveNumber(string num) {
        int n = num.size();
        for (int secondBegin = 1; secondBegin < n - 1; ++secondBegin) { // 第三位
            if (num[0] == '0' && secondBegin != 1) {
                break;
            }
            for (int secondEnd = secondBegin; secondEnd < n - 1; ++secondEnd) {
                if (num[secondBegin] == '0' && secondEnd != secondBegin) {
                    break;
                }
                if (valid(num, secondBegin, secondEnd)) { // 以当前两数开头是否valid
                    return true;
                }
            }
        }
        return false;
    }

    // 前两个数字不为0 保证了相加得到的第三个数字不会存在前导0
    bool valid(string num, int secondBegin, int secondEnd){
        int n = num.size();
        int firstBegin = 0, firstEnd = secondBegin - 1;
        // 枚举下一位
        while (secondEnd < n - 1) {
            string third = stringAdd(num, firstBegin, firstEnd, secondBegin, secondEnd);
            int thirdEnd = secondEnd + third.size();
            if (thirdEnd >= n || num.substr(secondEnd+1, third.size()) != third) {
                return false;
            }
            if (thirdEnd == n - 1) {
                return true;
            }
            firstBegin = secondBegin;
            firstEnd = secondEnd;
            secondBegin = secondEnd + 1;
            secondEnd = thirdEnd;
        }
        return true;
    }

    string stringAdd(string num, int one1, int one2, int two1, int two2){
        string res;
        int cur = 0, carry = 0;
        while (one2 >= one1 || two2 >= two1 || carry != 0) {
            cur = carry;
            if (one2 >= one1) {
                cur += num[one2--] - '0';
            }
            if (two2 >= two1) {
                cur += num[two2--] - '0';
            }
            carry = cur/10;
            cur %= 10;
            res = to_string(cur) + res;
        }
        return res;
    }


    // 842. 将数组拆分成斐波那契序列
    vector<int> splitIntoFibonacci(string num) {
        vector<int> res;
        if (num.size() < 3) {
            return res;
        }
        traceBack(num, res, 0);
        return res;
    }

    bool traceBack(string num, vector<int>& res, int idx) {
        int n = num.size();
        if (idx == n) { // stop
            return res.size() >= 3;
        }
        for (int i = idx; i < n; ++i) {
            if (num[idx] == '0' && i > idx) {
                break; //0只能在第一位
            }
            long long cur = stol(num.substr(idx, i - idx + 1));
            if (cur > INT_MAX) {
                break;
            }
            int len = res.size();
            if (len >= 2) {
                if (res[len-1] > cur - res[len-2]) { //res[i-1] + res[i-2] > cur
                    continue;
                } else if (res[len-1] < cur - res[len-2]) {
                    break;
                }
            }
            res.push_back(cur);
            if (traceBack(num, res, i + 1)) { //注意 这里是i+1
                return true;
            }
            res.pop_back();
        }
        return false;
    }


    // 1036. 逃离大迷宫
    // 简单想法：直接dfs，网格太大会超时。所以剪枝，即 C++广度有限搜索 从起点和终点同时广搜
    // 简单想法：直接dfs，网格太大会超时。所以剪枝，即 C++广度有限搜索 从起点和终点同时广搜
    int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    long long base = 1000000;
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        auto bfs = [&](vector<int> &source, vector<int> &target) {
            unordered_set<long long> visited;
            queue<vector<int>> qu;
            visited.insert(source[0] * base + source[1]); //转成一维
            for (auto& tmp:blocked) {
                visited.insert(tmp[0] * base + tmp[1]);
            }
            qu.push(source);
            while (!qu.empty()) {
                int size = qu.size();
                if (size > blocked.size()) { //有限搜索 提前终止 阈值如何获取
                    return true;
                }
                while (size-- > 0) {
                    auto cur = qu.front(); // auto& pop之后就为空的了？
                    qu.pop();
                    if (cur[0] == target[0] && cur[1] == target[1]) {
                        return true;
                    }
                    for (auto dir : dirs) {
                        int nx = cur[0] + dir[0], ny = cur[1] + dir[1];
                        if (nx >= base || nx < 0 || ny >= base || ny < 0 || visited.count(nx * base + ny)) {
                            continue;
                        }
                        visited.insert(nx * base + ny);
                        qu.push({nx, ny});
                    }
                }

            }
            return false;

        };
        return bfs(source, target) && bfs(target,source);
    }


    // 373. 查找和最小的K对数字  378 668
    // 第一反应 想到了归并排序 发现不行； so 优先队列 大根堆
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<vector<int>> res;
        // 按照首位大小排序 大根为最大值
        priority_queue<vector<int>, vector<vector<int>>, less<vector<int>>> pq;
        int m = nums1.size(), n = nums2.size();
        // 前k个 最多取nums1 nums2的前k位即可
        int ilen = min(m, k), jlen = min(n, k);

        for (int i = 0; i < ilen; ++i) {
            for (int j = 0; j < jlen; ++j) {
                int n1 = nums1[i], n2 = nums2[j];
                if (pq.size() < k) {
                    pq.push({n1 + n2, n1, n2});
                } else {
                    vector<int> tmp = pq.top();
                    if (tmp[0] > n1 + n2) {
                        pq.pop();
                        pq.push({n1 + n2, n1, n2});
                    } else { // n1 + n2都大了，后面的都大于tmp[0]
                        break;
                    }
                }
            }
        }

        while (!pq.empty()) {
            vector<int> tmp = pq.top();
            pq.pop();
            res.push_back({tmp[1], tmp[2]});
        }
        return res;
    }


    // 668. 乘法表中第k小的数
    // 二分求左边界
    int findKthNumber(int m, int n, int k) {
        int left = 1, right = m * n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            //求cnt 矩阵左下角开始
            int cnt = 0;
            int x = m, y = 1;
            while (x >= 1 && y <= n){
                if (x * y <= mid) {
                    cnt += x;
                    y++;
                } else {
                    x--;
                }
            }

            if (cnt >= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};

int main6(){
    solution_2 solution2;
    vector<vector<int>> d1{{0,100},{10,0}};
    vector<int> d2{0,0};
    vector<int> d3{0,2};
    // d1.clear();
    bool tmp = solution2.isEscapePossible(d1,d2,d3);
    cout << tmp << endl;
    return 0;
}
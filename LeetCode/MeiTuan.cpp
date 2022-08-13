// #include "bits/stdc++.h"
#include "iostream"
#include "vector"

using namespace std;


int main5() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m; cin >> n >> m;
    vector<int> a(n), b(n);
    for(int i = 0;i < n; i++) cin >> a[i] >> b[i];
    int ans = 0;
    for(int mask = 0;mask < (1 << n); mask++) {
        vector<bool> vis(m);
        int res = 0;
        bool flag = 1;
        for(int i = 0;i < n; i++) {
            if(mask >> i & 1) {
                res++;
                if(vis[a[i]] || vis[b[i]]) {
                    flag = 0;
                    break ;
                }
                vis[a[i]] = vis[b[i]] = 1;
            }
        }
        if(flag) ans = max(ans, res);
    }
    cout << ans << endl;
    return 0;
}





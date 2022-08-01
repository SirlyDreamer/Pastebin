#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

constexpr int maxn = 1e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3fL;

struct edge {
    i64 v, w;

    edge() = default;

    edge(int vv, int ww) : v(vv), w(ww) {}

    bool operator<(const edge &e) const {
        return w > e.w;
    }
};

vector<edge> mp[maxn];
vector<i64> dis(maxn);

bool spfa(int u, int n) {
    queue<int> T;					//存储接下来需要更新dis的点
    bool vis[maxn] = {false};                           //标记是否在队列中
    int cnt[maxn] = {0};                                //统计访问点的次数，如果超过n则说明有负环
    fill(dis.begin(), dis.end(), inf);			//初始化dis数组为∞
    dis[u] = 0;

    T.push(u);          //将源点入队并标记
    vis[u] = true;

    while (!T.empty()) {
        u = T.front();                              //取出队列前端的点并出队
        T.pop();
        vis[u] = false;                             //点u不在队列中了，标记为false
        for (auto &[v, w]: mp[u]) {
            if (dis[u] + w < dis[v]) {              //松弛点u的出边
                dis[v] = dis[u] + w;
                if (!vis[v]) {                      //如果松弛成功则将边的终点入队
                    T.push(v);
                    vis[v] = true;
                    cnt[v]++;                       //统计入队次数（即松弛轮数），如果大于n则说明有负环
                    if (cnt[v] > n)
                        return true;
                }
            }
        }
    }
    return false;
}

int main() {
    int m, n, s, t;
    cin >> n >> m >> s >> t;
    for (int i(0); i < m; ++i) {
        int u, v;
        i64 w;
        cin >> u >> v >> w;
        mp[u].emplace_back(v, w);
        mp[v].emplace_back(u, w);
    }
    spfa(s, n);
    cout << dis[t] << "\n";
    return 0;
}

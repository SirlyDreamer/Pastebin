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

bool Bellman_Ford(int cur, int n) {
    //初始化dis数组
    fill(dis.begin(),dis.end(),inf);
    dis[cur] = 0;
    bool ok(true);          //标记当前轮是否成功进行一次松弛

    int lim(n);             //设置松弛轮数的限制，如果限制归零则说明有负环
    while (lim-- && ok) {
        ok = false;
        //遍历图中的所有边并松弛
        for (int u(1); u <= n; ++u)
            for (auto &[v, w]: mp[u])
                if (dis[v] > dis[u] + w)    //对边e(u->v:w)进行松弛操作
                {
                    dis[v] = dis[u] + w;
                    ok = true;
                }
    }
    return lim >= 0;                        //如果有负环则lim == -1，返回false
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
    Bellman_Ford(s, n);
    cout << dis[t] << "\n";
    return 0;
}

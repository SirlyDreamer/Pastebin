#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
constexpr int maxn = 3e3 + 5;
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
//i64 dis[maxn];
vector<vector<i64>> dis(maxn, vector<i64>(maxn, 0));
vector<i64> h(maxn);

bool spfa(int s, int n) {
    queue<int> q;
    fill(h.begin(), h.end(), inf);
    bitset<maxn> vis;
    vector<int> cnt(maxn);
    h[s] = 0;
    q.emplace(s);
    vis[s] = 1;
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        vis[u] = 0;
        for (auto [v, w]: mp[u]) {
            if (h[v] > h[u] + w) {
                h[v] = h[u] + w;
                if (!vis[v]) {
                    q.emplace(v);
                    vis[v] = 1;
                    cnt[v]++;
                    if (cnt[v] == n)
                        return true;
                }
            }
        }
    }
    return false;
}

void dij(int s, int u) {
    priority_queue<edge> T;
    bool vis[maxn] = {false};

    fill(dis[s].begin(), dis[s].end(), inf);
    dis[s][u] = 0;
    T.emplace(u, 0);
    while (!T.empty()) {
        u = T.top().v;
        T.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (auto &[v, w]: mp[u]) {
            if (dis[s][u] + w < dis[s][v]) {
                dis[s][v] = dis[s][u] + w;
                T.emplace(v, dis[s][v]);
            }
        }
    }
}


int main() {
    int n, m;
    cin >> n >> m;
    for (int i(0); i < m; ++i) {
        int u, v;
        i64 w;
        cin >> u >> v >> w;
        mp[u].emplace_back(v, w);
    }
    for (int v(1); v <= n; ++v) {
        mp[0].emplace_back(v, 0);
    }
    if (spfa(0, n))
        cout << "-1\n";
    else {
        for (int u(1); u <= n; ++u)
            for (auto &[v, w]: mp[u])
                w = w + h[u] - h[v];
        for (int u(1); u <= n; ++u)
            dij(u, u);
        for (int u(1); u <= n; ++u) {
            i64 ans(0);
            for (int v(1); v <= n; ++v) {
                if (dis[u][v] == inf)
                    ans += v * 1e9;
                else if (u == v)
                    continue;
                else {
                    ans += v * (dis[u][v] - h[u] + h[v]);
                }
            }
            cout << ans << "\n";
        }
    }
    return 0;
}

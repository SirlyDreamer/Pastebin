#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
const i64 inf = 0x3F3F3F3F3F3F3F3FL;

const i64 _mod = 998244353;

long long fpow(long long x, long long t) {
    if (t == -1)
        return 0;
    long long ans(1), tmp(x);
    while (t) {
        if (t & 1)
            ans = ans * tmp % _mod;
        tmp = tmp * tmp % _mod;
        t >>= 1;
    }
    return ans;
}

struct edge {
    int v;
    i64 w, c;

    edge() = default;

    edge(int _v, i64 _w, i64 _c = 0) : v(_v), w(_w), c(_c) {}

    bool operator<(const edge &e) const {
        if (c == e.c)
            return w > e.w;
        if (c > 32 || e.c > 32)
            return c > e.c;
        return w + fpow(2, c - 1) > e.w + fpow(2, e.c - 1);
    }
};

bool cmp(pair<i64, i64> &a, pair<i64, i64> &b) {
    if (a.second == b.second)
        return a.first < b.first;
    if (a.second > 32 || b.second > 32)
        return a.second < b.second;
    return a.first + fpow(2, a.second - 1) < b.first + fpow(2, b.second - 1);
}

struct SP {
    static const int maxn = 1e6;
    const i64 inf = 0x3F3F3F3F3F3F3F3FLL;
    int n;
    vector<vector<edge>> mp;
    vector<pair<i64, i64>> dis;

    SP() = default;

    SP(int _n) : n(_n), mp(n + 1), dis(n + 1) {}

    void addedge(int _u, int _v, i64 _w, i64 _c = 0, bool isDirected = true) {
        mp[_u].emplace_back(_v, _w, _c);
        if (!isDirected)
            mp[_v].emplace_back(_u, _w, _c);
    }

    void dij(int u) {
        priority_queue<edge> T;
        bitset<maxn> vis;
        fill(dis.begin(), dis.end(), pair<i64, i64>(SP::inf, 0));
        dis[u] = {0, 0};
        T.emplace(u, 0, 0);
        while (!T.empty()) {
            u = T.top().v;
            T.pop();
            if (vis[u]) continue;
            vis[u] = true;
            for (auto &[v, w, c]: mp[u]) {
                auto tmp = dis[u];
                tmp.first += w;
                tmp.second += c;
                if (cmp(tmp, dis[v])) {
                    dis[v].first = dis[u].first + w;
                    dis[v].second = dis[u].second + c;
                    T.emplace(v, dis[v].first, dis[v].second);
                }
            }
        }
    }
};

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    SP cc(2 * n);
    for (int i(0); i < m; ++i) {
        int u, v;
        cin >> u >> v;
        cc.addedge(u, v, 1, 0);
        cc.addedge(v + n, u + n, 1, 0);
    }
    for (int i(1); i <= n; ++i)
        cc.addedge(i, i + n, 0, 1, false);
    cc.dij(1);
    i64 ans = (cc.dis[n].first % _mod + fpow(2, cc.dis[n].second - 1)) % _mod;
    ans = min(ans, (cc.dis[n + n].first % _mod + fpow(2, cc.dis[n + n].second - 1)) % _mod);
    cout << ans << "\n";
    return 0;
}

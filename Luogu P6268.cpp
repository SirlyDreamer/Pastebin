#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

constexpr int maxn = 1005;

struct edge {
    int v;
    i64 w;

    edge() = default;

    edge(int vv) : v(vv) {}

    edge(int vv, i64 ww) : v(vv), w(ww) {}

    bool operator<(const edge &e) const {
        return w > e.w;
    }
};

vector<edge> mp[maxn];
vector<bool> vis(maxn);
vector<int> lnk(maxn, -1);
vector<int> color(maxn, -1);

bool match(int u) {
    for (auto &[v, w]: mp[u]) {
        if (vis[v])
            continue;
        vis[v] = true;
        if (lnk[v] == -1 || match(lnk[v])) {
            lnk[v] = u;
            return true;
        }
    }
    return false;
}

bool col(int u) {
    queue<int> q;
    q.push(u);
    color[u] = 0;
    for (auto &[v, w]: mp[u]) {
        if (color[u] == color[v])
            return false;
        if (color[v] == -1) {
            color[v] = 1 - color[u];
            q.push(v);
        }
    }
    return true;
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i(0); i < m; ++i) {
        int u, v;
        cin >> u >> v;
        mp[u].emplace_back(v);
        mp[v].emplace_back(u);
    }
    int cnt(0);
    bool ok(true);
    for (int i(0); i < n && ok; ++i) {
        if (color[i] != -1)
            ok &= col(i);
    }
    for (int i(0); i < n; ++i) {
        if (color[i] == 1)
            continue;
        fill(vis.begin(), vis.end(), false);
        cnt += match(i);
    }
    cout << n - cnt << "\n";
}
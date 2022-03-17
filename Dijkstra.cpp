#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
using ll = long long;

constexpr int maxn = 2505;
constexpr int maxm = 6205;

struct edge {
    ll w;
    int v;
    bool operator<(const edge b) const { return w > b.w; }
} tmp;

vector<edge> mp[maxn];
int dis[maxn] = { 0 };

void dij(int cur) {
    priority_queue<edge> T;
    bool vis[maxn] = { false };

    memset(dis, 0x3f, sizeof dis);
    dis[cur] = 0;
    T.push({ 0, cur });
    while (!T.empty()) {
        cur = T.top().v;
        T.pop();
        if (vis[cur])
            continue;
        vis[cur] = true;
        for (auto &[w, v] : mp[cur]) {
            if (dis[cur] + w < dis[v]) {
                dis[v] = dis[cur] + w;
                T.push({ dis[v], v });
            }
        }
    }
}

int main() {
    int m, n, s, t;
    cin >> n >> m >> s >> t;
    for (int i(0); i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        tmp.w = w;
        tmp.v = v;
        mp[u].push_back(tmp);
        tmp.v = u;
        mp[v].push_back(tmp);
    }
    dij(s);
    cout << dis[t];
    return 0;
}
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
using ll = long long;

constexpr int maxn = 2505;
constexpr int maxm = 6205;

struct edge {
    int v;
    ll w;
} tmp;

vector<edge> mp[maxn];
int dis[maxn] = { 0 };

void spfa(int cur) {
    queue<int> T;
    bool vis[maxn] = { false };
    memset(dis, 0x3f, sizeof dis);

    dis[cur] = 0;
    T.push(cur);
    vis[cur] = true;
    
    while (!T.empty()) {
        cur = T.front();
        T.pop();
        vis[cur] = false;
        for (auto& [v, w] : mp[cur]) {
            if (dis[cur] + w < dis[v]) {
                dis[v] = dis[cur] + w;
                if (!vis[v]) {
                    T.push(v);
                    vis[v] = true;
                }
            }
        }
    }
}

int main() {
    ll m, n, s, t;
    cin >> n >> m >> s >> t;
    for (int i(0); i < m; ++i) {
        ll u, v, w;
        cin >> u >> v >> w;
        tmp.w = w;
        tmp.v = v;
        mp[u].push_back(tmp);
        tmp.v = u;
        mp[v].push_back(tmp);
    }
    spfa(s);
    cout << dis[t];
    return 0;
}
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
using ll = long long;

constexpr int maxn = 2505;

ll dis[maxn][maxn] = { 0 };

int main() {
    ll m, n, s, t;
    memset(dis, 0x3f, sizeof dis);

    cin >> n >> m >> s >> t;

    for (int i(0); i < m; ++i) {
        ll u, v, w;
        cin >> u >> v >> w;
        dis[u][v] = w;
        dis[v][u] = w;
    }

    for (int k(1); k <= n; ++k)
        for (int i(1); i <= n; ++i)
            for (int j(1); j <= n; ++j) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

    cout << dis[s][t];
    return 0;
}
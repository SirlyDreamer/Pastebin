#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
using ll = long long;

constexpr int maxn = 2505;
constexpr ll inf = 0x3f3f3f3f3f3f3f3fL;

ll dis[maxn][maxn];

int main() {
    int n, m, t;
    cin >> n >> m >> t;
    memset(dis, 0x3f, sizeof dis);
    for (int i(0); i <= n; ++i) 
        dis[i][i] = 0;					//初始化，自己到自己的最短路为0

    for (int i(0); i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        dis[u][v] = dis[v][u] = w;		//这里我们偷懒不存边，我们直接把u和v之间的最短路更新成其边权
        								//如果有重边的话这里需要取其最小值
    }

    for (int k(1); k <= n; ++k)				//k要写在最外层！！！！
        for (int i(1); i <= n; ++i)
            for (int j(1); j <= n; ++j) 
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);	//状态转移

    for (int i(0); i < t; ++i) {
        int u, v;
        cin >> u >> v;
        if (dis[u][v] == inf)
            cout << "-1\n";
        else
            cout << dis[u][v] << "\n";
    }
    return 0;
}
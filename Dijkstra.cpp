#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

using ll = long long;

constexpr int maxn = 1e5+5;
constexpr ll inf = 0x3f3f3f3f3f3f3f3fL;

struct edge
{
    int v;
    ll w;
    edge(int vv,ll ww):v(vv),w(ww){}
    edge():v(0),w(0){}
	bool operator<(const edge& _) const
	{
	    return w>_.w;
	}
} tmp;

vector<edge> mp[maxn];
ll dis[maxn] = {0};

void dij(int u) {
    priority_queue<edge> T;
    bool vis[maxn] = { false };

    fill(dis,dis+maxn,inf);
    dis[u] = 0;
    T.emplace(u, 0);
    while (!T.empty()) {
        u = T.top().v;
        T.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (auto &[v, w] : mp[u]) {
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                T.emplace(v, dis[v]);
            }
        }
    }
}

int main()
{
	ll m, n, s;
	cin >> n >> m >> s;
	for (int i(0); i < m; ++i)
	{
		int u, v;
		ll w;
		cin >> u >> v >> w;
		mp[u].emplace_back(v,w);
	}
	dij(s);
	for (int i(1); i <= n; ++i)
		if (dis[i] == inf)
			cout << "2147483647 ";
		else
			cout << dis[i] << " ";
	return 0;
}
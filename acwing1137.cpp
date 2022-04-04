#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
using ll = long long;

constexpr int maxn = 1e6 + 5;
constexpr int maxsn = 10;
constexpr ll inf = 0x3f3f3f3f3f3f3f3fL;

struct edge
{
	int v;
	ll w;
	edge(int vv, ll ww) : v(vv), w(ww) {}
	edge() : v(0), w(0) {}
	bool operator<(const edge& a) const { return w > a.w; }
} tmp;

vector<edge> mp[maxn];
ll ddis[6][maxn];
int s[maxsn];

void dij(ll (&dis)[maxn], int u)
{
	memset(dis, 0x3f, sizeof dis);
	bool vis[maxn];
	dis[u] = 0;
	priority_queue<edge> T;
	T.push({u, 0});
	while (!T.empty())
	{
		u = T.top().v;
		T.pop();
		if (vis[u])
			continue;
		vis[u] = true;
		for (auto& [v, w] : mp[u])
		{
			if (dis[v] > dis[u] + w)
			{
				dis[v] = dis[u] + w;
				T.push({v, dis[v]});
			}
		}
	}
}

ll dfs(int step, int u, int vis, ll dis)
{
	if (step == 6)
		return dis;
	ll mind = inf;
	for (int i(1); i < 6; ++i)
	{
		if ((vis >> i) & 1)
			continue;
		mind = min(mind, dfs(step + 1, i, vis ^ (1 << i), dis + ddis[u][s[i]]));
	}
	return mind;
}

int main()
{
	int n, m;

	cin >> n >> m;
	s[0] = 1;
	for (int i(1); i <= 5; ++i)
		cin >> s[i];
	for (int i(0); i < m; ++i)
	{
		int u, v;
		ll w;
		cin >> u >> v >> w;
		mp[u].emplace_back(v, w);
		mp[v].emplace_back(u, w);
	}
	for (int i(0); i < n; ++i)
		dij(ddis[i], s[i]);
	cout << dfs(1, 0, 0, 0);
	return 0;
}

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

using ll = long long;
constexpr int maxn = 1e6 + 5;

struct edge
{
	int v;
	ll w;
} tmp;

vector<edge> mp[maxn];
ll dis[maxn];

bool Bellman_Ford(int cur, ll n)
{
	memset(dis, 0x3f, sizeof dis);
	bool ok(true);
	dis[cur] = 0;

	int lim(n);
	while (lim-- && ok)
	{
		ok = false;
		for (int u(1); u <= n; ++u)
			for (auto& [v,w] : mp[u])
				if (dis[v] > dis[u] + w)
				{
					dis[v] = dis[u] + w;
					ok = true;
				}
	}
	return lim > 0;
}

int main()
{
	int m, n, s, t;
	cin >> n >> m >> s >> t;
	for (int i(0); i < m; ++i)
	{
		int u, v;
		ll w;
		cin >> u >> v >> w;
		tmp.w = w;
		tmp.v = v;
		mp[u].push_back(tmp);
		tmp.v = u;
		mp[v].push_back(tmp);
	}
	Bellman_Ford(s,n);
	cout << dis[t];
	return 0;
}

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

using ll = long long;

constexpr int maxn = 505;
constexpr ll inf = 0x3f3f3f3f3f3f3f3fL;

struct edge
{
    int v;
    ll w;
    edge(int vv, ll ww) :v(vv), w(ww) {}
    edge() :v(0), w(0) {}
    bool operator<(const edge& rhs) const
    {
        return w > rhs.w;
    }
} tmp;

vector<edge> mp[maxn];
ll ddis[maxn][maxn] = { 0 };

bool spfa(ll(&dis)[maxn], int u, int n) {
    queue<int> T;					
    bool vis[maxn] = { false };			
    int cnt[maxn] = { 0 };			
    memset(dis, 0x3f, sizeof dis);		
    dis[u] = 0;

    T.push(u);				
    vis[u] = true;

    while (!T.empty()) {
        u = T.front();			
        T.pop();
        vis[u] = false;			
        for (auto& [v, w] : mp[u]) {
            if (dis[u] + w < dis[v]) {	
                dis[v] = dis[u] + w;
                if (!vis[v]) {				
                    T.push(v);
                    vis[v] = true;
                    cnt[v]++;			
                    if (cnt[v] > n)
                        return false;
                }
            }
        }
    }
    return true;
}

void dij(ll(&dis)[maxn], int u)
{
	memset(dis, 0x3f, sizeof dis);
	bool vis[maxn] = { false };
	dis[u] = 0;
	priority_queue<edge> T;
	T.emplace(u,0LL);
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
                T.emplace(v, dis[v]);
			}
		}
	}
}

bool johnson(int& n)
{
    for (int v(1); v <= n; ++v)
        mp[0].emplace_back(v, 0LL);
    if (!spfa(ddis[0], 0, n))
        return false;
    for (int u(1); u <= n; ++u)
        for (auto& [v, w] : mp[u])
            w = w + ddis[0][u] - ddis[0][v];
    for (int u(1); u <= n; ++u)
        dij(ddis[u], u);
    return true;
}

int main()
{
	int n, m, t;
	cin >> n >> m >> t;

	for (int i(0); i < m; ++i)
	{
		int u, v;
		ll w;
		cin >> u >> v >> w;
		mp[u].emplace_back(v, w);
	}
	
    johnson(n);
    
	for (int i(0); i < t; ++i)
	{
		int u, v;
		cin >> u >> v;
		if (ddis[u][v] == inf)
			cout << "impossible\n";
		else
			cout << ddis[u][v] << "\n";
	}
	return 0;
}
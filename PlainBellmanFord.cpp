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
    //初始化dis数组
	memset(dis, 0x3f, sizeof dis);
	dis[cur] = 0;
    bool ok(true);	//标记当前轮是否成功进行一次松弛

	int lim(n);		//设置松弛轮数的限制，如果限制归零则说明有负环
	while (lim-- && ok)
	{
		ok = false;
        //遍历图中的所有边并松弛
		for (int u(1); u <= n; ++u)
			for (auto& [v,w] : mp[u])
            /*C++17语法，等价于
			for(int i(0); i < mp[u].size(); ++i)
            {
            	int& v = mp[u][i].v;
                ll& w = mp[u][i].w;*/
				if (dis[v] > dis[u] + w)	//对边{u,v,w}进行松弛操作
				{
					dis[v] = dis[u] + w;
					ok = true;
				}
	}
	return lim >= 0;						//如果有负环则lim=-1，返回false
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
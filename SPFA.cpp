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

bool spfa(int u,int n) {
    queue<int> T;						//存储接下来需要更新dis的点
    bool vis[maxn] = { false };			//标记是否在队列中
    int cnt[maxn] = {0};				//统计访问点的次数，如果超过n则说明有负环
    memset(dis, 0x3f, sizeof dis);		//初始化dis数组为∞
	dis[u] = 0;
    
    T.push(u);						//将源点入队并标记
    vis[u] = true;
    
    while (!T.empty()) {
        u = T.front();				//取出队列前端的点并出队
        T.pop();
        vis[u] = false;				//点u不在队列中了，标记为false
        for (auto& [v, w] : mp[u]) {
            if (dis[u] + w < dis[v]) {		//松弛点u的出边
                dis[v] = dis[u] + w;
                if (!vis[v]) {				//如果松弛成功则将边的终点入队
                    T.push(v);
                    vis[v] = true;
                    cnt[v]++;				//统计入队次数（即松弛轮数），如果大于n则说明有负环
                    if(cnt[v] > n)
                        return false;
                }
            }
        }
    }
    return true;
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
    spfa(s,n);
    cout << dis[t];
    return 0;
}
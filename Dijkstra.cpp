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
    bool operator<(const edge b) const { return w > b.w; }	//定义排序方式
} tmp;

vector<edge> mp[maxn];
int dis[maxn] = { 0 };

void dij(int u) {
    priority_queue<edge> T;		//这里并不是存边，这里存的是当前状态下，某一点和他的dis
    							//由于刚好又是边的两个参数，所以偷了个懒，直接拿边的struct来顶上了qwqwqwq
    
    bool vis[maxn] = { false };	//区分S点集和T点集，当vis[u] == true时我们认为u在S点集中
    memset(dis, 0x3f, sizeof dis);	//初始化dis数组，并将源点设置成0
    dis[u] = 0;
    T.push({ 0, u });			//将源点及其距离推入队列
    
    while (!T.empty()) {
        u = T.top().v;			//取出优先队列中当前dis最小的点
        T.pop();
        if (vis[u])				//如果这个点已经访问过则忽略这个点
            continue;
        vis[u] = true;			//将其加入S点集
        for (auto &[w, v] : mp[u]) {	//松弛其所有出边，并将其终点和dis加入优先队列
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
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
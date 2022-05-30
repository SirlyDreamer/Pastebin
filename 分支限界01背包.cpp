#include <bits/stdc++.h>

using namespace std;

struct node {
    int w, v;

    node() = default;

    node(int ww, int vv) : w(ww), v(vv) {};

    bool operator>(const node &x) const {
        return (v * 1.0 / w) > (x.v * 1.0 / x.w);
    }
};

struct state {
    int nxt, sumw, sumv;
    double maxv;

    bool operator<(const state &x) const {
        return maxv < x.maxv;
    }
};

int maxw, maxn;
vector<node> items;

double bound(int i, int sumw, int sumv) {
    double res = sumv;
    int lftw = maxw - sumw;
    while (i < maxn && items[i].w <= lftw) {
        lftw -= items[i].w;
        sumv += items[i].v;
        i++;
    }
    if (i < maxn) {
        res = sumv + lftw * (items[i].v * 1.0 / items[i].w);
    }
    return res;
}

int solve() {
    priority_queue<state> q;
    int res = 0;
    state r = {0, 0, 0, bound(0, 0, 0)};
    q.push(r);
    while (q.top().maxv > res) {
        state cur = q.top();
        q.pop();
        if (cur.nxt == maxn) {
            res = max(res, cur.sumv);
        } else {
            state u = cur;
            if (cur.sumw + items[cur.nxt].w <= maxw) {
                cur.maxv = bound(cur.nxt, cur.sumw, cur.sumv);
                if (cur.maxv > res) {
                    cur.sumw += items[cur.nxt].w;
                    cur.sumv += items[cur.nxt].v;
                    cur.nxt++;
                    q.push(cur);
                }
            }
            u.maxv = bound(u.nxt + 1, u.sumw, u.sumv);
            if (cur.maxv > res) {
                u.nxt++;
                q.push(u);
            }
        }
    }
    return res;
}

int main() {
    maxw = 878;
    maxn = 20;
    int w[] = {92, 4, 43, 83, 84, 68, 92, 82, 6, 44, 32, 18, 56, 83, 25, 96, 70, 48, 14, 58};
    int v[] = {44, 46, 90, 72, 91, 40, 75, 35, 8, 54, 78, 40, 77, 15, 61, 17, 75, 29, 75, 63};
    for (int i(0); i < 20; ++i)
        items.emplace_back(w[i], v[i]);
    sort(items.begin(), items.end(), greater<node>());
    cout << solve() << endl;
}
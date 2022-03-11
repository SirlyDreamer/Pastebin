#include <algorithm>
#include<iostream>
#include <math.h>
#define endl '\n'
#define AC return 0;
using namespace std;
#define int long long
//fenkuai_piece_add&query
const int N = 50004;
int n;
int id[N], s[N], b[N], Len;    //remeber:id[] -> b[]
int bl[N], br[N];
int a[N];   //targrt
// int sor_a[N];
struct node
{
    int v;
    int num;
    node(){}
    node(int a):v(a),num(0){}
    node(int a,int b):v(a),num(b){}
    bool operator < (const node& p)const
    {
        return v < p.v;
    }
}sor_a[N];

bool cmp1(node a, node b)
{
    return a.num < b.num;
}
void init()
{
    Len = sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        id[i] = (i - 1) / Len + 1;
    }
    int cnt = id[n];
    for (int i = 0; i < cnt; i++)
    {
        sort(sor_a + 1 + (Len * i), sor_a + 1 + min(n, (Len * (i + 1))));
    }
}

void fenkuai_add(int l, int r, int k)
{
    int L = id[l], R = id[r];
    if (L == R)
    {
        sort(sor_a + 1 + (Len * L), sor_a + 1 + min(n, (Len * (L + 1))), cmp1);
        for (int i = l; i <= r; i++)
            a[i] += k, sor_a[i].v += k;
        L--;
        sort(sor_a + 1 + (Len * L), sor_a + 1 + min(n, (Len * (L + 1))));
        return;
    }
    sort(sor_a + 1 + (Len * R), sor_a + 1 + min(n, (Len * (R + 1))), cmp1);
    sort(sor_a + 1 + (Len * L), sor_a + 1 + min(n, (Len * (L + 1))), cmp1);
    for (int i = l; id[i] == L; i++)
        a[i] += k, sor_a[i].v += k;
    for (int i = L + 1; i < R; i++)
        b[i] += k;
    for (int i = r; id[i] == R; i--)
        a[i] += k, sor_a[i].v += k;
    R--;
    L--;
    sort(sor_a + 1 + (Len * R), sor_a + 1 + min(n, (Len * (R + 1))));
    sort(sor_a + 1 + (Len * L), sor_a + 1 + min(n, (Len * (L + 1))));

}

int fenkuai_query(int l, int r, int c)
{
    int L = id[l], R = id[r];
    int ans = 0;
    if (L == R)
    {
        for (int i = l; i <= r; i++)
        {
            if (a[i] + b[i] <= c)
            {
                ans++;
            }
        }
        return ans;
    }
    for (int i = l; id[i] == L; i++)
    {
        if (a[i] + b[i] <= c)
            ans++;
    }
    for (int i = L + 1; i < R; i++)
    {
        if (b[i] + a[(i - 1) * Len + 1] > c)
            continue;
        node q(c - b[i]);
        int pos = upper_bound(sor_a + 1 + Len * (i - 1), sor_a + 1 + min(n, (Len * (i - 1 + 1))), q) - sor_a;
        ans += pos - (i - 1) * Len;
    }
    for (int i = r; id[i] == R; i--)
    {
        if (a[i] + b[i] <= c)
            ans++;
    }
    return ans;
}


void solve()
{

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], sor_a[i].v = a[i], sor_a[i].num = i;
    init();
    for (int i = 1; i <= n; i++)
    {
        int op, l, r, c;
        cin >> op >> l >> r >> c;
        if (op == 0)
            fenkuai_add(l, r, c);
        else
            cout << fenkuai_query(l, r, c * c) << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    //int T;cin >> T; while(T--)
    solve();
    AC
}

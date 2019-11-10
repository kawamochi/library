#include <bits/stdc++.h>
using namespace std;

class UnionFindTree
{
    vector<int> parent;
    vector<int> depth;
    vector<int> cnt;

public:
    UnionFindTree(int n) : parent(n), depth(n), cnt(n)
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            depth[i] = 0;
            cnt[i] = 1;
        }
    }

    //木の根を求める
    int find(int x)
    {
        if (parent[x] == x)
        {
            return x;
        }
        else
        {
            return parent[x] = find(parent[x]);
        }
    }

    //xとyの属する集合を併合
    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        if (depth[x] < depth[y])
        {
            parent[x] = y;
            cnt[y] += cnt[x];
        }
        else
        {
            parent[y] = x;
            cnt[x] += cnt[y];
            if (depth[x] == depth[y])
                depth[x]++;
        }
    }
    // 同じ集合に属しているか判定
    bool same(int x, int y)
    {
        return find(x) == find(y);
    }
    // 集合のサイズを取得
    int size(int x)
    {
        return cnt[find(x)];
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    UnionFindTree utree(n + 10);
    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        utree.unite(x, y);
    }
    map<int, int> fl;
    int ans = n;
    for (int i = 1; i <= n; i++)
    {
        if (!fl[utree.find(i)])
        {
            fl[utree.find(i)] = 1;
            ans -= utree.size(i) - 1;
        }
    }
    cout << ans << endl;
}

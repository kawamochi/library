#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

template <typename T>
struct edge
{
    int src, to;
    T cost;

    edge(int to, T cost) : src(-1), to(to), cost(cost) {}

    edge(int src, int to, T cost) : src(src), to(to), cost(cost) {}

    edge &operator=(const int &x)
    {
        to = x;
        return *this;
    }

    operator int() const { return to; }
};

template <typename T>
using Edges = vector<edge<T>>;
template <typename T>
using WeightedGraph = vector<Edges<T>>;
using UnWeightedGraph = vector<vector<int>>;
template <typename T>
using Matrix = vector<vector<T>>;

template <typename G>
struct DoublingLowestCommonAncestor
{
    const int LOG;
    vector<int> dep;
    const G &g;
    vector<vector<int>> table;

    DoublingLowestCommonAncestor(const G &g) : g(g), dep(g.size()), LOG(32 - __builtin_clz(g.size()))
    {
        table.assign(LOG, vector<int>(g.size(), -1));
    }

    void dfs(int idx, int par, int d)
    {
        table[0][idx] = par;
        dep[idx] = d;
        for (auto &to : g[idx])
        {
            if (to != par)
                dfs(to, idx, d + 1);
        }
    }

    void build(int n)
    {
        dfs(n, -1, 0);
        for (int k = 0; k + 1 < LOG; k++)
        {
            for (int i = 0; i < table[k].size(); i++)
            {
                if (table[k][i] == -1)
                    table[k + 1][i] = -1;
                else
                    table[k + 1][i] = table[k][table[k][i]];
            }
        }
    }

    int query(int u, int v)
    {
        if (dep[u] > dep[v])
            swap(u, v);
        for (int i = LOG - 1; i >= 0; i--)
        {
            if (((dep[v] - dep[u]) >> i) & 1)
                v = table[i][v];
        }
        if (u == v)
            return u;
        for (int i = LOG - 1; i >= 0; i--)
        {
            if (table[i][u] != table[i][v])
            {
                u = table[i][u];
                v = table[i][v];
            }
        }
        return table[0][u];
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    UnWeightedGraph g(n);
    int root;
    rep(i, n)
    {
        int k;
        cin >> k;
        if (k != -1)
        {
            g[k - 1].push_back(i);
        }
        else
        {
            root = i;
        }
    }
    DoublingLowestCommonAncestor<UnWeightedGraph> lca(g);
    lca.build(root);
    //    cout << root << endl;
    int q;
    cin >> q;
    rep(i, q)
    {
        int a, b;
        cin >> a >> b;
        //        cout << lca.query(a-1, b-1) << endl;
        if (lca.query(a - 1, b - 1) == b - 1)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
    return 0;
}
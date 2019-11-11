#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
typedef pair<int, int> P;
typedef long long ll;
int N;
// verified https://atcoder.jp/contests/abc137/submissions/8390522
class BellmanFord
{
    struct edge
    {
        int a, b;
        long long w;
    };
    int n;
    vector<edge> edges;
    vector<vector<int>> rev;
    vector<long long> d;
    vector<bool> reachable;
    void bfs()
    {
        queue<int> que;
        que.push(N);
        reachable[N] = true;
        while (!que.empty())
        {
            int a = que.front();
            que.pop();
            for (auto i : rev[a])
            {
                if (reachable[i] == false)
                {
                    reachable[i] = true;
                    que.push(i);
                }
            }
        }
    }

public:
    bool is_negative_loop = false;
    BellmanFord(int n) : n(n), edges(n), d(n, 1e18), rev(n), reachable(n) {}
    void add_edge(int a, int b, long long w)
    {
        assert(0 <= a && a < n && 0 <= b && b < n);
        edges.push_back({a, b, w});
        edges.push_back({b, a, w});
    }

    void add_arc(int a, int b, long long w)
    {
        assert(0 <= a && a < n && 0 <= b && b < n);
        edges.push_back({a, b, w});
        rev[b].push_back(a);
    }

    // return true if has negative loop
    void build(int a)
    {
        d[a] = 0;
        bfs();
        for (int i = 0; i < n; i++)
        {
            bool change = false;
            for (edge e : edges)
            {
                if (d[e.a] != 1e18 && reachable[e.a])
                {
                    if (d[e.b] > d[e.a] + e.w)
                    {
                        d[e.b] = d[e.a] + e.w;
                        change = true;
                    }
                }
            }
            if (!change)
            {
                return;
            }
        }
        is_negative_loop = true;
    }

    long long dist(int a)
    {
        return d[a];
    }
};

int main()
{
    int m, p;
    cin >> N >> m >> p;
    BellmanFord bel(N + 10);
    rep(i, m)
    {
        int a, b, c;
        cin >> a >> b >> c;
        c -= p;
        bel.add_arc(a, b, -c);
    }
    bel.build(1);
    if (bel.is_negative_loop)
    {
        cout << -1 << endl;
        return 0;
    }
    cout << max(0LL, -bel.dist(N)) << endl;
    return 0;
}
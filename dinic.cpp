#include <bits/stdc++.h>
using namespace std;

class Dinic
{
    struct edge
    {
        long long int to, cap, rev;
    };

    int n;
    vector<vector<edge>> G;
    vector<long long int> level;
    vector<long long int> iter;

    void bfs(int s)
    {
        level.assign(n, -1);
        queue<int> que;
        que.push(s);
        level[s] = 0;
        while (que.size())
        {
            int v = que.front();
            que.pop();
            for (int i = 0; i < G[v].size(); i++)
            {
                edge &e = G[v][i];
                if (e.cap > 0 && level[e.to] < 0)
                {
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }

    long long int dfs(int v, int t, long long int f)
    {
        if (v == t)
            return f;
        for (int i = iter[v]; i < G[v].size(); i++)
        {
            edge &e = G[v][i];
            if (e.cap > 0 && level[v] < level[e.to])
            {
                long long int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0)
                {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

public:
    Dinic(int n) : n(n), G(n), level(n), iter(n) {}

    void addEdge(int from, int to, long long int cap)
    {
        G[from].push_back({to, cap, int(G[to].size())});
        G[to].push_back({from, 0, int(G[from].size()) - 1});
    }

    long long int max_flow(int s, int t)
    {
        long long int flow = 0;
        while (1)
        {
            bfs(s);
            if (level[t] < 0)
                return flow;
            iter.assign(n, 0);
            long long int f;
            while ((f = dfs(s, t, 1e18)) > 0)
            {
                flow += f;
            }
        }
    }
};

int main()
{
    int n, m, p, g;
    cin >> n >> m >> p >> g;

    Dinic d(m + 1);

    for (int i = 0; i < g; i++)
    {
        int l;
        cin >> l;
        d.addEdge(m, l, 1e9);
    }

    for (int i = 0; i < n; i++)
    {
        int from, to, cap;
        cin >> from >> to >> cap;
        d.addEdge(from, to, cap);
    }

    cout << (d.max_flow(m, 0) >= p ? "Yes" : "No") << endl;
}
#include <bits/stdc++.h>
using namespace std;

class DAG
{
    int n;
    vector<vector<int>> adj;
    vector<int> visited;
    vector<int> dp;
    void dfs(int v)
    {
        if (visited[v] == 2)
        {
            is_acyclic = false;
            return;
        }
        else if (!visited[v])
        {
            visited[v] = 2;
            for (int s : adj[v])
            {
                dfs(s);
            }
            visited[v] = 1;
            sorted.push_back(v);
        }
    }

public:
    vector<int> sorted;
    DAG(int n) : n(n), adj(n), visited(n), dp(n, 0) {}
    bool is_acyclic = true;
    int longest_path = 0;

    //add directed link node a to node b
    void add_arc(int a, int b)
    {
        assert(0 <= a && a < n && 0 <= b && b < n);
        adj[a].push_back(b);
    }

    void tsort()
    {
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
                dfs(i);
        }
        reverse(sorted.begin(), sorted.end());
    }
    void build()
    {
        for (auto i : sorted)
        {
            for (auto j : adj[i])
            {
                dp[j] = max(dp[j], dp[i] + 1);
                longest_path = max(longest_path, dp[j]);
            }
        }
    }
};

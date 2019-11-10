#include <bits/stdc++.h>
using namespace std;
/*
重み付き無向グラフクラスです
実は有向グラフも適用できます
無向グラフ上のダイクストラ、ベルマンフード、負閉路検出、二部グラフ判定、
ワーシャルフロイドを載せます
すべてedgeで辺を持ちます
*/
class Graph{
    int n;
    struct edge{
        int to;
        int cost;
    };
    vector<vector<edge>> adj;
    vector<int> visited;
public:
    vector<int> dp;
    vector<vector<int>> floyd;
    Graph(int n):dp(n),adj(n),floyd(n),visited(n){}
    void add_edge(int a,int b){
        adj[a].push_back(edge{b, 1});
        adj[b].push_back(edge{a, 1});
    }
    void add_directed_edge(int from, int to){
        adj[from].push_back(edge{to,1});
    }
    void add_weighted_edge(int a, int b, int weight){
        adj[a].push_back(edge{b, weight});
        adj[b].push_back(edge{a, weight});
    }
    void add_weighted_directed_edge(int from,int to,int weight){
        adj[from].push_back(edge{to, weight});
    }
    void dijkstra(int from){
    }
}

int main(){
    return 0;
}
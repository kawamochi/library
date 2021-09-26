// verfied https://atcoder.jp/contests/abc220/submissions/26178414
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define endl '\n'
typedef pair<int, int> P;
typedef long long ll;
vector<vector<int>> v(200100);
vector<int> depth(200100, 1e9);
vector<int> child(200100);
vector<ll> ans(200100);
int N;
class Tree
{
private:
  int _time;

public:
  int _size;
  vector<vector<int>> _edges;
  vector<int> _depth;
  vector<int> _child_size; //自身を含めた子孫の数
  vector<int> _in_time;
  vector<int> _out_time;
  vector<int> _order;
  Tree(int n) : _size(n)
  {
    _edges.resize(n);
    _depth.resize(n, 1e9);
    _child_size.resize(n);
    _in_time.resize(n);
    _out_time.resize(n);
    _time = 0;
    _depth[0] = 0;
  }
  void add_edge(int a, int b)
  {
    _edges[a].push_back(b);
    _edges[b].push_back(a);
  }

  int calc_parameter(int node)
  {
    int res = 0;
    _in_time[node] = _time++;
    _order.push_back(node);
    for (auto n : _edges[node])
    {
      if (_depth[n] < _depth[node])
      {
        continue;
      }
      _depth[n] = _depth[node] + 1;
      res += calc_parameter(n);
    }
    _out_time[node] = _time++;
    _order.push_back(node);
    _child_size[node] = res + 1;
    return _child_size[node];
  }
};

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  Tree tree(n);
  rep(i, n - 1)
  {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    tree.add_edge(a, b);
  }
  tree.calc_parameter(0);
}
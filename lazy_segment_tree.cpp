#include <bits/stdc++.h>
using namespace std;

class LazySegTree
{
    int n;
    vector<long long int> node, lazy;

public:
    LazySegTree(vector<long long int> v)
    {
        int s = int(v.size());
        n = 1;
        while (n < s)
        {
            n <<= 1;
        }
        node.resize(2 * n - 1);
        lazy.resize(2 * n - 1, 0);

        for (int i = 0; i < s; i++)
        {
            node[i + n - 1] = v[i];
        }
        for (int i = n - 2; i >= 0; i--)
        {
            node[i] = node[i * 2 + 1] + node[i * 2 + 2];
        }
    }

    void eval(int k, int l, int r)
    {
        if (lazy[k])
        {
            node[k] += lazy[k];
            if (r - l > 1)
            {
                lazy[2 * k + 1] += lazy[k] / 2;
                lazy[2 * k + 2] += lazy[k] / 2;
            }

            lazy[k] = 0;
        }
    }

    void add(int a, int b, long long int x, int k = 0, int l = 0, int r = -1)
    {
        if (r < 0)
            r = n;
        eval(k, l, r);
        if (b <= l || r <= a)
        {
            return;
        }
        if (a <= l && r <= b)
        {
            lazy[k] += (r - l) * x;
            eval(k, l, r);
        }
        else
        {
            add(a, b, x, 2 * k + 1, l, (l + r) / 2);
            add(a, b, x, 2 * k + 2, (l + r) / 2, r);
            node[k] = node[2 * k + 1] + node[2 * k + 2];
        }
    }

    long long int rangeSum(int a, int b, int k = 0, int l = 0, int r = -1)
    {
        if (r < 0)
            r = n;
        eval(k, l, r);
        if (b <= l || r <= a)
        {
            return 0;
        }
        if (a <= l && r <= b)
        {
            return node[k];
        }
        long long int vl = rangeSum(a, b, 2 * k + 1, l, (l + r) / 2);
        long long int vr = rangeSum(a, b, 2 * k + 2, (l + r) / 2, r);
        return vl + vr;
    }

    void set(int a, long long int x)
    {
        add(a, a + 1, -get(a));
        add(a, a + 1, x);
    }

    long long int get(int a)
    {
        return rangeSum(a, a + 1);
    }
};

int main()
{
    int n;
    cin >> n;
    vector<long long int> as(n);
    LazySegTree seg(as);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        char c;
        cin >> c;
        if (c == 'A')
        {
            int id, x;
            cin >> id >> x;
            seg.set(id - 1, x);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << seg.rangeSum(l - 1, r) << endl;
        }
    }
}
#include <bits/stdc++.h>
using namespace std;

class Combination
{
    vector<long long> fact;
    vector<long long> factinv;
    long long MOD = 1e9 + 7;
    long long modpow(long long a, long long n)
    {
        if (n == 0)
            return 1;
        if (n % 2 == 0)
        {
            long long t = modpow(a, n / 2);
            return t * t % MOD;
        }
        return a * modpow(a, n - 1) % MOD;
    }

    long long modinv(long long a)
    {
        // mod is prime
        return modpow(a, MOD - 2);
    }

public:
    Combination(int n) : fact(n), factinv(n)
    {
        fact[0] = 1;
        for (int i = 1; i < n; i++)
        {
            fact[i] = fact[i - 1] * i % MOD;
        }
        factinv[n - 1] = modinv(fact[n - 1]);
        for (int i = n - 2; i >= 0; i--)
        {
            factinv[i] = factinv[i + 1] * (i + 1) % MOD;
        }
    }

    long long ncr(long long n, long long r)
    {
        if (r < 0 || r > n)
            return 0;
        return fact[n] * factinv[r] % MOD * factinv[n - r] % MOD;
    }

    long long npr(long long n, long long r)
    {
        if (r < 0 || r > n)
            return 0;
        return fact[n] * factinv[n - r] % MOD;
    }

    long long nhr(long long n, long long r)
    {
        if (n == 0 && r == 0)
            return 1;
        return ncr(n + r - 1, r);
    }
};

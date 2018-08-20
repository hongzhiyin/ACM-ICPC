int notPrim[N];
vi prim;
void GetPrime(int n)    // 预处理 [2, n] 的质数
{
    memset(notPrim, 0, sizeof(notPrim)); prim.clear();
    notPrim[0] = notPrim[1] = 1;
    rep(i, 2, n+1) {
        if (!notPrim[i]) prim.pb(i);
        for (int j = 0; j < sz(prim) && (ll)i * prim[j] <= n; ++j) {
            notPrim[i*prim[j]] = 1;
            if (i % prim[j] == 0) break;
        }
    }
}

// x <= 1e18
// a ^ (x-1) = 1 (mod x)
bool check(ll x) {      // 判断 x 是否是质数
    if (x == 2) return 1;
    if (x < 2 || !(x & 1)) return 0;
    rep(t, 0, 10) {
        ll a = rand() % (x-1) + 1;
        if (powmod(a, x-1) != 1) return 0;
    }
    return 1;
}

set <int> S;
void DPF(int x) {       // Decompose Prime Factor 分解质因数
    rep(i, 0, sz(prim)) {   // 预处理 [2, sqrt(x)] 的质数
        int p = prim[i];
        if (p > x) break;
        if (x % p == 0) {
            S.insert(p);
            while (x % p == 0) x /= p;
        }
    }
    if (x != 1) S.insert(x);
}

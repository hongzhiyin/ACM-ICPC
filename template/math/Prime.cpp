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

// n <= 1e18
// a ^ (n-1) = 1 (mod n)
bool check(ll x) {
    if (n == 2) return 1;
    if (n < 2 || !(n & 1)) return 0;
    rep(t, 0, 10) {
        ll a = rand() % (n-1) + 1;
        if (powmod(a, n-1) != 1) return 0;
    }
    return 1;
}

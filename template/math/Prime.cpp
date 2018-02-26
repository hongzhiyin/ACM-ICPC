int notPrim[N];
vi prim;
void GetPrime(int n)
{
    memset(notPrim, 0, sizeof(notPrim)); prim.clear();
    notPrim[0] = notPrim[1] = 1;
    rep(i, 2, n+1) {
        if (!notPrim[i]) prim.pb(i);
        for (int j = 0; j < sz(prim) && i * prim[j] <= n; ++j) {
            notPrim[i*prim[j]] = 1;
            if (i % prim[j] == 0) break;
        }
    }
}

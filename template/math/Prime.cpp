int notPrim[N];
vi prim;
void GetPrime(int n)
{
    memset(notPrim, 0, sizeof(notPrim)); prim.clear();
    rep(i, 2, n+1) if (!notPrim[i]) {
        prim.pb(i);
        if (i+i <= n) for (int j = i+i; j <= n; j += i)
            notPrim[j] = 1;
    }
}

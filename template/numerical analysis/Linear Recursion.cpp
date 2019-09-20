/*
【准备】
    1. 数列前 m 项， a[0] ~ a[m-1]
    2. 系数前 m 项， f[1] ~ f[m]
    3. a[m] = f[1] * a[m-1] + f[2] * a[m-2] .. + f[m] * a[0]
    4. N 为大于 2m+1 的 2 的幂
【使用】
    1. 调用 lr.qry(f, a, m, n) 求 a[n]
【注意】
    1. 模数需支持 NTT
*/

struct Linear_Recursion {
    int d, L, b[N], c[N], g[N], h[N], w[N];
    void dft(int *a, int f) {
        rep(i, 1, L) if (h[i] > i) swap(a[i], a[h[i]]);
        ll A; int i = 2, j, k, m, g = d>>1, *p, *l, *r;
        for (; m = i>>1, i <= L; i <<= 1, g >>= 1) for(j = 0; j < L; j += i) {
            p = w; l = a + j; r = l + m;
            for(k = 0; k < m; k++, l++, r++, p += g)
                A = (ll)(*p) * (*r), *r = (-A + *l) % MOD, *l = (A + *l) % MOD;
        }
        if (f == -1) {
            reverse(a + 1, a + L); int rev = qpow(L, MOD-2);
            rep(i, 0, L) a[i] = 1ll * a[i] * rev % MOD;
        }
    }
    void get(int n) {
        for (L = 1; L <= n; L <<= 1);
        rep(i, 1, L+1) h[i] = (h[i>>1] >> 1) | (i & 1 ? L>>1 : 0);
    }
    void inv(int *b, int *a, int n) {
        b[0] = 1;
        int t = 1; for (; t <= n; t <<= 1);
        for (L = 2; L <= t; L <<= 1) {
            get(L - 1);
            rep(i, 0, L) c[i] = a[i], g[i] = b[i];
            dft(c, 1); dft(g, 1); dot(c, g); dft(c, -1);
            rep(i, 0, L>>1) c[i] = c[i+(L>>1)], c[i+(L>>1)] = 0;
            dft(c, 1); dot(c, g); dft(c, -1);
            rep(i, L>>1, L) b[i] = -c[i-(L>>1)];
        }
    }
    void dot(int *a, int *b) {
        rep(i, 0, L) a[i] = 1ll * a[i] * b[i] % MOD;
    }
    void calc(int n, int *f, int m) {
        if (n < m) { c[m-n] = 1; return; }
        calc(n>>1, f, m);
        dft(c, 1); dot(c, c); dft(c, -1);
        if (n & 1) rep(i, 0, L) c[i] = c[i+1];
        rep(i, 0, m+1) g[i] = c[i];
        rep(i, m+1, L+1) g[i] = 0;
        dft(g, 1); dot(g, b); dft(g, -1);
        rep(i, m+1, L+1) g[i] = 0;
        dft(g, 1); dot(g, f); dft(g, -1);
        rep(i, 0, m+1) c[i] = (c[i+m] - g[i+m]) % MOD, c[i+m] = 0;
    }
    int qry(int *f, int *a, int m, int n) {
        memset(b, 0, sizeof(b));
        f[0] = 1; rep(i, 1, m+1) f[i] = -f[i];
        rep(i, m+1, N) f[i] = 0;
        get(m << 1); d = L;
        w[0] = 1; w[1] = qpow(3, (MOD-1)/L);
        rep(i, 2, L+1) w[i] = 1ll * w[i-1] * w[1] % MOD;
        inv(b, f, m);
        rep(i, 0, L+1) c[i] = g[i] = 0;
        get(m << 1);
        rep(i, m+1, L+1) b[i] = 0;
        dft(b, 1); dft(f, 1);
        calc(n, f, m);
        int res = 0;
        rep(i, 0, m) res = (1ll * c[m-i] * a[i] + res) % MOD;
        return (res + MOD) % MOD;
    }
} lr;

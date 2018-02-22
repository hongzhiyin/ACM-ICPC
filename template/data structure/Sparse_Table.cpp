struct ST {
    int d[maxn][30], p[maxn];

    void Init(int *a, int n) {
        rep(i, 0, n) d[i][0] = a[i];
        for (int j = 1; (1 << j) <= n; ++j)
            for (int i = 0; i + (1 << j) - 1 < n; ++i)
                d[i][j] = min(d[i][j - 1], d[i + (1 << (j - 1))][j - 1]);
        int k = 0;
        while ((1 << k) <= n) {
            rep(i, (1 << k), min(n + 1, (1 << k + 1)))
                p[i] = k;
            ++k;
        }
    }

    int st(int L, int R) {
        int k = p[R - L + 1];
        return min(d[L][k], d[R - (1 << k) + 1][k]);
    }
};

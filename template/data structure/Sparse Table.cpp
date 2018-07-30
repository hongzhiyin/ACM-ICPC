struct ST {
    int d[N][30], p[N];
    void init(int *a, int n) {
        rep(i, 0, n) d[i][0] = a[i];
        for (int j = 1; (1 << j) <= n; ++j)
            for (int i = 0; i + (1 << j) - 1 < n; ++i)
                d[i][j] = min(d[i][j - 1], d[i + (1 << (j - 1))][j - 1]);
        p[1] = 0;
        rep(i, 2, n+1) p[i] = p[i >> 1] + 1;
    }
    int query(int L, int R) {
        int k = p[R - L + 1];
        return min(d[L][k], d[R - (1 << k) + 1][k]);
    }
};

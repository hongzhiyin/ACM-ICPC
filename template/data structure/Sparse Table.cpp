// 固定起点的区间的最值具有单调性，可依此进行二分

struct ST {
    int d[N][30], lg[N];
    void init(int *a, int n) {      // a[] 从 0 开始
        rep(i, 0, n) d[i][0] = a[i];
        // rep(i, 1, n+1) d[i][0] = a[i];  // a[] 从 1 开始
        for (int j = 1; j < 30; ++j)
            for (int i = 0; i + (1 << j) - 1 < n; ++i)
            // for (int i = 1; i + (1 << j) - 1 <= n; ++i)  // a[] 从 1 开始
                d[i][j] = min(d[i][j - 1], d[i + (1 << (j - 1))][j - 1]);
        lg[1] = 0; rep(i, 2, n+1) lg[i] = lg[i >> 1] + 1;
    }
    int query(int L, int R) {       // 看情况 L 和 R 是否需要提前 -1
        int k = lg[R - L + 1];
        return min(d[L][k], d[R - (1 << k) + 1][k]);
    }
};


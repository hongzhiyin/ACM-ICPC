rep(i, 1, n+1) g[i] = INF;
rep(i, 0, n) {
    int k = lower_bound(g+1, g+n+1, a[i]) - g;
    dp[i] = k;
    g[k] = a[i];
}

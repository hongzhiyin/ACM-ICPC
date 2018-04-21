rep(i, 1, n+1) g[i] = INF;
rep(i, 0, n) {
    int k = lower_bound(g+1, g+n+1, a[i]) - g;
    dp[i] = k;  //dp[i] 表示以 a[i] 结尾的最长子序列的长度
    g[k] = a[i];    //用 a[i] 更新 g[] 中的值使得子序列元素尽可能小
}

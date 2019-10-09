rep(d, 2, len+1) {    // 枚举区间长度
    rep(i, 1, len-d+2) {    // 区间左端点，从 1 开始
        int j = i + d - 1;  // 区间右端点
        if (check(i, j)) dp[i][j] = fun1(dp[i+1][j-1]);
        rep(k, i, j) dp[i][j] = max(dp[i][j], fun2(dp[i][k], dp[k+1][j]) );
    }
}

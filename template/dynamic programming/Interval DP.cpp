// poj 2955
// 字符串中最多的匹配括号个数

bool check(int i, int j) {
    return s[i] == '(' && s[j] == ')' || s[i] == '[' && s[j] == ']';
}
int Solve() {
    memset(dp, 0, sizeof(dp));    // dp[i][j] 表示区间 [i, j] 内最大匹配数
    int len = strlen(s);
    rep(d, 2, len+1) {    // 枚举区间长度
        rep(i, 0, len-d+1) {    // 区间左端点
            int j = i + d - 1;  // 区间右端点
            if (check(i, j)) dp[i][j] = dp[i+1][j-1] + 2;
            rep(k, i, j) dp[i][j] = max(dp[i][j], dp[i][k] + dp[k+1][j]);
        }
    }
    printf("%d\n", dp[0][len-1]);
}

// hdu 4293
// 每个区间有一个权值，求区间互不相交和包含的最大权值

int Solve() {
    rep(i, 1, n+1) rep(j, 0, i)
        dp[i] = max(dp[i], dp[j] + grp[j+1][i]);
    return !printf("%d\n", dp[n]);
}

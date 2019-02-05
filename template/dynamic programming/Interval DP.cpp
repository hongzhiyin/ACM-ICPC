rep(d, 2, len+1) {    // 枚举区间长度
    rep(i, 1, len-d+2) {    // 区间左端点，从 1 开始
        int j = i + d - 1;  // 区间右端点
        if (check(i, j)) dp[i][j] = fun1(dp[i+1][j-1]);
        rep(k, i, j) dp[i][j] = max(dp[i][j], fun2(dp[i][k], dp[k+1][j]) );
    }
}

================================================== Problem Set ==================================================

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

// hdu 2476
// 每次可以将一段区间设为某个字符，求将字符串 A 变成字符串 B 的最小次数

int Solve() {
    memset(dp, 0, sizeof(dp));
    int len = strlen(s1);
    rep(i, 0, len) dp[i][i] = 1;
    rep(d, 2, len+1) {  // 当需要枚举区间中间节点时，如果不能知道中间区间的值，应该先枚举长度
        rep(i, 0, len-d+1) {
            int j = i + d - 1;
            dp[i][j] = dp[i+1][j] + 1;  // 相当于 k = i 的情况，设一个初值
            // 之所以不用 memset 设无穷大，因为后面会有 k > j 的情况，值应为 0
            rep(k, i+1, j+1)
                dp[i][j] = min(dp[i][j], dp[i+1][k] + dp[k+1][j] + (s2[i] != s2[k]));
        }
    }
    rep(i, 0, len) {
        ans[i] = dp[0][i];  // 设初值，因为 k 不能等于 -1
        if (s1[i] == s2[i]) ans[i] = i ? ans[i-1] : 0;  // 如果字符相等，则此位置不用付出代价
        rep(k, 0, i) ans[i] = min(ans[i], ans[k] + dp[k+1][i]);
    }
    printf("%d\n", ans[len-1]);
}

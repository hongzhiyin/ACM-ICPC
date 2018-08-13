// https://blog.csdn.net/wust_zzwh/article/details/52100392

memset(dp, -1, sizeof(dp));     // 如果多组数据不影响 dp[][] ，就放在 while() 外面

int dp[ 数位长度 ][ 状态数 ], num[ 数位长度 ];
int dfs(int pos, int state, bool limit) {   // pos ：当前枚举位， state ：当前状态， limit ：当前枚举位是否有限制
    if (pos == -1) return 1;                // 枚举完毕
    if (!limit && dp[pos][state] != -1) return dp[pos][state];    // 记忆化搜索
    int ans = 0, up = limit ? num[pos] : 9;          // 确定上界
    rep(i, 0, up+1) {
        if (!check(state, i)) continue;     // 状态非法
        ans += dfs(pos-1, change(state), limit && i==num[pos]);
    }
    return limit ? ans : dp[pos][state] = ans;
}

int digit(int x) {
    int pos = 0;
    while (x) {
        num[pos++] = x % 10;
        x /= 10;
    }
    return dfs(pos-1, state, true);
}

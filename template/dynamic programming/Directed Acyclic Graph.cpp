void dfs(int u) {
    if (dp[u] != -1) return dp[u];
    int res = Init;   // 设初值
    rep(i, 0, sz(e[u])) {
        v = e[u][i];
        // Cost: 代价  Profit(x): 关于 x 的收益
        res = max(res, res - Cost + Profit(dfs(v)));
    }
    return dp[u] = res;
}

int dfs(int u) {
    if (dp[u] != -1) return dp[u];
    int res = Init, tmp = 0;   // 设初值
    for (auto v : e[u]) // Cost: 代价  Profit(v): 关于 v 的收益
        tmp = max(tmp, - Cost + Profit(dfs(v)));
    return dp[u] = res + tmp;
}

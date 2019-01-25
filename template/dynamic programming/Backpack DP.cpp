// 背包九讲

int dp[N];    // dp[i] 表示体积为 i 时可以获得的最大价值

void Init() {
    memset(dp, 0, sizeof(dp));        // 不需要恰好装满
    memset(dp, 0xc0, sizeof(dp)); dp[0] = 0;    // 需要恰好装满
    rep(i, 1, n+1)
        function(...);      // 调用一下对应函数，用第 i 件物品来更新状态
}

// 01 背包 ( 1 个物品 ) 时间复杂度 O(V)
void ZeroOnePack(int cost, int weight) {
    per(i, cost, volume+1) dp[i] = max(dp[i], dp[i-cost] + weight);
}

// 完全背包 ( 无限个物品 ) 时间复杂度 O(V)
void CompletePack(int cost, int weight) {
    rep(i, cost, volume+1) dp[i] = max(dp[i], dp[i-cost] + weight);
}

// 多重背包 ( 有限个物品 ) 时间复杂度 O( V*log(amount) )
void MultiplePack(int cost, int weight, int amount) {
    if (cost * amount >= volume) CompletePack(cost, weight, volume);
    else {
        for (int k = 1; k < amount; amount -= k, k <<= 1)
            ZeroOnePack(k * cost, k * weight, volume);
        ZeroOnePack(amount * cost, amount * weight, volume);
    }
}

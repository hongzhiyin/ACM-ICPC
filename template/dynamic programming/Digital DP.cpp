// https://blog.csdn.net/wust_zzwh/article/details/52100392

memset(dp, -1, sizeof(dp));     // 如果多组数据不影响 dp[][] ，就放在 while() 外面

int dp[ 数位长度 ][ 状态数 ], num[ 数位长度 ];
int dfs(int pos, int state, bool limit) {   // pos ：当前枚举位， state ：当前状态， limit ：当前枚举位是否有限制
    if (pos == -1) { check(state); return x; }               // 枚举完毕，判断状态合法性，返回相应值
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

// ---------------------------------------------------------------------------------------------------- //

// hdu 4507
// https://www.cnblogs.com/kuangbin/archive/2013/05/01/3053233.html
// 和 7 有关：
// 1. 整数中某一位是 7 ；
// 2. 整数的每一位加起来的和是 7 的整数倍；
// 3. 这个整数是 7 的整数倍；
// 求一个区间中和 7 无关的数的平方和。

struct Node {
    int cnt, sum1, sum2;
    Node () {}
    Node (int cnt, int sum1, int sum2) : cnt(cnt), sum1(sum1), sum2(sum2) {}
};
Node dp[N][10][10];
int num[N], p[N];   // p[i] = 10 ^ i
Node dfs(int pos, int pre1, int pre2, bool limit) {
    if (pos == -1) return Node((pre1 != 0 && pre2 != 0), 0, 0);     // 枚举完毕，判断状态合法性，返回相应值
    if (!limit && dp[pos][pre1][pre2].cnt != -1) return dp[pos][pre1][pre2];    // 记忆化搜索
    int up = limit ? num[pos] : 9;          // 确定上界
    Node ans(0, 0, 0);
    rep(i, 0, up+1) {
        if (i == 7) continue;     // 状态非法
        Node tmp = dfs(pos-1, (pre1+i)%7, (pre2*10+i)%7, limit && i==num[pos]);
        int x = mul(i, p[pos]), x2 = mul(x, x);
        ans.cnt = add(ans.cnt, tmp.cnt);
        ans.sum1 = add(add(ans.sum1, tmp.sum1), mul(tmp.cnt, x));
        // (a1 + x) + (a2 + x) + ... + (an + x) = (a1 + a2 + ... + an) + n * x
        ans.sum2 = add(add(ans.sum2, tmp.sum2), add(mul(2ll * tmp.sum1, x), mul(tmp.cnt, x2)));
        // (a1 + x)^2 + (a2 + x)^2 + ... + (an + x)^2 = (a1^2 + a2^2 + ... + an^2) + 2 * x * (a1 + a2 + ... + an) + n * x^2
    }
    return limit ? ans : dp[pos][pre1][pre2] = ans;
}

int digit(ll x) {
    int pos = 0;
    while (x) {
        num[pos++] = x % 10;
        x /= 10;
    }
    return dfs(pos-1, 0, 0, true).sum2;
}

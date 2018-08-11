// hdu 2089
// 求区间内不包含 4 和 62 的数字个数
// https://www.cnblogs.com/wenruo/p/4725005.html

void Pre() {    // dp[i][j] 表示长度为 i 位，首位为 j 的符合要求的数字个数
    dp[0][0] = 1;   // 初始化
    rep(i, 1, 8) rep(j, 0, 10) rep(k, 0, 10)
        if (j != 4 && !(j == 6 && k == 2))    // 合法情况
          dp[i][j] += dp[i-1][k];   // 长度为 i 位，首位为 j 的数字个数等于合法的长度为 i-1 位，首位为 k 的数字个数
}

int work(int x) {   // 求 [0, x) 中合法的数字个数
    int len = 0, res = 0;
    while (x) {
        d[len++] = x % 10;
        x /= 10;
    }
    d[len + 1] = 0;
    per(i, 1, len+1) {    // 从高位到低位遍历
        rep(j, 0, dig[i]) {   // 遍历最高位小于当前枚举位的长度为 i 的合法数字个数
            if (!(dig[i+1] == 6 && j == 2))
                res += dp[i][j];
        }
        if (dig[i] == 4 || dig[i+1] == 6 && dig[i] == 2) break;   // 非法情况直接退出循环
    }
    return res;
}

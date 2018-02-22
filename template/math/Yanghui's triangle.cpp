//求前 n 行
ll C[maxn][maxn];
memset(C, 0, sizeof(C));
rep(i, 0, maxn) {
    C[i][0] = C[i][i] = 1;
    rep(j, 1, i)
        C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
}

//求第 n 行（不取模）
ll C[maxn];
C[0] = 1;
rep(i, 1, n + 1)
    C[i] = C[i - 1] * (n - i + 1) / i;

//求第 n 行（取模）
ll C[maxn];
C[0] = 1;
rep(i, 1, n + 1)
    C[i] = (C[i - 1] * (n - i + 1) % MOD * inv[i]) % MOD;

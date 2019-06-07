// 求 C(n, m)
ll C(int n, int m) {
    ll res = 1;
    rep(i, 0, m) res = res * (n-i) / (i+1);
    return res;
}

// 求 C(n, m) （取模）
int C(int n, int m) {
    int res = 1;
    rep(i, 0, m) res = mul(mul(res, n-i), inv[i+1]);
    return res;
}

// 求前 n 行
ll C[N][N];
void Yanghui() {
    memset(C, 0, sizeof(C));
    rep(i, 0, N) {
        C[i][0] = C[i][i] = 1;
        rep(j, 1, i) C[i][j] = add(C[i-1][j-1], C[i-1][j]);
    }
}

// 求第 n 行（不取模）
C[0] = 1;
rep(i, 1, n+1) C[i] = C[i-1] * (n - i + 1) / i;

// 求第 n 行（取模）
inv[1] = C[0] = 1;
rep(i, 2, n+1) inv[i] = mul(inv[MOD%i], MOD - MOD / i);
rep(i, 1, n+1) C[i] = mul(mul(C[i-1], n - i + 1), inv[i]);

// 求第 n 列（不取模）
C[n] = 1;
rep(i, n+1, N) C[i] = C[i-1] * i / (i - n);

// 求第 n 列（取模）
C[n] = inv[1] = 1;
rep(i, 2, N) inv[i] = mul(inv[MOD%i], MOD - MOD / i);
rep(i, n+1, N) C[i] = mul(mul(C[i-1], i), inv[i-n]);

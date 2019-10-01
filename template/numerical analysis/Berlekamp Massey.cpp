/*
< 准备 >
    1. vector<int> s 表示序列前若干项。

< 使用 >
    1. 调用 BM(s) ，得
    .. 返回 vector<int> 保存最短递推式系数

< 注意 >
    1. 递推式系数末尾的 0 (MOD) 是有意义的，为了解决前若干项不符合递推式的情况
*/

vi Berlekamp_Massey(vi s) {
    vi C(1, 1), B(1, 1);
    int L = 0, m = 1, b = 1;
    rep(n, 0, sz(s)) {
        ll d = 0;
        rep(i, 0, L+1) (d += 1ll * C[i] * s[n-i]) %= MOD;
        if(d == 0) ++m;
        else {
            vi T = C;
            ll c = MOD - d * qpow(b, MOD - 2) % MOD;
            while (sz(C) < sz(B) + m) C.pb(0);
            rep(i, 0, sz(B)) C[i + m] = add(C[i + m], mul(c, B[i]));
            if (2 * L <= n) L = n + 1 - L, B = T, b = d, m = 1;
            else ++m;
        }
    }
    rep(i, 0, sz(C)) C[i] = MOD - C[i];
    return vi(C.begin() + 1, C.end());
}

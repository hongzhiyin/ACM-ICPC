ll phi(ll n) {
    ll ret = n;
    for (ll i = 2; i*i <= n; ++i) if (n % i == 0) {
        ret = ret - ret / i;
        while (n % i == 0) n /= i;
    }
    if (n > 1) ret = ret - ret / n;
    return ret;
}

int phi[N];
void Euler() {
    memset(phi, 0, sizeof(phi));
    phi[1] = 1;
    rep(i, 2, N) if (!phi[i]) {
        for (int j = i; j < N; j += i) {
            if (!phi[j]) phi[j] = j;
            phi[j] = phi[j] / i * (i - 1);
        }
    }
}

// 欧拉降幂 ( B > phi(C) )
// A ^ B % C = A ^ (B % phi(C) + phi(C)) % C
ll Euler_qpow(ll a, ll b, ll mod) {
    ll res = 1; bool ok = (b > 0 && a >= mod);
    for (; b; b >>= 1) {
        if (b & 1) {
            res = res * a;
            ok |= (res >= mod);
            res %= mod;
        }
        a = a * a;
        ok |= (b > 1 && a >= mod);
        a %= mod;
    }
    return res + mod * ok;
}

// 求 a[l] ^ ( a[l+1] ^ ( a[l+2] ^ ( ... ^ a[r] ) ... ) % mod
// 注意：结果要再对 mod 取模，即 ans = work(l, r, mod) % mod
ll work(int l, int r, int mod) {
    if (mod == 1) return 1;
    if (l == r) return a[l];
    return Euler_qpow(a[l], work(l+1, r, phi[mod]), mod);
}

// 欧拉定理
// A ^ phi(C) ≡ 1 (mod C)

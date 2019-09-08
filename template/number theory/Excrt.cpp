struct Excrt {  // ans = a (mod b)
    ll a[N], b[N];
    int n;
    void init(int _n) {
        n = _n;
        rep(i, 0, n) scanf("%lld%lld", b+i, a+i);
    }
    ll qmul(ll a, ll b, ll mod) {
        ll res = 0;
        for (a %= mod; b; a = (a + a) % mod, b >>= 1) if (b & 1)
            res = (res + a) % mod;
        return res;
    }
    ll exgcd(ll a, ll b, ll &x, ll &y) {
        if (!b) { x = 1; y = 0; return a; }
        ll g = exgcd(b, a % b, y, x);
        y -= x * (a / b);
        return g;
    }
    ll excrt() {
        ll x, y, M = b[0], ans = a[0];
        ans = (ans % M + M) % M;
        rep(i, 1, n) {
            ll aa = M, bb = b[i], c = (a[i] + bb - ans % bb) % bb;
            ll g = exgcd(aa, bb, x, y), bg = bb / g;
            if (c % g != 0) return -1;
            x = qmul(x, c / g, bg);
            ans += x * M;
            M *= bg;
            ans = (ans % M + M) % M;
        }
        return ans;
    }
};

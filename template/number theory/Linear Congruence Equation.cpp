// ax ≡ b (mod n)

// vector <ll> X;
ll linear_congruence_equation(ll a, ll b, ll n) {
    if (a < 0) a = (a % n + n) % n;
    if (b < 0) b = (b % n + n) % n;
    // X.clear();
    ll x, y, g;
    exgcd(a, n, g, x, y);
    if (b % g != 0) return -1;
    ll x0 = (x * (b / g)) % n;
    // rep(i, 0, g) X.pb((x0 + i * (n / g)) % n);
    ll d = n / g;
    return (x0 % d + d) % d;
}

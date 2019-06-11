// ax + by = gcd(a, b)

void exgcd(ll a, ll b, ll &g, ll &x, ll &y) {
    if (!b) { g = a; x = 1; y = 0; }
    else { exgcd(b, a % b, g, y, x); y -= x * (a / b); }
}

char s[N];
ull Hash[N], p[N];
set <ull> S;
void Init()
{
    S.clear();
    ull base = 2333333333333333;
    p[0] = 1;
    Hash[0] = 0;
    int len = strlen(s + 1);
    rep(i, 1, N) p[i] = p[i-1] * base;
    rep(i, 1, len+1) Hash[i] = Hash[i-1] * base + (s[i] - 'a' + 1);
}

ull GetHash(int l, int r)
{
    return Hash[r] - Hash[l-1] * p[r-l+1];
}

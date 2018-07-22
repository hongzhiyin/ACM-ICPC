void msort(int l, int r) {
    if (l >= r) return;
    int m = (r + l) >> 1;
    msort(l, m);
    msort(m+1, r);
    int i = l, j = m+1;
    b.clear();
    while (i <= m && j <= r)
        if (a[i] < a[j]) b.pb(a[i++]);
        else ans += m - i + 1, b.pb(a[j++]);  // ans 为逆序对数
    while (j <= r) b.pb(a[j++]);
    while (i <= m) b.pb(a[i++]);
    rep(i, 0, sz(b)) a[l+i] = b[i];
}

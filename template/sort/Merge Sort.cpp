int b[N], ans;
void msort(int l, int r) {
    if (l >= r) return;
    int m = (r + l) >> 1;
    msort(l, m);
    msort(m+1, r);
    int i = l, j = m+1;
    rep(k, l, r+1) {
        if (j > r || i <= m && a[i] <= a[j]) b[k] = a[i++];
        else b[k] = a[j++], ans += m - i + 1;  // ans 为逆序对数
    }
    rep(k, l, r+1) a[k] = b[k];
}

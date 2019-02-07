vi dis;
void Discrete(int a[], int n) {
    dis.clear();
    rep(i, 1, n+1) dis.pb(a[i]);
    sort(all(dis));
    dis.erase(unique(all(dis)), dis.end());
    rep(i, 1, n+1) d[i] = lower_bound(all(dis), a[i]) - dis.begin() + 1;
}

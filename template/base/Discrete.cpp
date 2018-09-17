vi dis;
void Init() {
    dis.clear();
    rep(i, 0, n) scanf("%d", a+i), dis.pb(a[i]);
    sort(all(dis));
    dis.erase(unique(all(dis)), dis.end());
    rep(i, 0, n) d[i] = lower_bound(all(dis), a[i]) - dis.begin() + 1;  // 离散值从 1 开始
}

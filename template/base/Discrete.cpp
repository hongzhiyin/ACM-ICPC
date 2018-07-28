// 区间离散化
vector <pii> tmp;
bool cmp(pii a, pii b) { return a.se != b.se ? a.se < b.se : a.fi < b.fi; }
void discrete(pii *a, int n) {
    tmp.clear();
    rep(i, 0, n) tmp.pb(mp(a[i].fi, i)), tmp.pb(mp(a[i].se, i));
    sort(all(tmp));
    int tot = 0, pre = 0;
    rep(i, 0, sz(tmp)) {
        if (tmp[i].fi == pre) {
            tmp[i].fi = tot;
        } else {
            pre = tmp[i].fi;
            tmp[i].fi = ++tot;
        }
    }
    sort(all(tmp), cmp);
    for (int i = 0; i < sz(tmp); i+=2) {
        a[tmp[i].se].fi = tmp[i].fi;
        a[tmp[i].se].se = tmp[i+1].fi;
    }
}

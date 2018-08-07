// 将 a 的数据成员 x 离散化为 dx
vector <Node> a;
vector <T> dis;
void Init() {
    a.clear(); dis.clear(); dis.pb(-INF);
    T x, y, z;
    rep(i, 0, n) {
        scanf("%d%d%d", &x, &y, &z);
        a.pb(Node(x, y, z));
        dis.pb(x);
    }
    sort(all(a)); sort(all(dis));
    dis.erase(unique(all(dis)), dis.end());
    rep(i, 0, sz(a))
        a[i].dx = lower_bound(all(dis), a[i].x) - dis.begin();
}

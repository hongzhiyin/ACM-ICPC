struct Kruskal {
    int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }
    void Union(int x, int y) {
        int u = find(x), v = find(y);
        if (u != v) fa[u] = v;
    }
    ll kruskal() {
        ll sum = 0;
        sort(all(e));
        rep(i,0,sz(e)) {
            int u = e[i].se.fi, v = e[i].se.se;
            if (Find(u) != Find(v)) {
                sum += e[i].fi;
                Union(u, v);
            }
        }
        return sum;     //返回最小生成树的边权和
    }
};

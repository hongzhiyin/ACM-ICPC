vi Q;
ll d[N];
int cnt[N];
bool vis[N];
vector <pii> e[N];
bool spfa(int s) {
    memset(d, 0x3f, sizeof(d));   // 判正环时设为 0
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    d[s] = 0;   // 判正环时设为初值
    vis[s] = cnt[s] = 1;
    Q.clear(); Q.pb(s);
    rep(i, 0, sz(Q)) {
        int u = Q[i];
        vis[u] = 0;
        for (auto x : e[u]) {
            int v = x.fi, w = x.se;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                if (!vis[v]) {
                    Q.pb(v);
                    cnt[v] += vis[v] = 1;
                    if (cnt[v] > n) return 0;   // 存在负环
                }
            }
        }
    }
    return 1; // 无负环
}

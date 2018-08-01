vector <pii> e[N];
queue <int> Q;
int d[N];
bool vis[N];
int cnt[N];
struct SPFA {
    void init() {
        memset(d, 0x3f, sizeof(d));   // 判正环时设为 0
        memset(vis, 0, sizeof(vis));
        memset(cnt, 0, sizeof(cnt));
        while (!Q.empty()) Q.pop();
    }
    bool spfa(int s) {
        d[s] = 0;   // 判正环时设为初值
        vis[s] = cnt[s] = 1;
        Q.push(s);
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            vis[u] = 0;
            rep(i, 0, sz(e[u])) {
                int v = e[u][i].fi, w = e[u][i].se;
                if (d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                    if (!vis[v]) {
                        Q.push(v);
                        vis[v] = 1;
                        cnt[v]++;
                        if (cnt[v] > n) return false;
                    }
                }
            }
        }
        return true;
    }
};

int f[N][30], dep[N];
struct LCA {
    void init() { memset(f, 0, sizeof(f)); memset(dep, 0, sizeof(dep)); }   // 如果不用 init() 可能可以省空间
    void dfs(int u, int p, int d) {
        f[u][0] = p; dep[u] = d;
        rep(j, 1, 30) f[u][j] = f[f[u][j-1]][j-1];
        rep(i, 0, sz(e[u])) {
            int v = e[u][i];
            if (v != p) dfs(v, u, d+1);
        }
    }
    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = 29, d = dep[u] - dep[v]; i >= 0; --i)
            if (d >> i & 1) u = f[u][i];
        if (u == v) return u;
        per(i, 0, 30) if (f[u][i] != f[v][i])
            u = f[u][i], v = f[v][i];
        return f[u][0];
    }
};

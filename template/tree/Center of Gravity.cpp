int g[2], sz[N], minsz;
void Gravity (int u, int f) {
    if (f == 0) { g[0] = g[1] = -1; minsz = INF; }
    sz[u] = 1;
    int mx = 0;
    for (auto v : e[u]) if (v != f)  {
        Gravity(v, u);
        sz[u] += sz[v];
        mx = max(mx, sz[v]);
    }
    mx = max(mx, n - sz[u]);  // n : 树的总结点数
    if (mx < minsz) {
        minsz = mx;
        g[0] = u; g[1] = -1;
    } else if (mx == minsz) {
        g[1] = u;
        if (g[0] > g[1]) swap(g[0], g[1]);
    }
}

int no, in[N], top[N];
void dfs(int u) {
    top[u] = ++no;
    for (auto v : e[u]) if (!--in[v]) dfs(v);
}

void Init() {
    no = 0;
    memset(in, 0, sizeof(in));
    memset(top, 0, sizeof(top));
    rep(i, 1, n+1) if (!in[i] && !top[i]) dfs(i);
}

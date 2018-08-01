// tarjan
// dfn[] dfs 序;
// low[] dfs 序最小结点;
// scc[] 所属强联通分量
// tot dfs 序号
// cnt 强联通分量数
int dfn[N], low[N], scc[N], tot, cnt;
stack <int> S;
struct SCC {
    void init() {
        tot = cnt = 0;
        memset(scc, 0, sizeof(scc));
        memset(dfn, 0, sizeof(dfn));
    }
    void dfs(int u) {
        dfn[u] = low[u] = ++tot;
        S.push(u);
        rep(i, 0, sz(e[u])) {
            int v = e[u][i];
            if (!dfn[v]) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (!scc[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u]) {
            cnt++; int x;
            do {
                x = S.top(); S.pop();
                scc[x] = cnt;
            } while (x != u);
        }
    }
    void run(int n) { rep(i, 0, n) if (!dfn[i]) dfs(i); }
};

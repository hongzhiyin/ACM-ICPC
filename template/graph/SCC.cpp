// poj 1236
// https://www.cnblogs.com/kuangbin/archive/2011/08/07/2130277.html
// 缩点：遍历原图所有的边，当发现两个端点不属于同一个强联通分量时，即为新图的边，端点即为两个强联通分量的序号
// 使一张图强联通，即将所有入度为 0 的点和出度为 0 的点相连，如果找不到对应的点，就随便取一个点相连，所需加的边数即为：max(in, out)
// 选择最少的点使得从这些点出发能遍历整个有向图，点的个数即为：入度为 0 的点的个数

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
    void run(int n) { rep(i, 1, n+1) if (!dfn[i]) dfs(i); }
};

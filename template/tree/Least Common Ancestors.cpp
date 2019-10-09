/* 倍增
【函数功能】
void dfs(int u, int p, int d) : 根结点 u ; 父节点 p ; 深度 d
int lca(int u, int v)	      : 返回 u 和 v 的最近公共祖先

【注意事项】
1. 如果超时，改用邻接表
*/

struct LCA {
    int f[N][21], dep[N];
    void dfs(int u, int p, int d) {	// dfs(rt, rt, 0)
        f[u][0] = p; dep[u] = d;
        rep(j, 1, 21) f[u][j] = f[f[u][j-1]][j-1];
        for (auto v : e[u]) if (v != p) dfs(v, u, d+1);
    }
    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = 20, d = dep[u] - dep[v]; i >= 0; --i)
            if (d >> i & 1) u = f[u][i];
        if (u == v) return u;
        per(i, 0, 21) if (f[u][i] != f[v][i])
            u = f[u][i], v = f[v][i];
        return f[u][0];
    }
};

// 求路径长度、最值
    ll sum[N][21];
    ll op(ll a, ll b) { return ? ; }
    void dfs(int u, int p, int d, ll w) {
        f[u][0] = p; dep[u] = d; sum[u][0] = w;
        rep(j, 1, 21) {
            f[u][j] = f[f[u][j-1]][j-1];
            sum[u][j] = op(sum[f[u][j-1]][j-1], sum[u][j-1]);
        }
        for (auto v : e[u]) if (v.fi != p) dfs(v.fi, u, d+1, v.se);
    }
    ll dist(int u, int v) {
        int p = lca(u, v);
        ll d1 = 0, d2 = 0;
        for (int i = 20, d = dep[u] - dep[p]; i >= 0; --i)
            if (d >> i & 1) d1 = op(d1, sum[u][i]), u = f[u][i];
        for (int i = 20, d = dep[v] - dep[p]; i >= 0; --i)
            if (d >> i & 1) d2 = op(d2, sum[v][i]), v = f[v][i];
        return op(d1, d2);
    }

// 离线 tarjan
vi e[N];
vector <pii> q[N];  // 事先存下询问
bool vis[N];
int fa[N], lca[N];  // 答案存在 lca[] ，下标为询问序号
struct LCA {
    void init() { memset(vis, 0, sizeof(vis)); };
    int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
    void dfs(int u) {
        fa[u] = u; vis[u] = 1;
        rep(i, 0, sz(q[u])) {       // 这两个循环不能对调顺序，否则会造成重复更新答案
            int v = q[u][i].fi;
            if (vis[v]) lca[q[u][i].se] = find(v);
        }
        rep(i, 0, sz(e[u])) {
            int v = e[u][i];
            if (!vis[v]) dfs(v), fa[v] = u;
        }
    }
};

================================================== Problem Set ==================================================

// https://nanti.jisuanke.com/t/31462
// 题意：最少的花费删除图中某些边，使得询问的点对存在唯一最短路，输出最短路长度
// 题解：求最大生成树， LCA 求树上两点距离
int Solve() {
    rep(i, 1, n+1) rep(j, 1, m+1) {
        char ch[5]; int c1, c2;
        scanf("%s%d%s%d", ch, &c1, ch, &c2);
        int id1 = m * (i - 1) + j, id2 = m * i + j, id3 = m * (i - 1) + j + 1;
        if (i < n) edge.pb(mp(-c1, mp(id1, id2)));
        if (j < m) edge.pb(mp(-c2, mp(id1, id3)));
    }
    kruskal();
	dfs(1, 0, 0, 0);
    int q; scanf("%d", &q);
    while (q--) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        int u = m * (x1 - 1) + y1;
        int v = m * (x2 - 1) + y2;
        printf("%lld\n", dist(u, v));
    }
}

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

----------------------------------------------------------------------------------------------------

// poj 3728
// 离线 tarjan 求 lca 的运用

// up[x] 表示从 x 走到 lca 的最优解
// down[x] 表示从 lca 走到 x 的最优解
// mx[x], mi[x] 分别表示 x 和 lca 之间的最大值和最小值
int n, Q, mx[N], mi[N], up[N], down[N];
int ans[N];
struct Node {
    int from, to, id;
    Node () {}
    Node (int u, int v, int id) : from(u), to(v), id(id) {}
};
vector <Node> lca[N];
vi e[N];
vector <pii> q[N];  // 事先存下询问
bool vis[N];
int fa[N];
struct LCA {
    void init() { memset(vis, 0, sizeof(vis)); };
    int find(int x) {   // 通过并查集从上往下更新从 lca 到 x 的路径信息
        if (x == fa[x]) return x;
        int f = fa[x];
        fa[x] = find(fa[x]);
        // 每次都从 LCA 开始往下逐级更新，逐渐延长这条从 LCA 开始的链
        // 每次更新到某个点，就设该点为最大值或最小值，然后从前面这条链中取出对应的值
        // 从而更新这个点对应的四个值 up , down, mi, mx
        // 这时这个点相当于带有前面这条链上的信息，相当于链被更新到了这个点
        // 然后继续拿新的链向下扩展更新下面的点
        up[x] = max(up[x], max(up[f], mx[f] - mi[x]));
        down[x] = max(down[x], max(down[f], mx[x] - mi[f]));
        mx[x] = max(mx[x], mx[f]);
        mi[x] = min(mi[x], mi[f]);
        return fa[x];
    }
    void dfs(int u) {
        fa[u] = u; vis[u] = 1;
        rep(i, 0, sz(q[u])) {       // 查询询问和 dfs 两个循环不能对调顺序，否则会造成重复更新答案
            int v = q[u][i].fi;
            if (vis[v]) {
                int x = find(v), id = q[u][i].se;
                // 保存以 x 为 lca 的所有询问节点对
                lca[x].pb(id > 0 ? Node(u, v, id) : Node(v, u, -id));
            }
        }
        rep(i, 0, sz(e[u])) {
            int v = e[u][i];
            if (!vis[v]) dfs(v), fa[v] = u;
        }
        rep(i, 0, sz(lca[u])) {
            int from = lca[u][i].from, to = lca[u][i].to, id = lca[u][i].id;
            find(from); find(to); // 及时更新从 lca 到 from 和 to 的链
            ans[id] = max(mx[to] - mi[from], max(up[from], down[to]));
        }
    }
};
LCA obj;

void Init() {
    memset(up, 0, sizeof(up));
    memset(down, 0, sizeof(down));
    rep(i, 1, n+1) e[i].clear(), q[i].clear();
    obj.init();

    rep(i, 1, n+1) {
        int w; scanf("%d", &w);
        mx[i] = mi[i] = w;
    }
    rep(i, 1, n) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].pb(v);
        e[v].pb(u);
    }
    scanf("%d", &Q);
    rep(i, 1, Q+1) {
        int u, v;
        scanf("%d%d", &u, &v);
        q[u].pb(mp(v, i));
        q[v].pb(mp(u, -i));     // 负数表示路径反向
    }
}

int Solve() {
    obj.dfs(1);
    rep(i, 1, Q+1) printf("%d\n", ans[i]);
    return 0;
}

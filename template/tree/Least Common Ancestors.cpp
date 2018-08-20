// 倍增
vi e[N];
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

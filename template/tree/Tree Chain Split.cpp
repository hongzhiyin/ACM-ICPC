/* ----- 树链剖分 -----
< 准备 >
    1. 树边集 vector<int> e[N]
    
< 使用 >
    1. 调用 tr.run(rt) 进行树链剖分， rt 为树的根节点，得
    .. dep[] : 节点深度，根节点深度为 1
    .. fa[]  : 当前节点的父亲节点
    .. sz[]  : 以当前节点为根的子树大小（包括子树根节点）
    .. son[] : 当前节点的重儿子，即以重儿子为根的子树最大
    .. top[] : 树链剖分后，当前节点所在树链中，深度最小的节点
    .. id[]  : 树链剖分后，当前节点的新编号
    2. 调用 tr.build(n, a, b) 后
    .. 将原始节点的点权 a[] 转换到新编号节点的点权 b[] 中
    .. 并将新节点按顺序，以差分数组的形式，更新到树状数组中
    3. tr.upd_road(u, v, w) : 从 u 到 v 的路径上的所有点权加上 w
    4. tr.qry_road(u, v)    : 查询从 u 到 v 的路径上的所有点权之和
    5. tr.upd_tree(rt, w)   : 以 rt 为根的子树中的所有点权加上 w
    6. tr.qry_tree(rt)      : 查询以 rt 为根的子树中的所有点权之和
    
< 注意 >
    1. 涉及树状数组的部分，才会使用节点的新编号 id[]
    2. 使用支持区间查询的树状数组，即树状数组内保存的是差分数组
*/

int dep[N], fa[N], sz[N], son[N], top[N], id[N], no;
struct Tree_Chain_Split {
    void dfs_1(int u, int f = 0) {
        dep[u] = dep[f] + (sz[u] = 1);
        for (auto v : e[u]) if (v != f) {
            dfs_1(v, u);
            sz[fa[v] = u] += sz[v];
            if (sz[v] > sz[son[u]]) son[u] = v;
        }
    }
    void dfs_2(int u) {
        if (son[fa[u]] == u) top[u] = top[fa[u]];
        else top[u] = u;
        id[u] = ++no;
        if (son[u]) dfs_2(son[u]);
        for (auto v : e[u]) if (v != fa[u] && v != son[u])
            dfs_2(v);
    }
    void run(int rt) { dep[0] = no = 0; dfs_1(rt); dfs_2(rt); }
    void build(int n, int a[], int b[]) {
        rep(i, 1, n+1) b[id[i]] = a[i];
        rep(i, 1, n+1) fen.upd(i, b[i] - b[i-1]);
    }
    void upd_road(int u, int v, int w) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            fen.upd(id[top[u]], id[u], w);
            u = fa[top[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        fen.upd(id[u], id[v], w);
    }
    ll qry_road(int u, int v) {
        ll sum = 0;
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            sum += fen.qry(id[top[u]], id[u]);
            u = fa[top[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        sum += fen.qry(id[u], id[v]);
        return sum;
    }
    void upd_tree(int rt, int w) { fen.upd(id[rt], id[rt] + sz[rt] - 1, w); }
    ll qry_tree(int rt) { return fen.qry(id[rt], id[rt] + sz[rt] - 1); };
} tr;


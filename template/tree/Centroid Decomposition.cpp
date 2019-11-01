/* ----- 点分治 -----
< 准备 >
    1. 树的边集 vi e[]
    
< 使用 >
    1. 调用 obj.init(n) 初始化
    2. 调用 obj.run(n) 执行点分治，在 calc(rt) 中统计答案
*/

struct Centroid_Decomposition {
    int vis[N], sz[N], cnt;
    void init(int n) { memset(vis, 0, sizeof(vis[0]) * (n+1)); }
    void Gravity(int u, int f, int n, int &rt) {
        sz[u] = 1;
        for (auto v : e[u]) if (!vis[v] && v != f) { Gravity(v, u, n, rt); sz[u] += sz[v]; }
        if (!rt && sz[u] * 2 > n) rt = u;
    }
    void run(int u) {
        int rt;
        Gravity(u, 0, 0, rt);
        Gravity(u, 0, sz[u], rt = 0);
        vis[rt] = 1;
        calc(rt);
        for (auto v : e[rt]) if (!vis[v]) run(v);
    }
    
    // 根据具体问题编写 calc(rt) 函数
    struct node { int grp, dis; } a[N];
    void dfs(int u, int f = 0, int d = 0, int g = 0) {
        a[cnt].dis = d; a[cnt++].grp = g;
        for (auto o : e[u]) if (!vis[o.fi] && o.fi != f)
            dfs(o.fi, u, d + o.se, g ? g : o.fi);
    }
    void find_equal_k(int u) {  // 查找长度等于 k 的路径
        cnt = 0;
        dfs(u);
        Radix_Sort((ll*)a, cnt);
        int R = cnt - 1;
        rep(L, 0, cnt) {
            while (R > L && a[L].dis + a[R].dis > k) R--;
            while (R > L && a[L].dis + a[R].dis == k && a[L].grp == a[R].grp) R--;
            if (L >= R) break;
            if (a[L].dis + a[R].dis == k) { ans = 1; break; }
        }
    }
} obj;

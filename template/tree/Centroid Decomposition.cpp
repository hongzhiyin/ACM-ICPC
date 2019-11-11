/* ----- 点分治 -----
< 准备 >
    1. 树的边集 vi e[]
    
< 使用 >
    1. 调用 obj.init(n) 初始化
    2. 调用 obj.run(1) 执行点分治，在 calc(rt) 中统计答案
*/

struct Centroid_Decomposition {
    int vis[N], sz[N];
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
    
    // ----- 查找长度等于 k 的路径 ----- //
    int cnt;
    struct node { int grp, dis; } a[N];
    void dfs(int u, int f = 0, int d = 0, int g = 0) {
        a[cnt].dis = d; a[cnt++].grp = g;
        for (auto o : e[u]) if (!vis[o.fi] && o.fi != f)
            dfs(o.fi, u, d + o.se, g ? g : o.fi);
    }
    void calc(int u) {
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
    // -------------------------------- //
    
    // ----- 经过每个节点的路径中，至多一种字符出现奇数次的路径数 ----- //
    void dfs(int u, int f = 0, int mask = 0, int val = 1) {
        mask ^= 1 << s[u];
        cnt[mask] += val;
        for (auto v : e[u]) if (!vis[v] && v != f) dfs(v, u, mask, val);
    }
    ll work(int u, int f, int mask = 0) {
        mask ^= 1 << s[u];
        ll sum = cnt[mask];
        rep(i, 0, 20) sum += cnt[mask ^ 1 << i];
        for (auto v : e[u]) if (!vis[v] && v != f) sum += work(v, u, mask);
        ans[u] += sum;
        return sum;
    }
    void Init() { memset(cnt, 0, sizeof(cnt[0])); }
    void calc(int u) {
        dfs(u);
        ll sum = cnt[0];
        rep(i, 0, 20) sum += cnt[1 << i];
        for (auto v : e[u]) if (!vis[v]) {
            dfs(v, u, 1 << s[u], -1); 
            sum += work(v, u);
            dfs(v, u, 1 << s[u], 1);
        }
        ans[u] += sum / 2;
        dfs(u, 0, 0, -1);
    }
    // -------------------------------------------------------- //
} obj;

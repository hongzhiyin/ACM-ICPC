/* ----- 可视化 -----
< 使用 >
    1. n 和 m 分别为画布行数与列数
    2. clear()        : 清空画布
    3. print()        : 打印画布
    4. print(r, c, x) : 在坐标 (r, c) 的位置打印数字 x
    5. tree(n, e, rt) : 打印一棵 n 个节点、根节点为 rt 的树，边集保存在 vi e[] 中
*/

struct Visualization {
    char v[200][200];
    int n = 40, m = 90;
    vi e[N]; int w[N];

    void clear() { rep(i, 0, n) rep(j, 0, m) v[i][j] = ' '; }
    void print() { rep(i, 0, n) { rep(j, 0, m) printf("%c", v[i][j]); puts(""); } }
    void print(int r, int c, int x) {
        v[r][c] = x < 10 ? x + '0' : x / 10 + '0';
        v[r][c+1] = x < 10 ? ' ' : x % 10 + '0';
    }

    void tree_dfs(int u) {
        w[u] = sz(e[u]) ? 3 * (sz(e[u]) - 1) : 1;
        for (auto v : e[u]) { tree_dfs(v); w[u] += w[v]; }
    }
    void tree_draw(int u, int row = 0, int col = 0) {
        print(row, col+w[u]/2, u);
        if (sz(e[u]) == 0) return;
        v[row+1][col+w[u]/2] = '|';
        int st = w[e[u][0]] / 2, ed = w[u] - (w[e[u].back()] + 1) / 2;
        rep(i, st, ed+1) v[row+2][col+i] = '.';
        for (auto v : e[u]) { tree_draw(v, row+3, col); col += w[v] + 3; }
    }
    void tree(int n, vi _e[], int rt = 1) {
        clear();
        rep(i, 0, n+1) e[i] = _e[i];
        tree_dfs(rt);
        tree_draw(rt);
        print();
    }
} view;

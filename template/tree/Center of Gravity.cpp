/* ----- 树的重心 -----
< 定义 >
    1. 以重心为根的树，在删除根节点后，剩余子树中，最大的子树最小。
    2. 树的重心至多有 2 个

< 准备 >
    1. 树的边集 vi e[] ，树的节点总数 n
    
< 使用 >
    1. 调用 Gravity(n, u) ， n 为树的节点总数， u 为任取树上一点，得
    .. g[0] 和 g[1] 保存树的重心的节点编号，只有一个重心时， g[1] = -1
*/

int g[2], sz[N], minsz;
void Gravity(int n, int u, int f = 0) {
    if (f == 0) { g[0] = g[1] = -1; minsz = INF; }
    sz[u] = 1;
    int mx = 0;
    for (auto v : e[u]) if (v != f)  {
        Gravity(n, v, u);
        sz[u] += sz[v];
        mx = max(mx, sz[v]);
    }
    mx = max(mx, n - sz[u]);
    if (mx < minsz) { minsz = mx; g[0] = u; g[1] = -1; }
    else if (mx == minsz) g[1] = u;
}

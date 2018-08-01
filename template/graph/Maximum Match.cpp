// 最大匹配
// 选择边数最大的子图称为图的最大匹配问题 (maximal matching problem)
// 如果一个匹配中，图中的每个顶点都和图中某条边相关联，则称此匹配为完全匹配，也称作完备匹配。
// https://blog.csdn.net/c20180630/article/details/70175814

vi e[N];
int link[N];
bool vis[N], g[N][N];
struct Hungary {
    void init() { memset(link, 0, sizeof(link)); }
    bool dfs(int u) {
        rep(i, 0, sz(e[u])) {
            int v = e[u][i];
            if (g[u][v] && !vis[v]) {
                vis[v] = 1;
                if (!link[v] || dfs(link[v])) {
                    link[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    int hungary() {
        int res = 0;
        rep(i, 1, n+1) {
            memset(vis, 0, sizeof(vis));
            res += dfs(i);
        }
        return res;
    }
};

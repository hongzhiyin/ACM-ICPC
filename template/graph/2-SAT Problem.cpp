/* ----- 2-SAT 问题 -----
< 准备 >
    1. 根据约束条件建图 e[] ， u -> v 表示 u 成立时 v 必成立
    .. 下标从 1 开始
    
< 使用 >
    1. 调用 sat.run(n) ，
    .. 返回值 0 表示无解
    .. 返回值 1 表示有解， n 个布尔变量的解储存在 sat.val[] 中
    
< 注意 >
    1. 因为每个布尔变量有两个值，所以点数 N 应开两倍
    .. 点 i+n 表示点 i 的反值
*/

struct Two_SAT {
    int val[N], dfn[N], low[N], scc[N], S[N], top, cnt, no;
    void SCC(int u) {
        dfn[u] = low[u] = ++no;
        S[top++] = u;
        for (auto v : e[u]) {
            if (!dfn[v]) {
                SCC(v);
                low[u] = min(low[u], low[v]);
            } else if (!scc[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u]) {
            cnt++;
            do { scc[S[--top]] = cnt; } while (S[top] != u);
        }
    }
    int run(int n) {
        no = top = cnt = 0;
        memset(dfn, 0, sizeof(dfn[0]) * (2*n+1));
        memset(scc, 0, sizeof(scc[0]) * (2*n+1));
        rep(i, 1, 2*n+1) if (!dfn[i]) SCC(i);
        rep(i, 1, n+1) if (scc[i] == scc[i+n]) return 0;
        rep(i, 1, n+1) val[i] = (scc[i] < scc[i+n]);
        return 1;
    }
} sat;

/*
< 准备 >
    1. 有向图边集 vector<int> e[] ，顶点编号从 1 开始

< 使用 >
    1. 调用 Scc.run(n) ， n 为有向图顶点数，得
    .. dfn[i] : 点 i 的 dfs 序，从 1 开始
    .. low[i] : 点 i 能到达的最小 dfs 序
    .. scc[i] : 点 i 所属强连通分量的编号，从 1 开始
    .. cnt : 强连通分量个数
    2. 调用 Scc.run(n) 后即完成了缩点，得
    .. 缩点后新图的边集 vector<int> e2[]

< 注意 >
    1. 缩点建新图的过程中，可增加统计其他所需的信息，如入度、出度等。
*/

vi e2[N];
int dfn[N], low[N], scc[N], S[N], top, cnt, no;
struct Strongly_Connected_Component {
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
    void run(int n) {
        no = top = cnt = 0;
        memset(dfn, 0, sizeof(dfn[0]) * (n+1));
        memset(scc, 0, sizeof(scc[0]) * (n+1));
        rep(i, 1, n+1) if (!dfn[i]) SCC(i);
        rep(i, 1, cnt+1) e2[i].clear();                    // 缩点前初始化
        rep(u, 1, n+1) for (auto v : e[u])                 // 缩点部分
            if (scc[u] != scc[v]) e2[scc[u]].pb(scc[v]);
    }
} Scc;

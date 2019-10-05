/* ----- 点双连通分量 -----
< 准备 >
    1. 有向图边集 vector<int> e[] ，顶点编号从 1 开始

< 使用 >
    1. 调用 vbc.run(n) ， n 为有向图顶点数，得
    .. dfn[i] : 点 i 的 dfs 序，从 1 开始
    .. low[i] : 点 i 能到达的最小 dfs 序
    .. cut[i] : 点 i 是否为割点
    .. id[i]  : 缩点建新图后，给割点 i 新的编号 id[i]
    .. dcc[i] : 点 i 所属点双连通分量的编号，从 1 开始
    .. cnt    : 点双连通分量个数
    .. Dcc[i] : 第 i 个点双连通分量，点保存在 vector 中
    2. 调用 vbc.run(n) 后即完成了缩点，得
    .. 新图点数为 num
    .. 新图的边集 vector<int> e2[]

< 注意 >
    1. 缩点后，新图的点数可能比原图的点数多，但不会超过原图点数的两倍
    .. 样例：考虑一条链的情况
    .. 证明：新图点数 = 原图割点数 + 点双分量数，二者皆小于等于原图点数
*/

vi Dcc[N], e2[N<<1];
int dfn[N], low[N], cut[N], id[N], dcc[N], S[N], top, cnt, num, no;
struct Vertex_Biconnected_Component {
    void DCC(int u, int rt) {
        dfn[u] = low[u] = ++no;
        S[top++] = u;
        if (e[u].empty()) { Dcc[++cnt].pb(u); return ; }
        int son = 0;
        for (auto v : e[u]) {
            if (!dfn[v]) {
                DCC(v, rt);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    son++;
                    if (u != rt || son > 1) cut[u] = 1;
                    cnt++;
                    do { Dcc[cnt].pb(S[--top]); } while (S[top] != v);
                    Dcc[cnt].pb(u);
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
    void run(int n) {
        no = top = cnt = 0;
        memset(dfn, 0, sizeof(dfn[0]) * (n+1));
        memset(cut, 0, sizeof(cut[0]) * (n+1));
        rep(i, 1, n+1) Dcc[i].clear();
        rep(i, 1, n+1) if (!dfn[i]) DCC(i, i);
        num = cnt;
        rep(i, 1, n+1) if (cut[i]) id[i] = ++num;
        rep(i, 1, num+1) e2[i].clear();
        rep(i, 1, cnt+1) for (auto o : Dcc[i]){
            if (cut[o]) { e2[i].pb(id[o]); e2[id[o]].pb(i); }
            else dcc[o] = i;
        }
    }
} vbc;

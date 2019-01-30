/*
【变量定义】
dfn[i] : 点 i 的 dfs 序
low[i] : 点 i 能到达的 dfs 序最小的结点
scc[i] : 点 i 所属的强联通分量标号，从 1 开始
cut[i] : 点 i 是否为割点
tot    : dfs 序号
cnt    : 强联通分量个数

【函数功能】
void init()                  : 初始化
void run(int n)              : 调用所需函数
void SCC(int u)              : 求强联通分量
void CutPoint(int u, int fa) : 求割点
*/

vi e[N];
struct Tarjan {
    int dfn[N], low[N], tot;
    void init() {
        tot = 0; cnt = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(scc, 0, sizeof(scc));
        memset(cut, 0, sizeof(cut));
    }
    void run(int n) { rep(i, 1, n+1) if (!dfn[i]) function(i); }
    int scc[N], cnt; stack <int> S;
    void SCC(int u) {   // 求强联通分量
        dfn[u] = low[u] = ++tot;
        S.push(u);
        for(auto v : e[u]) {
            if (!dfn[v]) {
                SCC(v);
                low[u] = min(low[u], low[v]);
            } else if (!scc[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u]) {
            cnt++; int x;
            do {
                x = S.top(); S.pop();
                scc[x] = cnt;
            } while (x != u);
        }
    }
    bool cut[N];
    void CutPoint(int u, int fa) { // 求割点
        dfn[u] = low[u] = ++tot;
        int son = 0;
        for (auto v : e[u]) {
            if (!dfn[v]) {
                CutPoint(v, fa);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u] && u != fa) cut[u]=1;
                if (u == fa) son++;
            }
            low[u] = min(low[u], dfn[v]);
        }
        if (son >= 2 && u == fa) cut[u] = 1;
    }
};

================================================== Problem Set ==================================================

// poj 1236
// https://www.cnblogs.com/kuangbin/archive/2011/08/07/2130277.html
// 缩点：遍历原图所有的边，当发现两个端点不属于同一个强联通分量时，即为新图的边，端点即为两个强联通分量的序号
// 使一张图强联通，即将所有入度为 0 的点和出度为 0 的点相连，如果找不到对应的点，就随便取一个点相连，所需加的边数即为 : max(in, out)
// 选择最少的点使得从这些点出发能遍历整个有向图，点的个数即为 : 入度为 0 的点的个数

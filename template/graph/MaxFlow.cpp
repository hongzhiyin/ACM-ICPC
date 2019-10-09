/*
< 准备 >
    1. 点数 N ，边数 M

< 使用 >
    1. 调用 mxf.init(T) 初始化， T 表示最大点编号（该编号一般作为汇点）
    2. 调用 mxf.addEdge(s, t, v) 建图：
    .. 加一条从 s 到 t ，容量为 v 的有向边
    .. 无向边即为两条有向边
    3. 调用 mxf.dinic(S, T) ，得
    .. 返回值 maxflow : 最大流

< 注意 >
    1. 运行一次 mxf.dinic(S, T) 之后，残量网络改变，不能再次运行 mxf.dinic(S, T)
*/
struct MaxFlow {
    int n, no, dis[N], Q[N], cur[N], head[N];
    struct Edge {
        int s, t, v, net;
        Edge () {}
        Edge (int s, int t, int v, int net) : s(s), t(t), v(v), net(net) {}
    } e[M<<1];
    void init(int _n) {
        n = _n, no = 0;
        memset(head, -1, sizeof(head[0]) * (n+1));
    }
    void addEdge(int s, int t, int v) {
        e[no] = Edge(s, t, v, head[s]), head[s] = no++;
        e[no] = Edge(t, s, 0, head[t]), head[t] = no++;
    }
    bool bfs(int S, int T) {
        int qh = 0, qt = 0;
        memset(dis, -1, sizeof(dis[0]) * (n+1));
        dis[S] = 0, Q[qt++] = S;
        while (qh < qt) for (int i = head[Q[qh++]]; ~i; i = e[i].net) {
            if (e[i].v && !~dis[e[i].t]) {
                dis[Q[qt++] = e[i].t] = 1 + dis[e[i].s];
                if (e[i].t == T) return 1;
            }
        }
        return 0;
    }
    ll dinic(int S, int T) {
        int u, qt;
        ll maxflow = 0;
        while (bfs(S, T)) {
            memcpy(cur, head, sizeof(cur[0]) * (n+1));
            u = S, qt = 0;
            while (~cur[S]) {
                if (u == T) {
                    ll flow = LINF;
                    per(i, 0, qt) flow = min(flow, (ll)e[Q[i]].v);
                    per(i, 0, qt) {
                        e[Q[i]].v -= flow, e[Q[i]^1].v += flow;
                        if (!e[Q[i]].v) qt = i;
                    }
                    u = e[Q[qt]].s, maxflow += flow;
                } else if (~cur[u] && e[cur[u]].v && dis[u]+1 == dis[e[cur[u]].t]) {
                    Q[qt++] = cur[u];
                    u = e[cur[u]].t;
                } else {
                    while (u != S && !~cur[u]) u = e[Q[--qt]].s;
                    cur[u] = e[cur[u]].net;
                }
            }
        }
        return maxflow;
    }
} mxf;

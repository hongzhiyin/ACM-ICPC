// N : 点数 , M : 边数
struct MaxFlow {
    int n, no, dis[N], Q[N], cur[N], head[N];
    struct Edge {
        int s, t, v, net;
        Edge() {}
        Edge(int s, int t, int v, int net) : s(s), t(t), v(v), net(net) {}
    } e[M<<1];
    void init(int _n) {     // _n 为最大点编号 + 1
        n = _n, no = 0;
        memset(head, -1, sizeof(head[0]) * n);  // 去掉结构体会影响到这里和下面的 n
    }
    void addEdge(int s, int t, int v) {
        e[no] = Edge(s, t, v, head[s]), head[s] = no++;
        e[no] = Edge(t, s, 0, head[t]), head[t] = no++;
    }
    bool bfs(int S, int T) {
        int qh = 0, qt = 0;
        memset(dis, -1, sizeof(dis[0]) * n);
        dis[S] = 0, Q[qt++] = S;
        while (qh < qt)
            for (int i = head[Q[qh++]]; ~i; i = e[i].net)
                if (e[i].v && !~dis[e[i].t]) {
                    dis[Q[qt++] = e[i].t] = 1 + dis[e[i].s];
                    if (e[i].t == T) return true;
                }
        return false;
    }
    ll dinic(int S, int T) {
        int u, qt;
        ll maxflow = 0;
        while (bfs(S, T)) {
            memcpy(cur, head, sizeof(cur[0]) * n);
            u = S, qt = 0;
            while (~cur[S]) {
                if (u == T) {
                    ll flow = LINF;
                    per(i, 0, qt) flow = min(flow, (ll)e[Q[i]].v);
                    per(i, 0, qt) {
                        e[Q[i]].v -= flow, e[Q[i]^1].v += flow;
                        if (!e[Q[i]].v)    qt = i;
                    }
                    u = e[Q[qt]].s, maxflow += flow;
                } else if (~cur[u] && e[cur[u]].v
                        && dis[u] + 1 == dis[e[cur[u]].t]) {
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
};

================================================== Problem Set ==================================================

// luogu P2756
// 题意：二分图最大匹配，输出方案
// 题解：建超级源点和超级汇点，分别连流量为 1 的边，跑最大流
int Solve() {
    obj.init(n+2);  // 最大点编号 + 1
    int u, v;
    while (~scanf("%d%d", &u, &v)) {
        if (u == -1 || v == -1) break;
        obj.addEdge(u, v, 1);
    }
    S = 0, T = n + 1;
    rep(i, 1, m+1) obj.addEdge(S, i, 1);
    rep(i, m+1, n+1) obj.addEdge(i, T, 1);

    ll ans = obj.dinic(S, T);
    if (!ans) return puts("No Solution!");
    printf("%lld\n", ans);
    for (int i = 0; i < obj.no; i += 2) {
        if (obj.e[i].s != S && obj.e[i].t != S) {   // 如果不是连接源点的边（没判断汇点是因为 break ）
            if (obj.e[i^1].v != 0)  // 如果反向边流量不为 0 ，说明该正向边有流量通过
                printf("%d %d\n", obj.e[i].s, obj.e[i].t);
        } else break;   // 因为加边的顺序，当出现连接源点的边时，说明已经遍历所有匹配边
    }
    return 0;
}

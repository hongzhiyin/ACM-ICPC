// k 短路
// https://nanti.jisuanke.com/t/31445
// 建立反向边 re ，以终点 E 为起点跑最短路，然后在正向边 e 中跑 A*
int dist[N];
bool inq[N];
Vector e[N], re[N];
priority_queue <pii> Q;
void spfa(int s) {
    memset(dist, 0x3f, sizeof(dist));
    memset(inq, 0, sizeof(inq));
    Q.push(mp(dist[s] = 0, s));
    inq[s] = 1;
    while (!Q.empty()) {
        int u = Q.top().se; Q.pop();
        inq[u] = 0;
        for (int i = re[u].head; i; i = net[i]) { // 反向边
            int v = node[i].fi, w = node[i].se;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!inq[v]) {
                    Q.push(mp(-dist[v], v));
                    inq[v] = 1;
                }
            }
        }
    }
}

struct A {
    int f, g, v;
    bool operator < (const A a) const {
        if(a.f == f) return a.g < g;
        return a.f < f;
    }
};
int Astar(int src, int des, int k) {  // 若 k 短路不存在，返回 -1 ，否则返回路径长度
    int cnt = 0;
    priority_queue <A> Q;
    if (src == des) k++;
    if (dist[src] == INF) return -1;
    A t, tt;
    t.v = src, t.g = 0, t.f = t.g + dist[src];
    Q.push(t);
    while(!Q.empty()) {
        tt = Q.top(); Q.pop();
        if(tt.v == des && ++cnt == k) return tt.g;
        for(int i = e[tt.v].head; i; i = net[i]) {  // 正向边
            t.v = node[i].fi;
            t.g = tt.g + node[i].se;
            t.f = t.g + dist[t.v];
            Q.push(t);
        }
    }
    return -1;
}

int Solve() {
    no = 0;
    rep(i, 1, n+1) e[i].clear(), re[i].clear();

    scanf("%d%d%d%d", &S, &E, &K, &T);
    rep(i, 0, m) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        e[u].pb(mp(v, w));  // 正向边
        re[v].pb(mp(u, w)); // 反向边
    }
    spfa(E);
    int ans = Astar(S, E, K);
    return puts(ans != -1 && ans <= T ? "yareyaredawa" : "Whitesnake!");
}

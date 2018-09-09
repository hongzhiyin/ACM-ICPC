int dist[N];
bool done[N];
vector <pii> e[N];
priority_queue <pii> Q;
void dijkstra(int s) {
    memset(dist, 0x3f, sizeof(dist));
    memset(done, 0, sizeof(done));
    Q.push(mp(dist[s] = 0, s));
    while (!Q.empty()) {
        int u = Q.top().se; Q.pop();
        if (done[u]) continue; done[u] = true;
        rep(i, 0, sz(e[u])) {
            int v = e[u][i].fi, w = e[u][i].se;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                Q.push(mp(-dist[v], v));
            }
        }
    }
}

================================================== Problem Set ==================================================

// cf 229B
// 题意： n 个点， m 条边，每个点有若干个时刻不能出发，求从 1 到 n 的最短时间
set <int> S[N];     // S[i] 存下在 i 点的所有不能出发的时刻
void dijkstra(int s) {
    Q.push(mp(dist[s] = 0, s));
    while (!Q.empty()) {
        int u = Q.top().se; Q.pop();
        if (done[u]) continue;
        done[u] = true;

        // 当要以当前点 u 去松弛其他点时
        int go = dist[u];
        while (S[u].count(go)) go++;

        rep(i, 0, sz(e[u])) {
            int v = e[u][i].fi, w = e[u][i].se;
            if (dist[v] > go + w) {
                dist[v] = go + w;
                Q.push(mp(-dist[v], v));
            }
        }
    }
}

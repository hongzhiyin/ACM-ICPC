int dist[N];
bool done[N];
vector <pii> e[N];
priority_queue <pii> Q;
struct Dijkstra {
    void init(int n) {
        while (!Q.empty()) Q.pop();
        memset(dist, 0x3f, sizeof(dist));
        memset(done, 0, sizeof(done));
        rep(i, 0, n+1) e[i].clear();
    }
    void dijkstra(int s) {
        Q.push(mp(dist[s] = 0, s));
        while (!Q.empty()) {
            int u = Q.top().se; Q.pop();
            if (done[u]) continue;
            done[u] = true;
            rep(i, 0, sz(e[u])) {
                int v = e[u][i].fi, w = e[u][i].se;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    Q.push(mp(-dist[v], v));
                }
            }
        }
    }
};

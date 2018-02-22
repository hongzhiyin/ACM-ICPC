struct Dijkstra {   //注意：点的标号是从0开始 rep(i,0,n)
    int n;
    ll dist[N];
    bool done[N];
    vector < pair<int, ll> > e[N];

    void Init(int n) {  //从 1 开始就传入 n + 1
        this->n = n;
        rep(i, 0, n) e[i].clear();
    }

    void AddEdge(int u, int v, ll w) {
        e[u].pb({v, w});
    }

    void dijkstra(int s) {
        priority_queue < pair<ll, int> > Q;
        rep(i,0,n) dist[i] = LINF;
        memset(done, 0, sizeof(done));
        Q.push({dist[s] = 0, s});
        while (!Q.empty()) {
            int u = Q.top().se; Q.pop();
            if (done[u]) continue;
            done[u] = true;
            rep(i, 0, sz(e[u])) {
                int v = e[u][i].fi;
                ll w = e[u][i].se;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    Q.push({-dist[v], v});
                }
            }
        }
    }
};

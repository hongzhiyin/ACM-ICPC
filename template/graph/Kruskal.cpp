struct Kruskal {

    struct Edge {
        int from, to, dist;
        Edge(int u, int v, int d) : from(u), to(v), dist(d) {}
        bool operator < (const Edge &rhs) const { return dist < rhs.dist; }
    };

    int n, fa[N];
    vector<Edge> edge;

    void Init(int n) {
        this -> n = n;
        rep(i, 0, n) fa[i] = i;
        edge.clear();
    }

    int Find(int x) {
        return fa[x] == x ? x : fa[x] = Find(fa[x]);
    }

    void Union(int a,int b) {
        int Fa = Find(a),Fb = Find(b);
        if (Fa != Fb) fa[Fb] = Fa;
    }

    void AddEdge(int from, int to, int dist) {
        edge.pb(Edge(from, to, dist));
    }

    ll kruskal() {
        ll sum = 0;
        sort(all(edge));
        rep(i,0,sz(edge)) {
            Edge &e = edge[i];
            if (Find(e.from) != Find(e.to)) {
                sum += e.dist;
                Union(e.from, e.to);
            }
        }
        return sum;     //返回最小生成树的边权和
    }
    
};

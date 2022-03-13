template <typename distType>
class Dijkstra {
    int n;
    vector<bool> done;
    vector<distType> dist;
    vector<vector<pair<int, distType>>> edge;
    void init() {
        fill(done.begin(), done.end(), 0);
        fill(dist.begin(), dist.end(), sizeof(distType) == 4 ? 0x3f3f3f3f : 0x3f3f3f3f3f3f3f3f);
    }
public:
    Dijkstra(int _n) : n(_n + 1), done(n), dist(n), edge(n) {}
    distType dis(int id) { return dist[id]; }
    void addEdge(int from, int to, int weight) {
        edge[from].push_back(make_pair(to, weight));
    }
    void dijkstra(int start) {
        init();
        priority_queue<pair<distType, int>> Q;
        Q.push(make_pair(dist[start]=0, start));
        while (!Q.empty()) {
            int u = Q.top().second; Q.pop();
            if (done[u]) continue; done[u] = true;
            for (auto &[v, w] : edge[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    Q.push(make_pair(-dist[v], v));
                }
            }
        }
    }
};

/*
时间复杂度 : O( (V+E)logV )
准备 :
    e[] : 边集
输入 :
    s : 起点
输出 :
    dist[i] : 从起点 s 到点 i 的最短距离
注意 :

*/

// int pre[N];  // PrintRoad
T dist[N];
bool done[N];
vector < pair<int, T> > e[N];
priority_queue < pair<T, int> > Q;
void dijkstra(int s) {
    memset(dist, 0x3f, sizeof(dist));
    memset(done, 0, sizeof(done));
    Q.push(mp(dist[s] = 0, s));
    while (!Q.empty()) {
        int u = Q.top().se; Q.pop();
        if (done[u]) continue; done[u] = true;
        rep(i, 0, sz(e[u])) {
            int v = e[u][i].fi; T w = e[u][i].se;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                // pre[v] = u;  // PrintRoad
                Q.push(mp(-dist[v], v));
            }
        }
    }
}

vi road;
void PrintRoad(int S, int T) {
    road.clear(); road.pb(T);
    int v = T;
    while (v != S) {
        v = pre[v];
        road.pb(v);
    }
    per(i, 0, sz(road))
        printf("%d%c", road[i], " \n"[i==0]);
}

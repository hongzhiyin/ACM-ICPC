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

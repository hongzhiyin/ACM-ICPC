/*
【函数功能】
void bfs(int rt, int *dis, int *fa)
1. 以 rt 为根进行 bfs
2. dis[i] 表示点 i 到 rt 的距离
3. fa[i] 表示点 i 在以 rt 为根的树中的父节点

void Diameter()
1. 两遍 bfs 求出直径
2. 第一遍任取一点 bfs 找到最远一点，即为直径一端
3. 第二遍以直径一端 bfs 找到最远一点，即为直径另一端

【使用方法】
1. 调用 Diameter()
2. 树的直径保存在 vector <int> dim 中
3. dis[i] 表示点 i 到 dim[0] 的距离
4. fa[i] 表示点 i 在以 dim[0] 为根的树中的父节点

【性质】
1. 直径之外的点，距离其最远的点一定是直径的端点

*/

vi Q;
void bfs(int rt, int *dis, int *fa) {
    rep(i, 1, n+1) dis[i] = INF, fa[i] = -1;
    dis[rt] = 0;
    Q.clear(); Q.pb(rt);
    rep(i, 0, sz(Q)) {
        int u = Q[i];
        for (auto v : e[u]) {
            if (dis[v] != INF) continue;
            dis[v] = dis[u] + 1;
            fa[v] = u;
            Q.pb(v);
        }
    }
}

vi dim;
int dis[N], fa[N];
void Diameter() {
    int p[2] = {1, 1};
    rep(j, 0, 2) {
        bfs(p[!j], dis, fa);
        rep(i, 1, n+1) if (dis[p[j]] < dis[i]) p[j] = i;
    }
    dim.clear();
    for (int v = p[1]; v != p[0]; v = fa[v]) dim.pb(v);
    dim.pb(p[0]);
    reverse(all(dim));
}

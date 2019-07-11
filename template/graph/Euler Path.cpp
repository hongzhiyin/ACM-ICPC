int eno, to[N<<1], net[N<<1], head[N];
void AddEdge(int u, int v) {
    to[++eno] = v; net[eno] = head[u]; head[u] = eno;
}

vi path;
bool vis[N];
int top, sta[N];
void EulerPath(int st) {
    sta[++top] = st;
    while (top) {
        int u = sta[top], i = head[u];
        while (i && vis[i]) i = net[i];
        if (i) {
            sta[++top] = to[i];
            vis[i] = vis[i ^ 1] = 1;  // 标记当前这条无向边
            head[u] = net[i];  // 修改表头，删除已访问过的边
        } else {
            top--;
            path.pb(u);
        }
    }
}

void Init() {
    eno = 1;  // 初始化边编号，方便存储正反边
    rep(i, 0, m) {
        int u, v; scanf("%d%d", &u, &v);
        AddEdge(u, v); AddEdge(v, u);
    }
}

int Solve() {
    EulerPath(1);  // 以 1 为起点
    per(i, 0, sz(path)) printf("%d\n", path[i]);  // 路径需逆序输出
    return 0;
}

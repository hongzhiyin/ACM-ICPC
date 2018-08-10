struct Floyd {
    int n;
    int d[N][N];
    void Init(int n) {
        this->n = n;
        memset(d,0x3f,sizeof(d));
        rep(i, 0, n) d[i][i] = 0;
    }
    void AddEdge(int from, int to, int dist) {
        d[from][to] = min(d[from][to], dist);
    }
    void floyd() {
        rep(k, 0, n) rep(i, 0, n) rep(j, 0, n)
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    }
    void connect() {    // 检验连通性
        rep(k, 0, n) rep(i, 0, n) rep(j, 0, n)
            d[i][j] = d[i][j] || (d[i][k] && d[k][j]);
    }
    // road() 要结合 circle() 判断图中是否包含回路
    void road() {       // 从 i 到 j 的路径总数
        rep(k, 0, n) rep(i, 0, n) rep(j, 0, n)
            d[i][j] += d[i][k] * d[k][j];
    }
    void circle() {
        rep(k, 0, n) if (d[k][k]) {     // 如果中间节点 k 可以自己到达自己，说明存在经过 k 的回路
            rep(i, 0, n) rep(j, 0, n) if (d[i][k] && d[k][j])   // 那么所有经过节点 k 的路径
                d[i][j] = -1;                                   // 都是无穷多的
        }
    }
};

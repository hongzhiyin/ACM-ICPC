struct Floyd {
    int n;
    int d[N][N];
    void Init(int n) {
        this->n = n;
        memset(d,0x3f,sizeof(d));
        rep(i,0,n) d[i][i] = 0;
    }
    void AddEdge(int from, int to, int dist) {
        d[from][to] = min(d[from][to], dist);
    }
    void floyd() {
        rep(k,0,n) rep(i,0,n) rep(j,0,n)
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    }
    void connect() {
        rep(k,0,n) rep(i,0,n) rep(j,0,n)
            d[i][j] = d[i][j] || (d[i][k] && d[k][j]);
    }
};

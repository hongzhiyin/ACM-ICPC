vi Dcc[N];
bool cut[N];
int dfn[N], low[N], S[N], top, cnt, no;
void DCC(int u, int rt) {
    dfn[u] = low[u] = ++no;
    S[top++] = u;
    if (e[u].empty()) { Dcc[++cnt].pb(u); return ; }
    int son = 0;
    for (auto v : e[u]) {
        if (!dfn[v]) {
            DCC(v, rt);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                son++;
                if (u != rt || son > 1) cut[u] = 1;
                cnt++;
                do { Dcc[cnt].pb(S[--top]); } while (S[top] != v);
                Dcc[cnt].pb(u);
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

vi e2[N];
int id[N], dcc[N];
void run(int n) {
    no = top = cnt = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(cut, 0, sizeof(cut));
    rep(i, 1, n+1) Dcc[i].clear();
    rep(i, 1, n+1) if (!dfn[i]) DCC(i, i);
    int num = cnt;
    rep(i, 1, n+1) if (cut[i]) id[i] = ++num;
    rep(i, 1, num+1) e2[i].clear();
    rep(i, 1, cnt+1) for (auto o : Dcc[i]){
        if (cut[o]) { e2[i].pb(id[o]); e2[id[o]].pb(i); }
        else dcc[o] = i;
    }
}

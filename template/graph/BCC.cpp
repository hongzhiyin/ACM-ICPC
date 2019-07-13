/*
【注意】
  1. 缩点时，因为遍历的是原图的点，所以只需要加单向边，另一个方向的边在遍历到对面的点时就会加入。
*/

bool bri[N];
vector <pii> e[N];
int dfn[N], low[N], bcc[N], S[N], top, cnt, no;
void BCC(int u, int eid) {
    dfn[u] = low[u] = ++no;
    S[top++] = u;
    for (auto o : e[u]) {
        int v = o.fi, id = o.se;
        if (!dfn[v]) {
            BCC(v, id);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) bri[id] = 1;
        } else if (id != eid) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        ++cnt;
        do { bcc[S[--top]] = cnt; } while (S[top] != u);
    }
}

vi e2[N];
void run(int n) {
    no = top = cnt = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(bri, 0, sizeof(bri));
    memset(bcc, 0, sizeof(bcc));
    rep(i, 1, n+1) if (!dfn[i]) BCC(i, 0);
    rep(i, 1, cnt+1) e2[i].clear();
    rep(u, 1, n+1) for (auto o : e[u])
        if (bcc[u] != bcc[o.fi]) e2[bcc[u]].pb(bcc[o.fi]);
}

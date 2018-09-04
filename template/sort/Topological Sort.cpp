================================================== Problem Set ==================================================

// cf 1037E
// 题意： n 个点，每次加一条边，求当前图中最大的点集合，集合中的点的度数都大于等于 k
// 题解：反向操作，依次删边，再通过拓扑排序把不符合要求的点都删掉
int Solve() {
  rep(i, 0, m) {
        int u, v; scanf("%d%d", &u, &v);
        a[i] = mp(u, v);
        e[u].pb(i);
        e[v].pb(i);
        in[u]++; in[v]++;
    }
    int tot = n;
    rep(i, 1, n+1) if (in[i] < k) Q.push(i);
    per(i, 0, m) {
        while (!Q.empty()) {
            int u = Q.front(); Q.pop(); tot--;
            for (int i = e[u].head; i; i = net[i]) {
                int eno = node[i];
                if (vis[eno]) continue; vis[eno] = 1;   // vis[eno] 表示编号为 eno 的边已经被删了
                int v = a[eno].fi == u ? a[eno].se : a[eno].fi;
                if (--in[v] == k - 1) Q.push(v);  // 如果 in[v] < k-1 说明 v 之前已经入队了
            }
        }
        ans[i] = tot;
        if (!tot) break;
        if (vis[i]) continue; vis[i] = 1;
        int u = a[i].fi, v = a[i].se;
        if (--in[u] < k) Q.push(u);
        if (--in[v] < k) Q.push(v);
    }
    rep(i, 0, m) printf("%d\n", ans[i]);
}

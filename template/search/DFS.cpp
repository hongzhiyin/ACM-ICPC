================================================== Problem Set ==================================================

// cf 917B
// 题意：
// 给一个有向图，每条边的边权都是一个字母的 ASCLL 码值，有两个人从起点 i 和起点 j 走起，
// 每次所走的边权必须大于等于上一个人所走的边权，第一个无法走的人失败，另一个人获胜，输出所有起点 i 和 j 的获胜情况。
// 题解：
// dfs 搜索所有的状态转移
bool dfs(int first, int second, int pre) {
    // dp[first][second][pre] 表示先手在 first ，后手在 second ，上一步权值为 pre 时，先手为必胜态还是必败态
    if (~dp[first][second][pre]) return dp[first][second][pre];
    bool win = 0;
    rep(i, 0, sz(e[first])) {   // 如果找到一个点 third ，使得从 first 走到 third 后，能使后手落入必败态，则先手为必胜态
        int third = e[first][i].fi, w = e[first][i].se;
        if (w < pre) continue;
        win |= !dfs(second, third, w);
    }
    return dp[first][second][pre] = win;
}
int Solve() {
    rep(i, 0, m) {
        int u, v; char w[5];
        scanf("%d%d%s", &u, &v, w);
        e[--u].pb(mp(--v, w[0]-'a'));
    }
    rep(i, 0, n) {
        rep(j, 0, n) putchar(dfs(i, j, 0) ? 'A' : 'B');
        puts("");
    }
}

----------------------------------------------------------------------------------------------------

// http://codeforces.com/gym/101142 C
// 题意：如果 A > B 并且 B > C , 那么有 A > C , 现在 A > B 的条件是， A 的两个元素中的至少一个大于 B 。问一个人可以打败多少人
// 题解：按每一分量排序，相邻连边，最后从小到大（随便某一分量） dfs 每一个点，小的点能到达的点，大的点也一定能到达，所以叠加 cnt
void dfs(int u) {
	++cnt;
	vis[u] = 1;
	for (auto v : e[u]) if (!vis[v]) dfs(v);
}
int Solve() {
	sort(a, a + n, [&](Node a, Node b){ return a.x < b.x; });
	rep(i, 1, n) e[a[i].id].pb(a[i-1].id);
	sort(a, a + n, [&](Node a, Node b){ return a.y < b.y; });
	rep(i, 1, n) e[a[i].id].pb(a[i-1].id);
	cnt = 0;
    rep(i, 0, n) {
		if (!vis[a[i].id]) dfs(a[i].id);
		ans[a[i].id] = cnt - 1;
	}
	rep(i, 0, n) printf("%d\n", ans[i]);
}

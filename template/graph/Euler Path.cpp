void dfs(int u) {
    for (auto &v : e[u]) if (v.se) {
        v.se = 0;
        dfs(v.fi);
        ans.pb(mp(v.fi, u));
    }
}
void Solve() {  // 输出从 start 出发的一条欧拉路径（回路），根据度数定义找到正确的起始点
    dfs(start);
    for (auto x : ans) printf("%d %d\n", x.fi, x.se);
}

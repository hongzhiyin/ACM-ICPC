// hdu 4714
// 删边和连边的代价都为 1 ，求将一棵树变成一个环的最小代价
// https://blog.csdn.net/tobewhatyouwanttobe/article/details/11538439
// 如果一个节点的分支数 >= 2 ，则该节点需与其父节点断开（当然根节点就不用了）
// 即去掉一条边形成一个游离的链，所有游离的链需要增加一条边连接在根节点所在的链上
// 然后再用一条边将这条长链首位相连

// dfs 返回值表示是否与父节点连接
int dfs(int u, int f) {
    int sum = 0;
    for (int i = e[u].head; i; i = net[i]) {
        int v = node[i];
        if (v == f) continue;
        sum += dfs(v, u);
    }
    if (sum > 1) {
        if (u == 1) ans += 2 * (sum - 2);
        else ans += 2 * (sum - 1);
        return 0;
    }
    return 1;
}
int Solve() {
    dfs(1, 0);
    return !printf("%d\n", ans+1);
}

----------------------------------------------------------------------------------------------------

// poj 2255
// 已知先序遍历，中序遍历，求后序遍历

void build(int len, char *DLR, char *LDR) {     // DLR: 先序遍历 LDR: 中序遍历
    if (len == 0) return;
    int pos = strchr(LDR, DLR[0]) - LDR;
    build(pos, DLR + 1, LDR);
    build(len - pos - 1, DLR + pos + 1, LDR + pos + 1);
    putchar(DLR[0]);
}
int Solve() {
    int len = strlen(DLR);
    build(len, DLR, LDR);
    puts("");
}

================================================== Problem Set ==================================================

// cf 1037D
// 题意：判断一个 BFS 序列是否合法，规定 BFS 从 1 开始
// 题解：
// 以 1 为根节点进行 dfs ，存下每个节点的父节点，然后依次把给定序列的元素入队，
// 当队首元素非当前序列元素的父节点时，队首出队，如果前面所有的元素都非该元素的父节点，则该 BFS 序列不合法。
int Solve() {
    if (a[0] != 1) return !puts("No");
    dfs(1, 0);
    Q.push(1);
    rep(i, 1, n) {
        int v = a[i], u = Q.front();
        Q.push(v);
        while (Q.front() != v && fa[v] != Q.front()) Q.pop();
        if (Q.front() == v) return !puts("No");
    }
    return !puts("Yes");
}

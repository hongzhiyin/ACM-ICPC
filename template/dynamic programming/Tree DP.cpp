================================================== Problem Set ==================================================

// cf 954H
// 题意：给一棵 n 层的树，第 i 层的每个节点有 a[i] 个儿子节点，问树上的简单路径中长度在 1 ~ 2*(n-1) 之间的分别有多少条
// 题解：
// 对于路径，只有两种情况， " \ " 和 " ^ " 这两种形状
// down[i][j] 表示在 i 层的 1 个节点，直接向下走 j 步的方案数，即第一种情况
// up[i][j] 表示在 i 层的 1 个节点，第一步必须向上走，共走 j 步的方案数，即第二种情况
// 则方程为：
// down[i][j] = a[i] * down[i+1][j-1]
// up[i][j] = up[i-1][j-1] + (a[i-1] - 1) * down[i][j-2]
// 由于空间限制，且根据递推关系，按照 i 从小到大， j 从大到小的循环顺序， up 的更新不会影响到 down ，所以两者可以使用同一数组

#define up down
int Solve() {
    rep(i, 1, n) scanf("%d", a+i);
    sum[1] = 1;
    rep(i, 2, n+1) sum[i] = mul(sum[i-1], a[i-1]);

    per(i, 1, n+1) {
        down[i][0] = 1;   // 这里也相当于为下面做了 up[i][0] = 1;
        rep(j, 1, n-i+1) {
            down[i][j] = mul(a[i], down[i+1][j-1]);
            ans[j] = add(ans[j], mul(sum[i], down[i][j]));
        }
    }
    
    rep(j, 1, n+1) up[1][j] = 0;
    rep(i, 2, n+1) {
        per(j, 1, 2*(n-1)+1) {
            up[i][j] = up[i-1][j-1];
            if (j >= 2) up[i][j] = add(up[i][j], mul(a[i-1]-1, down[i][j-2]));
            ans[j] = add(ans[j], mul(sum[i], up[i][j]));
        }
    }
    rep(i, 1, 2*(n-1)+1) printf("%d%c", mul(ans[i], 500000004), " \n"[i==2*(n-1)]);
    return 0;
}

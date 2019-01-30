/*
【注意事项】
1. lower_bound : 严格上升 ; upper_bound : 非严格上升
*/

int g[N];
int LIS(int a[], int n) {
    int res = 0;
    rep(i, 1, n+1) g[i] = INF;
    rep(i, 0, n) {
        int k = lower_bound(g+1, g+n+1, a[i]) - g;  // k 表示以 a[i] 结尾的最长子序列的长度
        res = max(res, k);
        g[k] = a[i];
    }
    return res; // 返回最长上升子序列长度
}

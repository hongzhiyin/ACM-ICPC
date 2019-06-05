/*
【注意事项】
1. lower_bound : 严格上升 ; upper_bound : 非严格上升
2. 最长下降 : a[i] = -a[i] 即可， g[i] 不用变

【结论】
1. 判断 a[i] 是否可能在 LIS 中 :
    若 dp1[i] + dp2[i] - 1 == mxlen ，则 a[i] 可能在 LIS 中
    dp1[i] : 以 a[i] 为终点的 LIS 长度
    dp2[i] : 以 a[i] 为起点的 LIS 长度
    mxlen : 序列的 LIS 的长度
   
2. 判断可能在 LIS 中的元素是否在全部 LIS 中 :
    若在 a[i] 左边的所有可能在 LIS 中的元素中，有值大于等于 a[i] 的元素，
    或在 a[i] 右边的所有可能在 LIS 中的元素中，有值小于等于 a[i] 的元素，
    则 a[i] 不可能在全部 LIS 中。
    反之，则 a[i] 在全部 LIS 中。

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

/*
【注意事项】
1. a[] 从 1 开始
2. 根据需要修改 min or max
3. 固定起点的区间的最值具有单调性，可依此进行二分
*/

int lg[N]; T d[N][21];
struct ST {
    void init(T a[], int n) {
        rep(i, 1, n+1) d[i][0] = a[i];
        rep(j, 1, 21) for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            d[i][j] = op(d[i][j-1], d[i + (1 << (j-1) )][j-1]);
        lg[1] = 0; rep(i, 2, n+1) lg[i] = lg[i>>1] + 1;
    }
    T qry(int l, int r) {
        int k = lg[r-l+1];
        return op(d[l][k], d[r-(1<<k)+1][k]);
    }
} rmq;

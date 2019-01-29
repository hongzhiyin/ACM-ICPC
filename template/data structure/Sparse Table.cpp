/*
【函数功能】
void Init(T a[], int n) : 以长度为 n 的数组 a[] 初始化 ST 表
T Qry(int L, int R)     : 询问区间 [L, R] 的最值

【注意事项】
1. a[] 从 1 开始
2. 根据需要修改 min or max
3. 固定起点的区间的最值具有单调性，可依此进行二分
*/

template <class T>
struct ST {
    int lg[N]; T d[N][30];
    void Init(T a[], int n) {
        rep(i, 1, n+1) d[i][0] = a[i];
        rep(j, 1, 30) for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            d[i][j] = max(d[i][j-1], d[i + ( 1 << (j-1) )][j-1]);
        lg[1] = 0; rep(i, 2, n+1) lg[i] = lg[i>>1] + 1;
    }
    T Qry(int L, int R) {
        int k = lg[R - L + 1];
        return max(d[L][k], d[R - (1<<k) + 1][k]);
    }
};

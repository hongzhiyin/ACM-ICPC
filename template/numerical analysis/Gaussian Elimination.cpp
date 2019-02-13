/*
【变量定义】
x[i]    : 对应变量的解
used[i] : used[i] == 1 表示 x[i] 不是自由变量
a[][]   : 増广矩阵

【注意事项】
1. 参数 n 和 m 表示系数矩阵的大小，不是增广矩阵
*/

const db eps = 1e-7;
bool used[N];
double x[N], a[N][N];
int gauss(int n, int m) { // 1 : 唯一解 ; 0 : 非唯一解 ; -1 : 无解
    int row, col;
    for (row = col = 0; row < n && col < m; ++row, ++col) {
        int mxr = row;
        rep(i, row+1, n) if (fabs(a[i][col]) > fabs(a[mxr][col])) mxr = i;
        if (fabs(a[mxr][col]) < eps) {
            --row;
            continue;
        }
        if (mxr != row) swap(a[row], a[mxr]);
        rep(i, 0, n) if (i != row && fabs(a[i][col]) > eps)
            per(j, col, m+1) a[i][j] -= a[row][j] * a[i][col] / a[row][col];
    }
    if (row == n && n == m) {
        rep(i, 0, n) x[i] = a[i][m] / a[i][i];
        return 1;
    }
    rep(i, row, n) if (a[i][m] > eps) return -1;
    memset(used, false, sizeof(used[0]) * m);
    rep(i, 0, row) {
        int cnt = 0, ind = -1;
        rep(j, 0, m) if (fabs(a[i][j]) > eps && !used[j])
            ++cnt, ind = j;
        if (cnt == 1)
            x[ind] = a[i][m] / a[i][ind], used[ind] = 1;
    }
    rep(i, 0, m) if (!used[i]) return 0;
    return 1;
}

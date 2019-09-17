/*
【准备】
    增广矩阵 a[n][m+1] ，下标从 0 开始

【使用】
    调用 Gaussian_Elimination(n, m) ，注意 n 和 m 为系数矩阵的大小，得：
      1. 返回值 ( 1 : 唯一解 ; 0 : 多解 ; -1 : 无解 )
      2. 解向量 x[m]
      3. 是否为自由元 used[m] ( 0 : 自由元 ; 1 : 非自由元 )
*/

const db eps = 1e-7;
bool used[N];
double x[N], a[N][N];
int Gaussian_Elimination(int n, int m) {  // 1 : 唯一解 ; 0 : 多解 ; -1 : 无解
    int row, col;
    for (row = col = 0; row < n && col < m; ++row, ++col) {
        int mxr = row;
        rep(i, row+1, n) if (fabs(a[i][col]) > fabs(a[mxr][col])) mxr = i;    // 寻找列主元，即系数最大
        if (fabs(a[mxr][col]) < eps) { --row; continue; }                     // 如果该列系数都为 0 ，从下一列开始
        if (mxr != row) swap(a[row], a[mxr]);                                 // 将列主元所在行与当前行交换
        rep(i, 0, n) if (i != row && fabs(a[i][col]) > eps)                   // 如果其他行尚未消元
            per(j, col, m+1) a[i][j] -= a[row][j] * a[i][col] / a[row][col];  // 对其他行进行消元
    }
    if (row == n && n == m) {                                                 // 若成功化为对角阵
        rep(i, 0, n) x[i] = a[i][m] / a[i][i];                                // 求出解向量
        return 1;                                                             // 返回唯一解
    }
    rep(i, row, n) if (a[i][m] > eps) return -1;                              // 系数为 0 ，结果不为 0 ，返回无解
    memset(used, false, sizeof(used[0]) * m);                                 // 初始化设所有解都为自由元
    rep(i, 0, row) {
        int cnt = 0, ind = -1;
        rep(j, 0, m) if (fabs(a[i][j]) > eps && !used[j])                     // 统计该行系数不为 0 的自由元数量
            ++cnt, ind = j;
        if (cnt == 1)                                                         // 如果自由元只有一个
            x[ind] = a[i][m] / a[i][ind], used[ind] = 1;                      // 则该变量非自由元，求出对应的解
    }
    rep(i, 0, m) if (!used[i]) return 0;                                      // 若存在自由元，返回多解
    return 1;                                                                 // 返回唯一解
}

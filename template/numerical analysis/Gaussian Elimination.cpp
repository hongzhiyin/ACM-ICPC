/* ----- 高斯消元 -----
< 准备 >
    1. 增广矩阵 a[n][m+1] ，下标从 0 开始

< 使用 >
    1. 调用 Gaussian_Elimination(n, m) ，注意 n 和 m 为系数矩阵的大小，得：
    .. 返回值 ( 1 : 唯一解 ; 0 : 多解 ; -1 : 无解 )
    .. 解向量 x[m]
    .. 是否为自由元 used[m] ( 0 : 自由元 ; 1 : 非自由元 )
*/

const db eps = 1e-7;
bool used[N];
db x[N], a[N][N];
int Gaussian_Elimination(int n, int m) {
    int row, col;
    for (row = col = 0; row < n && col < m; ++row, ++col) {
        int mxr = row;
        rep(i, row+1, n) if (fabs(a[i][col]) > fabs(a[mxr][col])) mxr = i;    // 寻找列主元，即系数最大
        if (fabs(a[mxr][col]) < eps) { --row; continue; }                     // 如果该列系数都为 0 ，从下一列开始
        if (mxr != row) rep(j, col, m+1) swap(a[row][j], a[mxr][j]);          // 交换列主元所在行与当前行
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
        if (cnt == 1) x[ind] = a[i][m] / a[i][ind], used[ind] = 1;            // 自由元只有一个，则非自由元，求出对应解
    }
    rep(i, 0, m) if (!used[i]) return 0;                                      // 若存在自由元，返回多解
    return 1;                                                                 // 返回唯一解
}

---

// ----- 取模版本，使用方式同上 -----

bool used[N];
int x[N], a[N][N];
int Gaussian_Elimination(int n, int m) {
    int row, col;
    for (row = col = 0; row < n && col < m; ++row, ++col) {
        int r = row;
        while (r < n && !a[r][col]) ++r;                              // 找到列主元，即系数非 0
        if (r == n) { --row; continue; }                              // 如果该列系数都为 0 ，从下一列开始
        if (r != row) rep(j, col, m+1) swap(a[row][j], a[r][j]);      // 交换列主元所在行与当前行
        ll tmp = qpow(a[row][col], MOD-2);                            // 求列主元的逆元
        rep(j, col, m+1) a[row][j] = mul(a[row][j], tmp);             // 该行所有数乘以列主元的逆元
        rep(i, 0, n) if (i != row && a[i][col]) per(j, col, m+1)      // 如果其他行尚未消元
            a[i][j] = add(a[i][j], MOD - mul(a[row][j], a[i][col]));  // 对其他行进行消元
    }
    if (row == n && n == m) {                                         // 若成功化为对角阵
        rep(i, 0, n) x[i] = a[i][m];                                  // 求出解向量
        return 1;                                                     // 返回唯一解
    }
    rep(i, row, n) if (a[i][m]) return -1;                            // 系数为 0 ，结果不为 0 ，返回无解
    memset(used, false, sizeof(used[0]) * m);                         // 初始化设所有解都为自由元
    rep(i, 0, row) {
        int cnt = 0, ind = -1;
        rep(j, 0, m) if (a[i][j] && !used[j])                         // 统计该行系数不为 0 的自由元数量
            ++cnt, ind = j;
        if (cnt == 1) x[ind] = a[i][m], used[ind] = 1;                // 自由元只有一个，则非自由元，求出对应解
    }
    rep(i, 0, m) if (!used[i]) return 0;                              // 若存在自由元，返回多解
    return 1;                                                         // 返回唯一解
}

---

/* ----- 矩阵求逆 -----
< 准备 >
    1. 原矩阵和单位矩阵 a[n][n<<1] ，下标从 0 开始

< 使用 >
    1. 调用 Matrix_Inversion(n) ， n 为原矩阵的大小，得：
    .. 返回值 ( 1 : 矩阵可逆 ; 0 : 矩阵不可逆 )
    2. 将原矩阵化为单位矩阵后，原单位矩阵即为逆矩阵
*/

int a[N][N<<1];
int Matrix_Inversion(int n) {
    rep(r, 0, n) {
        int row = r;
        while (row < n && !a[row][r]) ++row;                      // 找到列主元，即系数非 0
        if (row == n) return 0;                                   // 该列系数都为 0 ，矩阵不可逆
        if (row != r) rep(j, r, n+n) swap(a[row][j], a[r][j]);    // 交换列主元所在行与当前行
        ll tmp = qpow(a[r][r], MOD-2);                            // 求列主元的逆元
        rep(j, r, n+n) a[r][j] = mul(a[r][j], tmp);               // 该行所有数乘以列主元的逆元
        rep(i, 0, n) if (i != r && a[i][r]) per(j, r, n+n)        // 如果其他行尚未消元
            a[i][j] = add(a[i][j], MOD - mul(a[r][j], a[i][r]));  // 对其他行进行消元
    }
    return 1;                                                     // 矩阵可逆
}

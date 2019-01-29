// 秦九韶算法
T Horner(T x) {
    T res = 0;
    rep(i, 0, n+1)
        res = res * x + a[i]; // a[i] 为第 i 次项系数
    return res;
}

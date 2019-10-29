/* ----- 基数排序 -----
< 准备 >
    1. 待排序数组 a[]

< 使用 >
    1. 调用 Radix_Sort(a, n)
    .. a 为待排序数组首地址，
    .. n 为数组元素个数
    .. 调用后 a[] 已从小到大排好序
*/

int _b[N];
inline void Radix_Sort(int *a, int n) {
    int t[4][0x100], *b = _b;
    memset(t, 0, sizeof(t));
    rep(i, 0, n) rep(j, 0, 4) ++t[j][(a[i] >> (j << 3)) & 0xff];
    rep(i, 1, 0x100) rep(j, 0, 4) t[j][i] += t[j][i-1];
    rep(j, 0, 4) {
        per(i, 0, n) b[--t[j][(a[i] >> (j << 3)) & 0xff]] = a[i];
        swap(a, b);
    }
}

/* ----- long long ----- */

ll _b[N];
inline void Radix_Sort(ll *a, int n) {
    int t[8][0x100]; ll *b = _b;
    memset(t, 0, sizeof(t));
    rep(i, 0, n) rep(j, 0, 8) ++t[j][(a[i] >> (j << 3)) & 0xff];
    rep(i, 1, 0x100) rep(j, 0, 8) t[j][i] += t[j][i-1];
    rep(j, 0, 8) {
        per(i, 0, n) b[--t[j][(a[i] >> (j << 3)) & 0xff]] = a[i];
        swap(a, b);
    }
}

/* ----- 基数排序 -----
< 准备 >
    1. 待排序数组 a[]

< 使用 >
    1. 调用 Radix_Sort(a, n)
    .. a 为待排序数组首地址，
    .. n 为数组元素个数
    .. 调用后 a[] 已从小到大排好序
    
< 注意 >
    1. 可以把一个包含两个 int 的结构体，强制转换成 long long ，然后使用基数排序
    .. struct { int a, b; } x[N]; Radix_Sort((ll*)x, n);
    .. 但要注意，若要求 a 为第一关键字， b 为第二关键字的话，结构体中的声明顺序应写为
    .. struct { int b, a; } x[N];
    .. 即优先级越高，声明顺序越后面，原因是
    .. 该结构体在内存中是按顺序存储， b 在低地址， a 在高地址
    .. 而一个 long long 类型在内存中的存储，也是高位在高地址，低位在低地址
    .. 因此 struct { int b, a; } 这样的结构体可看作是一个 long long 类型的数字 ab
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

================================================== Problem Set ==================================================

// cf 1028E
// 题意：给一数组 b[] ， b[i] = a[i] % a[(i+1)%n] ，构造 a[]
// 题解：
// 若 b[] 所有元素都相等
// 当 b[i] = 0 时， a[] 显然全为 0 ；
// 当 b[i] != 0 时，设 a[i] 为 a[] 中最小值，则 a[i] 只能为 b[i] ，但这样无法构造 a[i-1] ，则此情况无解
// 若 b[] 所有元素不都相等
// 找到 b[pos] == max 且 b[pos-1] != max ，则
// a[pos] = b[pos] , a[i] = (a[i] + ... + a[pos-1]) + 2 * a[pos]
// 2 * a[pos] 的原因在于若 b[i] 只有一个元素不为 0 且 a[i] = (a[i] + ... + a[pos-1]) + a[pos] ，
// 则 a[pos+1] == b[pos] ，即 a[pos] % a[pos+1] == 0 ，不符合条件
int Solve() {
    rep(i, 0, n) scanf("%lld", b+i);
    ll mx = *max_element(b, b + n), pos = -1;
    rep(i, 0, n) {
        if (b[i] == mx && b[(i-1+n)%n] < mx) {
            pos = i; break;
        }
    }
    if (!~pos) {
        if (mx == 0) {
            puts("YES");
            rep(i, 0, n) printf("1%c", " \n"[i==n-1]);
            return 0;
        } else {
            return !puts("NO");
        }
    }
    a[pos] = b[pos] << 1;
    rep(i, 1, n) {
        int p = (pos - i + n) % n;
        a[p] = a[(p+1)%n] + b[p];
    }
    a[pos] = b[pos];
    puts("YES");
    rep(i, 0, n) printf("%lld%c", a[i], " \n"[i==n-1]);
    return 0;
}

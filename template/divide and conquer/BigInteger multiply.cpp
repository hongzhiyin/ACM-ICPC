public static BigInteger calc(int l, int r) {
    if (l == r) return BigInteger.valueOf(a[l]);
    int m = l + r >> 1;
    return calc(l, m).multiply(calc(m + 1, r));
}

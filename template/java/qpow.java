public static BigInteger qpow(BigInteger a, long b) {
    BigInteger res = BigInteger.ONE;
    for (; b > 0; a = a.multiply(a)) {
        if (b % 2 == 1) res = res.multiply(a);
        b /= 2;
    }
    return res;
}

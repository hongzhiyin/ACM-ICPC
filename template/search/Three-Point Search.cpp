ll L = min, R = max;
while (L < R - 1) {
    ll m1 = L + (R - L) / 3, m2 = L + 2 * (R - L) / 3;
    if (work(m1) > work(m2)) {
        if (R == m2) R = m2 - 1;
        else R = m2;
    } else {
        if (L == m1) L = m1 + 1;
        else L = m1;
    }
}

// 浮点数
db L = min, R = max;
while (L + eps < R) {
    db M = (L + R) / 2;
    if (work(M + eps) > work(M - eps)) L = M;
    else R = M;
}
printf("%.5f\n", (L+R)/2);

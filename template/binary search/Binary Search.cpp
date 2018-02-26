//求最大值
int L = 0, R = max;
while (L < R) {
    int M = L + ((R - L + 1) >> 1);     //防止溢出，溢出可能造成TLE
    if (check(M)) L = M; else R = M - 1;
}
printf("%d\n", L);

//求最小值
int L = 0, R = max;
while (L < R) {
    int M = L + ((R - L) >> 1);
    if (check(M)) R = M; else L = M + 1;
}
printf("%d\n", L);

//浮点数
db L = 0, R = max;
while (!eq(L, R)) {
    db M = (L + R) / 2;
    if (check(M)) L = M;
    else R = M;
}
printf("%.4f\n", L);
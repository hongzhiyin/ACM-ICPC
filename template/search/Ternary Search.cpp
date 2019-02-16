// 凸函数求最大值

// 整数 ( 边界这样取是因为 : 对于整数，不存在 M 和 M + 1 落在最高点两端的情况 )
ll L = min, R = max;
while (L < R) {
    int M = L + ((R - L) >> 1);
    if (work(M) > work(M + 1)) R = M;
    else L = M + 1;
}
printf("%lld\n", L);

// 浮点数
db L = min, R = max;
while (L + eps < R) {
    db M = (L + R) / 2;
    if (work(M + eps) > work(M - eps)) L = M;
    else R = M;
}
printf("%.5f\n", (L+R)/2);

/*
    1. 终止条件 L == R
    2. 求最大值不会取到 L ，求最小值不会取到 R
    3. [l, r] 表示二分区间， l-1 和 r+1 表示越界下标，如果 L == R 等于越界下标，说明无解
*/

// 求最大值
int L = l - 1, R = r;
while (L < R) {
    int M = L + R + 1 >> 1;
    if (check(M)) L = M; else R = M - 1;
}

// 求最小值
int L = l, R = r + 1;
while (L < R) {
    int M = L + R >> 1;
    if (check(M)) R = M; else L = M + 1;
}

// 浮点数
db L = l, R = r;
while (!eq(L, R)) {     // 精度太小可能 TLE ，可以用固定次数的循环
    db M = (L + R) / 2;
    if (check(M)) L = M; else R = M;
}
printf("%.4f\n", 0.5 * (L + R));

// 各种莫名其妙的精度问题：
// 保留两位小数，其余位舍去：
printf("%.2f\n", floor(x * 100)/100);

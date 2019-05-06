// 勒让德定理
// 对 n! 分解质因数，则素数 p 的最高指数 L_p(n!) 等于：
// L_p(n!) = \sum_{q\ge1}\lfloor\frac{n}{p^q}\rfloor

ll Lp = 0, t = n;
while (t) Lp += (t /= p);

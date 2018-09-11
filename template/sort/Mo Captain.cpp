ll tmp;
void add(int p) { tmp.. }
void sub(int p) { tmp.. }
void mo() {
    int l = 1, r = 0;
    rep(i, 0, q) {
        for (; r < qry[i].r; ++r) add(r + 1);
        for (; r > qry[i].r; --r) sub(r);
        for (; l < qry[i].l; ++l) sub(l);
        for (; l > qry[i].l; --l) add(l - 1);
        ...
    }
}

================================================== Problem Set ==================================================

// luogu P1494
// 题意： n 只袜子，每只袜子都有颜色， q 个询问，每个询问求区间 [l, r] 内取两只袜子是同一颜色的概率
// 题解：
// 对于 [l, r] 的询问，设其中颜色为 x, y, z.. 的袜子的个数为 a, b, c..
// 那么答案即为 (a*(a-1)/2+b*(b-1)/2+c*(c-1)/2....) / ((R-L+1)*(R-L)/2)
// 化简得： (a^2+b^2+c^2+...x^2-(a+b+c+d+.....)) / ((R-L+1)*(R-L))
// 即： (a^2+b^2+c^2+...x^2-(R-L+1)) / ((R-L+1)*(R-L))
// 即：求一个区间内每种颜色数目的平方和
ll tmp;
void add(int p) { // x^2 + 2*x + 1 == (x+1)^2
    tmp += 2 * cnt[c[p]] + 1;
    cnt[c[p]]++;
}
void sub(int p) { // x^2 - 2*x + 1 == (x-1)^2
    tmp -= 2 * cnt[c[p]] - 1;
    cnt[c[p]]--;
}
void mo() {
    int l = 1, r = 0;
    rep(i, 0, q) {
        for (; r < qry[i].r; ++r) add(r + 1);
        for (; r > qry[i].r; --r) sub(r);
        for (; l < qry[i].l; ++l) sub(l);
        for (; l > qry[i].l; --l) add(l - 1);
        if (qry[i].l == qry[i].r) {
            qry[i].zi = 0;
            qry[i].mu = 1;
            continue;
        }
        ll len = qry[i].r - qry[i].l + 1;
        qry[i].zi = tmp - len;
        qry[i].mu = len * (len - 1);
        ll g = __gcd(qry[i].zi, qry[i].mu);
        qry[i].zi /= g;
        qry[i].mu /= g;
    }
}
int Solve() {
    int block = sqrt(n);
    rep(i, 1, n+1) {
        scanf("%d", c+i);
        pos[i] = (i - 1) / block + 1;
    }
    rep(i, 0, q) {
        scanf("%d%d", &qry[i].l, &qry[i].r);
        qry[i].id = i;
    }
    sort(qry, qry + q, [&](Node a, Node b){ return pos[a.l] != pos[b.l] ? a.l < b.l : a.r < b.r; });
    mo();
    sort(qry, qry + q, [&](Node a, Node b){ return a.id < b.id; });
    rep(i, 0, q) printf("%lld/%lld\n", qry[i].zi, qry[i].mu);
    return 0;
}

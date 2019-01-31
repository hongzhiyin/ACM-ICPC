// 莫队  O(n^(3/2))

ll tmp;
void add(int p) { tmp.. } // 计算将位置 p 纳入区间带来的影响
void sub(int p) { tmp.. } // 计算将位置 p 移出区间带来的影响
void mo() {
    int l = 1, r = 0;
    rep(i, 0, q) {
        while (r < qry[i].r) add(++r);
        while (r > qry[i].r) sub(r--);
        while (l < qry[i].l) sub(l++);
        while (l > qry[i].l) add(--l);
        qry[i].ans = tmp;
    }
}
int Solve() {
    int block = sqrt(n);    // 1. 设置块大小
    rep(i, 0, q) {          // 2. 设置询问区间、序号、块号
        scanf("%d%d", &qry[i].l, &qry[i].r);
        qry[i].id = i;
        qry[i].pos = (qry[i].l - 1) / block + 1;
    }
    sort(qry, qry + q, [&](Node a, Node b){ return a.pos != b.pos ? a.l < b.l : a.r < b.r; }); // 3. 按块号排序
    mo();   // 4. 莫队算法
    sort(qry, qry + q, [&](Node a, Node b){ return a.id < b.id; }); // 5. 按序号排序
    rep(i, 0, q) printf("%lld\n", qry[i].ans); // 6. 输出答案
}

// 带修改莫队  O(n^(5/3))

bool cmp(Node a, Node b) {
    return pos[a.l] != pos[b.l] ? pos[a.l] < pos[b.l] :
           pos[a.r] != pos[b.r] ? pos[a.r] < pos[b.r] : a.pre < b.pre;
}
int tmp, l, r, cur;
void add(int p) { tmp.. }
void sub(int p) { tmp.. }
void upd(int cur) {
    if (chg[cur].pos >= l && chg[cur].pos <= r) { tmp.. }
    swap(chg[cur].val, c[ chg[cur].pos ]);
}
void mo() {
    rep(i, 1, qno+1) {
        while (r < qry[i].r) add(++r);
        while (r > qry[i].r) sub(r--);
        while (l < qry[i].l) sub(l++);
        while (l > qry[i].l) add(--l);
        while (cur < qry[i].pre) upd(++cur);
        while (cur > qry[i].pre) upd(cur--);
        qry[i].ans = tmp;
    }
}
int Solve() {
    qno = cno = 0;
    tmp = 0; l = 1; r = 0; cur = 0;

    int block = pow(n, 2.0 / 3);    // 注意分块大小
    rep(i, 1, n+1) {
        pos[i] = (i - 1) / block + 1;
        ...
    }
    while (q--) {
        char op[5]; scanf("%s", op);
        if (op[0] == 'Q') {     // 读询问
            ++qno;
            scanf("%d%d", &qry[qno].l, &qry[qno].r);
            qry[qno].pre = cno; // 最近一次修改
            qry[qno].id = qno;
        } else {                // 读修改
            ++cno;
            scanf("%d%d", &chg[cno].pos, &chg[cno].val);
        }
    }
    sort(qry + 1, qry + qno + 1, cmp);
    mo();
    sort(qry + 1, qry + qno + 1, [&](Node a, Node b){ return a.id < b.id; });
    rep(i, 1, qno+1) printf("%lld\n", qry[i].ans);
    return 0;
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
        while (r < qry[i].r) add(++r);
        while (r > qry[i].r) sub(r--);
        while (l < qry[i].l) sub(l++);
        while (l > qry[i].l) add(--l);
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

----------------------------------------------------------------------------------------------------

// luogu P1903
// 题意：询问 [l, r] 的颜色种数，修改 pos 位置的颜色
// 题解：带修改莫队
int tmp, l, r, cur;
void add(int p) {
    cnt[c[p]]++;
    if (cnt[c[p]] == 1) tmp++;
}
void sub(int p) {
    cnt[c[p]]--;
    if (cnt[c[p]] == 0) tmp--;
}
void upd(int cur) {
    if (chg[cur].pos >= l && chg[cur].pos <= r) {
        if (--cnt[ c[ chg[cur].pos ] ] == 0) tmp--;
        if (++cnt[ chg[cur].val ] == 1) tmp++;
    }
    swap(chg[cur].val, c[ chg[cur].pos ]);
}
void mo() {
    rep(i, 1, qno+1) {
        while (r < qry[i].r) add(++r);
        while (r > qry[i].r) sub(r--);
        while (l < qry[i].l) sub(l++);
        while (l > qry[i].l) add(--l);
        while (cur < qry[i].pre) upd(++cur);
        while (cur > qry[i].pre) upd(cur--);
        qry[i].ans = tmp;
    }
}
int Solve() {
    qno = cno = 0;
    tmp = 0; l = 1; r = 0; cur = 0;
    memset(cnt, 0, sizeof(cnt));

    int block = pow(n, 2.0 / 3);    // 注意分块大小
    rep(i, 1, n+1) {
        pos[i] = (i - 1) / block + 1;
        scanf("%d", c+i);
    }
    while (q--) {
        char op[5];
        scanf("%s", op);
        if (op[0] == 'Q') {
            ++qno;
            scanf("%d%d", &qry[qno].l, &qry[qno].r);
            qry[qno].pre = cno;
            qry[qno].id = qno;
        } else {
            ++cno;
            scanf("%d%d", &chg[cno].pos, &chg[cno].val);
        }
    }
    sort(qry + 1, qry + qno + 1, cmp);
    mo();
    sort(qry + 1, qry + qno + 1, [&](Node a, Node b){ return a.id < b.id; });
    rep(i, 1, qno+1) printf("%d\n", qry[i].ans);
    return 0;
}

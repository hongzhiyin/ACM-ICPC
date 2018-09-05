================================================== Problem Set ==================================================

// cf 1028C
// 题意：给 n 个矩形，保证至少有一个点被 n-1 个矩形覆盖，找出任意一个这样的点
// 题解：枚举每一个矩形，假设这个矩形不属于那 n-1 个矩形，求剩下的矩形的最大左下角和最小右上角，如果可以构成矩形，则找到该点
inline pii min(pii a, pii b) { return mp(min(a.fi, b.fi), min(a.se, b.se)); }
inline pii max(pii a, pii b) { return mp(max(a.fi, b.fi), max(a.se, b.se)); }
int Solve() {
    rep(i, 1, n+1) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        a[i] = mp(mp(x1, y1), mp(x2, y2));
    }
    pl[0] = pl[n+1] = sl[0] = sl[n+1] = mp(-INF, -INF);
    pr[0] = pr[n+1] = sr[0] = sr[n+1] = mp(INF, INF);
    rep(i, 1, n+1) {  // 前 i 个矩形
        pl[i] = max(pl[i-1], a[i].fi);
        pr[i] = min(pr[i-1], a[i].se);
    }
    per(i, 1, n+1) {  // 后 i 个矩形
        sl[i] = max(sl[i+1], a[i].fi);
        sr[i] = min(sr[i+1], a[i].se);
    }
    rep(i, 1, n+1) {  // 枚举矩形
        pii l = max(pl[i-1], sl[i+1]);
        pii r = min(pr[i-1], sr[i+1]);
        if (l.fi <= r.fi && l.se <= r.se)
            return !printf("%d %d\n", l.fi, l.se);
    }
}

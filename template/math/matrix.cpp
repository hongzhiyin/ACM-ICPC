struct Mat {
	vector<vi> a;
	Mat() {}
	Mat(int n, int m) { a.resize(n, vi(m)); }
	Mat operator *(const Mat &b) const {
		int n = sz(a), m = sz(b.a[0]), nm = sz(b.a); Mat r(n, m);
		rep(i, 0, n) rep(j, 0, m) rep(k, 0, nm)
			r.a[i][j] = add(r.a[i][j], mul(a[i][k], b.a[k][j]));
		return r;
	}
	Mat operator ^(ll b) {
		int n = sz(a); Mat r(n, n), t = *this;
		rep(i, 0, sz(r.a)) r.a[i][i] = 1;
		for (; b; b >>= 1) {
			if (b & 1) r = r * t;
			t = t * t;
		}
		return r;
	}
	void out() {
		rep(j, 0, sz(a)) {
		    vi r = a[j];
		    rep(i, 0, sz(r))
                printf("%d%c", r[i], " \n"[i == sz(r) - 1]);
        }
	}
};

/*
矩阵快速幂求斐波那契数列第 n 项
┌       ┐     ┌      ┐(n-1)  ┌      ┐
│  F[n] │     │ 1  1 │       │ F[1] │
│       │  =  │      │   ×   │      │
│ F[n-1]│     │ 1  0 │       │ F[0] │
└       ┘     └      ┘       └      ┘
斐波那契数列前 n 项和
Sn = F[n+2] - F[2]
*/

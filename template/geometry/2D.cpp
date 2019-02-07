typedef ll T;
const db eps = 1e-7, pi = acosl(-1.);
int sgn(T x) { return (x > eps) - (x < -eps); }
struct P {
    T x, y; P () {} P (T x, T y) : x(x), y(y) {}
    P operator + (P b) { return P(x + b.x, y + b.y); }  // 向量加
    P operator - (P b) { return P(x - b.x, y - b.y); }  // 向量减
    T operator * (P b) { return x * b.x + y * b.y; }    // 向量点积
    T operator / (P b) { return x * b.y - y * b.x; }    // 向量叉积
    P operator * (T k) { return P(x * k, y * k); }      // 向量数乘
    P operator / (T k) { return P(x / k, y / k); }      // 向量数除
};
T cross(P o, P a, P b) { return (a - o) / (b - o); }
int Scross(P o, P a, P b) { return sgn(cross(o, a, b)); }

bool SxS(P a, P b, P c, P d) {  // seg x seg
    return
    max(a.x, b.x) >= min(c.x, d.x) && max(c.x, d.x) >= min(a.x, b.x) &&
    max(a.y, b.y) >= min(c.y, d.y) && max(c.y, d.y) >= min(a.y, b.y) &&
    Scross(a, b, c) * Scross(a, b, d) <= eps &&
    Scross(c, d, a) * Scross(c, d, b) <= eps;
}
P SxSP(P a, P b, P c, P d) {    // after SxS
	T s1 = cross(a, b, c), s2 = cross(a, b, d);
	P tmp;
	tmp.x = (c.x * s2 - d.x * s1) / (s2 - s1);
	tmp.y = (c.y * s2 - d.y * s1) / (s2 - s1);
	return tmp;
}

struct C {
    P o; db r; C () {} C (P o, db r) : o(o), r(r) {}
};

C getC(P a,P b,P c){  // 三点确定一个圆 （ 三角形外接圆 ）
    db a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1 * a1 + b1 * b1) / 2;
    db a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2 * a2 + b2 * b2) / 2;
    db d = a1 * b2 - a2 * b1;
    P o = P(a.x + (c1 * b2 - c2 * b1) / d, a.y + (a1 * c2 - a2 * c1) / d);
    return C(o, a.dis(o));
}

typedef ll T;
const db eps = 1e-7, pi = acosl(-1.);
int sgn(T x) { return (x > eps) - (x < -eps); }
struct P {
    T x, y; P () {} P (T x, T y) : x(x), y(y) {}
    P operator - (P b) { return P(x - b.x, y - b.y); }
    P operator + (P b) { return P(x + b.x, y + b.y); }
    T operator * (P b) { return x * b.x + y * b.y; }
    T operator / (P b) { return x * b.y - y * b.x; }
    P operator * (T k) { return P(x * k, y * k); }
    P operator / (T k) { return P(x / k, y / k); }
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

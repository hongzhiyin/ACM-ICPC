/* 注意
  1. 点、向量
    1. 如果角度出现 -pi ，可以加上 2pi 修正为 pi
    2. atan2(y, x) 的参数是浮点数时，可能出现 -pi ，如 atan2(-0.0, -1.0)
  2. 线段、直线
    1. 线段严格相交定义为：每条线段的两个端点落在另一条线段两边，形象来说，就是可以在图形里看到四个端点和一个交点
*/

typedef db T;
const db eps = 1e-7, pi = acosl(-1.);
int sgn(T x) { return (x > eps) - (x < -eps); }
bool inMid(T l, T x, T r) { return sgn(l - x) * sgn(r - x) <= 0; }  // 数 x 在区间 [l, r] 内（包括边界）

// 点、向量
struct P {
    T x, y; P () {} P(T x, T y) : x(x), y(y) {}
    P operator + (const P &b) const { return P(x + b.x, y + b.y); }  // 向量加
    P operator - (const P &b) const { return P(x - b.x, y - b.y); }  // 向量减
    T operator * (const P &b) const { return x * b.x + y * b.y; }    // 向量点积
    T operator / (const P &b) const { return x * b.y - y * b.x; }    // 向量叉积
    P operator * (const T &k) const { return P(x * k, y * k); }      // 向量数乘
    P operator / (const T &k) const { return P(x / k, y / k); }      // 向量数除
    bool operator < (const P &b) const { return sgn(x - b.x) ? x < b.x : y < b.y; }  // 左小右大，下小上大
    bool operator == (const P &b) const { return !sgn(x - b.x) && !sgn(y - b.y); }   // 向量相等
    P rot(T t) { return P(x * cos(t) - y * sin(t), x * sin(t) + y * cos(t)); }  // 向量逆时针旋转 t 弧度
    P rot90() { return P(-y, x); }           // 向量逆时针旋转 90 度
    db arg() const { return atan2(y, x); }   // 方位角 (-pi, pi]
    T abs() { return sqrt(x * x + y * y); }  // 向量模长
    T abs2() { return x * x + y * y; }       // 向量模长的平方
    P unit() { return (*this) / abs(); }     // 单位向量
    void scan() { db tx, ty; scanf("%lf%lf", &tx, &ty); x = tx; y = ty; }  // 输入
    void print() { printf("%.11lf %.11lf\n", x, y); }                      // 输出
    P toR() { return (sgn(x) == -1 || !sgn(x) && sgn(y) == -1) ? (*this)*(-1) : (*this); }  // 若向量在 2 3 象限，则取相反向量
    bool isUp() const { return sgn(y) == 1 || !sgn(y) && sgn(x) == -1; }                    // 向量是否在 1 2 象限
};
T dis(P a, P b) { return (b - a).abs(); }   // 点 a 到点 b 的距离
P symmetry(P p, P a) { return a + a - p; }  // 点 p 关于点 a 的中心对称点
T cross(P o, P a, P b) { return (a - o) / (b - o); }         // 向量 oa 与 ob 的叉积
int crossSgn(P o, P a, P b) { return sgn(cross(o, a, b)); }  // 向量 oa 与 ob 的叉积符号
db rad(P a, P b) { return atan2(a / b, a * b); }             // 向量 a 与 b 的夹角（弧度制）
bool order(const P &a, const P &b) { return a.isUp() < b.isUp() || a.isUp() == b.isUp() && sgn(a/b) > 0; }  // 极角排序

// 线段、直线
struct L { P s, t; L () {} L(P s, P t) : s(s), t(t) {} };
bool onPS(P p, L a) { return sgn((a.t-a.s)/(p-a.s))==0 && sgn((p-a.s)*(p-a.t))<=0; }   // 点 p 是否在线段 a 上
bool inRec(P p, L a) { return inMid(a.s.x, p.x, a.t.x) && inMid(a.s.y, p.y, a.t.y); }  // 点 p 在以直线 a 为对角线的矩形内
P proj(P p, L a) { return (a.t-a.s) * ( (p-a.s) * (a.t-a.s) / (a.t-a.s).abs2() ) + a.s; }  // 点 p 关于直线 a 的投影点
P reflect(P p, L a) { return proj(p, a) * 2 - p; }                                         // 点 p 关于直线 a 的对称点
bool xSSr(const L &a, const L &b) {  // 线段 a 和线段 b 严格相交
    T c1 = (a.t-a.s) / (b.s-a.s), c2 = (a.t-a.s) / (b.t-a.s);
    T c3 = (b.t-b.s) / (a.s-b.s), c4 = (b.t-b.s) / (a.t-b.s);
    return sgn(c1) * sgn(c2) < 0 && sgn(c3) * sgn(c4) < 0;
}
bool xSS(L a, L b) {                 // 线段 a 和线段 b 不严格相交
    T c1 = (a.t-a.s) / (b.s-a.s), c2 = (a.t-a.s) / (b.t-a.s);
    T c3 = (b.t-b.s) / (a.s-b.s), c4 = (b.t-b.s) / (a.t-b.s);
    return sgn(c1) * sgn(c2) <= 0 && sgn(c3) * sgn(c4) <= 0 &&
           sgn(max(a.s.x,a.t.x) - min(b.s.x,b.t.x)) >= 0 &&
           sgn(max(b.s.x,b.t.x) - min(a.s.x,a.t.x)) >= 0 &&
           sgn(max(a.s.y,a.t.y) - min(b.s.y,b.t.y)) >= 0 &&
           sgn(max(b.s.y,b.t.y) - min(a.s.y,a.t.y)) >= 0;
}
bool xSL(L a, L b) {  // 线段 a 与直线 b 相交 ( 不严格 : <= ; 严格 : < )
    return sgn( (b.t - b.s) / (a.s - b.s) ) * sgn( (b.t - b.s) / (a.t - b.s) ) <= 0;
}
P xLL(L a, L b) {  // 直线 a 和直线 b 的交点
    T s1 = (b.t - b.s) / (a.s - b.s), s2 = -( (b.t - b.s) / (a.t - b.s) );
    return (a.s * s2 + a.t * s1) / (s1 + s2);
}
db disPL(P p, L a) { return fabs( (a.t-a.s) / (p-a.s) ) / (a.t-a.s).abs(); }  // 点 p 到直线 a 的距离
db disPS(P p, L a) {                                                          // 点 p 到线段 a 的距离
    return sgn( (a.t-a.s) * (p-a.s) ) * sgn( (a.s-a.t) * (p-a.t) ) == 1
           ? disPL(p, a) : min( (p-a.s).abs(), (p-a.t).abs() );
}
db disSS(L a, L b){                                                           // 线段 a 到线段 b 的距离
    if (xSS(a,b)) return 0;
    return min( min( disPS(a.s,b), disPS(a.t,b) ), min( disPS(b.s,a), disPS(b.t,a) ) );
}
db disLL(L a, L b) { return (a.t-a.s) / (b.t-b.s) ? 0 : disPL(a.s, b); }      // 直线 a 到直线 b 的距离

// 多边形、凸包
typedef vector<P> polygon;
polygon Convex(polygon A) {  // 求凸包，逆时针排序（ 内角 <180 : (<=) ; 内角 <=180 : (<) ）
    int n = sz(A); if (n <= 1) return A;
    sort(all(A));
    polygon B;
    for (int i = 0; i < n; B.pb(A[i++]))
        while (sz(B) > 1 && crossSgn(B[sz(B)-2], B.back(), A[i]) < 0) B.pop_back();  // 更改这里的 <
    for (int i = n - 2, t = sz(B); i >= 0; B.pb(A[i--]))
        while (sz(B) > t && crossSgn(B[sz(B)-2], B.back(), A[i]) < 0) B.pop_back();  // 同上
    B.pop_back(); return B;
}
T area(polygon A) {  // 多边形 A 的面积，整型可以返回面积的两倍，保持精度
    T res = 0;
    rep(i, 0, sz(A)) res += A[i] / A[ (i+1) % sz(A) ];
    return fabs(res) / 2;
}
bool isConvex(polygon A) {  // 多边形 A 是否是凸包，要求 A 的点集按逆时针排序
    rep(i, 0, 2) A.pb(A[i]);
    rep(i, 0, sz(A)-2) if ( sgn( (A[i+1]-A[i]) / (A[i+2]-A[i]) ) < 0 ) return 0;
    return 1;
}
int inPpo(P p, polygon A) {  // 点和多边形关系 ( 2 : in , 1 : on , 0 : out )
    int res = 0; A.pb(A[0]);
    rep(i, 1, sz(A)) {
        P u = A[i-1], v = A[i];
        if (onPS(p, L(u, v))) return 1;
        if (sgn(u.y - v.y) > 0) swap(u, v);
        if (sgn(u.y - p.y) >= 0 || sgn(v.y - p.y) < 0) continue;
        if (crossSgn(v, u, p) < 0) res ^= 1;
    }
    return res << 1;
}
T ConvexDiameter(polygon A) {  // 凸包 A 的直径，即凸包 A 上的最远点对
    int now = 0, n = sz(A); T res = 0;
    if (n <= 1) return 0;
    rep(i, 0, sz(A)) {
        now = max(now, i);
        while (1) {
            T t1 = dis(A[i], A[now%n]), t2 = dis(A[i], A[(now+1)%n]);
            res = max(res, max(t1, t2));
            if (t2 > t1) now++; else break;
        }
    }
    return res;
}
polygon ConvexCut(polygon A, L a) {  // 半平面 a 切割凸包 A 形成的凸包（直线 a 逆时针方向）
    int n = sz(A); A.pb(A[0]); polygon res;
    rep(i, 0, n) {
        int w1 = crossSgn(a.s, a.t, A[i]), w2 = crossSgn(a.s, a.t, A[i+1]);
        if (w1 >= 0) res.pb(A[i]);
        if (w1 * w2 < 0) res.pb(xLL(a, L(A[i], A[i+1])));
    }
    return res;
}

struct C {
    P o; db r; C () {} C (P o, db r) : o(o), r(r) {}
};

C getC(P a,P b,P c){  // 三点确定一个圆 （ 三角形外接圆 ）
    db a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1 * a1 + b1 * b1) / 2;
    db a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2 * a2 + b2 * b2) / 2;
    db d = a1 * b2 - a2 * b1;
    P o = P(a.x + (c1 * b2 - c2 * b1) / d, a.y + (a1 * c2 - a2 * c1) / d);
    return C(o, dis(a, o));
}

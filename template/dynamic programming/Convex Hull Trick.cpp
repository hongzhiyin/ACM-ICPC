struct P {
    ll x, y;
    P () {} P (ll x, ll y) : x(x), y(y) {}
    P operator - (const P &rhs) const { return P(x - rhs.x, y - rhs.y); }
    
    // 叉积可能爆 long long ，返回叉积是否大于 0
    bool operator ^ (const P &rhs) const { return (db)x * rhs.y > (db)y * rhs.x; }
};
#define X(j) (...)   // 点的横坐标
#define Y(j) (...)   // 点的纵坐标
#define K(i) (...)   // 直线斜率

int Solve() {
    deque <P> Q; Q.pb(P(X(0), Y(0)));    // 设置初值
    rep(i, 1, n+1) {
        // 队首斜率 小于 直线斜率
        while (sz(Q) > 1 && (Q[1].y - Q[0].y) < (Q[1].x - Q[0].x) * K(i)) Q.pop_front();
        
        // dp 转移式
        dp[i] = Q[0].y - K(i) * Q[0].x - B(i)
        
        // 第 i 个结点待入队
        P a(X(i), Y(i));
        
        // 队尾元素是否下凸
        while (sz(Q) > 1 && !((Q[sz(Q)-2] - a) ^ (Q.back() - a))) Q.pop_back();
        
        // 第 i 个结点入队
        Q.pb(a);
    }
    return printf("%lld\n", dp[n]);
}

// 直线斜率不单调，二分查找答案
int Solve() {
    deque <P> Q; Q.pb(P(X(0), Y(0)));    // 设置初值
    rep(i, 1, n+1) {
        // 二分查找最优决策，左侧线段斜率比直线斜率小，右侧线段斜率比直线斜率大
        int L = 0, R = sz(Q) - 1;
        while (L < R) {
            int M = (L + R) >> 1;
            if (Q[M+1].y - Q[M].y <= K(i) * (Q[M+1].x - Q[M].x)) L = M + 1;
            else R = M;
        }
        
        // 点 Q[L] 为最优决策点，转移获得 dp[i]
        dp[i] = Q[L].y - K(i) * Q[L].x + B(i)
        
        // 第 i 个结点待入队
        P a(X(i), Y(i));
        
        // 队尾元素是否下凸
        while (sz(Q) > 1 && !((Q[sz(Q)-2] - a) ^ (Q.back() - a))) Q.pop_back();
        
        // 第 i 个结点入队
        Q.pb(a);
    }
    return printf("%lld\n", dp[n]);
}

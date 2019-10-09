// 线性筛素数
// 利用了每个合数必有一个最小素因子。每个合数仅被它的最小素因子筛去正好一次。所以为线性时间
// 代码中体现在 : if (i % prim[j] == 0) break;
// prim 数组中的素数是递增的，当 i 能整除 prim[j]，那么 i*prim[j+1] 这个合数肯定被 prim[j] 乘以某个数筛掉
// 因为 i 中含有 prime[j], prime[j] 比 prime[j+1] 小。接下去的素数同理，所以不用筛下去了
// 在满足 i % prim[j] == 0 这个条件之前以及第一次满足该条件时， prim[j] 必定是 prim[j]*i 的最小因子

/*
时间复杂度 : O(n)
输入 :
    n : 筛出 [2, n) 内的质数
输出 :
    prim : 质数集合 ; notPrim[i] : i 是否为质数
*/

vi prim;
bool notPrim[N];
void GetPrime(int n) {   // 预处理 [2, n) 的质数
    memset(notPrim, 0, sizeof(notPrim)); prim.clear();
    notPrim[0] = notPrim[1] = 1;
    rep(i, 2, n) {
        if (!notPrim[i]) prim.pb(i);
        for (int j = 0; j < sz(prim) && (ll)i * prim[j] < n; ++j) {
            notPrim[i*prim[j]] = 1;
            if (i % prim[j] == 0) break;
        }
    }
}

// x <= 1e18
// a ^ (x-1) = 1 (mod x)
bool check(ll x) {      // 判断 x 是否是质数
    if (x == 2) return 1;
    if (x < 2 || !(x & 1)) return 0;
    rep(t, 0, 10) {
        ll a = rand() % (x-1) + 1;
        if (powmod(a, x-1) != 1) return 0;
    }
    return 1;
}

// Decompose Prime Factor 分解质因数
vi pf;
void DPF(int x) {
    pf.clear();
    for (int i = 2; i * i <= x; ++i) if (x % i == 0) {
        pf.pb(i);
        while (x % i == 0) x /= i;
    }
    if (x > 1) pf.pb(x);
}

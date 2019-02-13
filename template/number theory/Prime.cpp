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
// 预处理 [2, sqrt(x)] 的质数
vi pf;
void DPF(int x) {
    pf.clear();
    for(auto p : prim) {
        if (p > x) break;
        if (x % p == 0) {
            pf.pb(p);
            while (x % p == 0) x /= p;
        }
    }
    if (x != 1) pf.pb(x);
}

================================================== Problem Set ==================================================

// cf 822D
// 题意：
// 有 n 个人参加比赛，每一轮将他们分成任意组（必须保证每组人数相同），然后每组的所有人两两之间都必须进行一次比较，胜者进行下一轮
// f(n) 表示确定第一名所需的最少比较次数
// 求 f(1) ~ f(n)
// 结论：
// 当 x 为质数时， f(x) = x * (x-1) / 2; 当 x 为合数时， f(x) = (x/p) * f(p) + f(x/p) ( p 为 x 的最小质因子 )
// 即将 n 个人分为尽可能多的组，每组人数尽可能少，则总比较次数最少。
// 证明： https://blog.csdn.net/qq_36306833/article/details/77947537 （证明表述有误，但思路没错，通过假设值进行证明）
void Init() {
    memset(f, -1, sizeof(f));
    GetPrime(N);
    f[1] = 0;
    rep(i, 2, N) {      // 求 f(1) ~ f(n) 的过程类似线性筛素数
        if (!~f[i]) f[i] = ((ll)i * (i-1) / 2) % MOD;   // 如果 i 为素数，则直接赋值
        for (int j = 0; prim[j] <= i && (ll)i * prim[j] < N; ++j) {
            f[i*prim[j]] = add(mul(i, f[prim[j]]), f[i]);   // 更新合数
            if (i % prim[j] == 0) break;    // 保证 f[x] 是被其最小质因子更新
        }
    }
}

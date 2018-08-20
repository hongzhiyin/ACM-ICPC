// 扩展欧几里德
// 求 a 在模数 MOD 下的逆元
// 若 gcd(a, MOD) != 1 说明逆元不存在
ll inverse(ll a, ll MOD) {  
    ll g, x, y;  
    exgcd(a, MOD, g, x, y);  
    return (g == 1) ? (x + MOD) % MOD : -1;  
}

// 费马小定理
// a 是整数， MOD 是质数，且 a, MOD 互质
// 则 a 的 (MOD-1) 次方除以 MOD 的余数恒等于 1
// 即 a ^ (MOD-1) ≡ 1 (mod MOD)
// 可推出： a^k × a^(MOD-1-k) ≡ 1 (mod MOD)，则 a^k 的乘法逆元为 a^(p-1-k)
// 当 k = 1 时，a 的乘法逆元为 a^(MOD-2)

// 递推公式
// 模数 MOD 为奇质数
inv[1] = 1;
rep(i, 2, MOD)
    inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;

// 另，有结论：1 到 p-1 模 p 的所有逆元值对应 1 到 p 中所有的数。
// 例如， p = 7 ，那么 1 到 6 对应的逆元是 1 4 5 2 3 6 。

// 特殊情况
// 当 N 是质数，a 是 (N + 1) 的约数时 
// inv[a] = (N+1)/a

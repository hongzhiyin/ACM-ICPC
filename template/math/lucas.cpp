// description : cal C(a, b) % MOD
// cal-time : O( log_{mod}^{n} )
// pre-time : O( MOD )
// inv[i] : inv(i)
// ijc[i] : inv(jc[i])
// !!!! : MOD should be a prime
int jc[MOD], ijc[MOD], inv[MOD];
int C(int a, int b) { return a < b ? 0 : mul(jc[a], mul(ijc[b], ijc[a - b])); }
int lucas(ll a, ll b) { return ! b ? 1 : mul(C(a % MOD, b % MOD), lucas(a / MOD, b / MOD)); }
int lucas_ini() {
	jc[0] = 1; rep(i, 1, MOD) jc[i] = mul(jc[i - 1], i);    //阶乘
	inv[1] = 1; rep(i, 2, MOD) inv[i] = mul(inv[MOD % i], MOD - MOD / i);
	ijc[0] = 1; rep(i, 1, MOD) ijc[i] = mul(ijc[i - 1], inv[i]);
}

ll phi(ll n)
{
    ll ret = n;
    for (ll i = 2; i*i <= n; ++i)
        if (n % i == 0) {
            ret = ret - ret / i;
            while (n % i == 0) n /= i;
         }
    if (n > 1) ret = ret - ret / n;
    return ret;
}

//欧拉定理
//A ^ phi(C) ≡ 1 (mod C)

//欧拉降幂公式 ( B > phi(C) )
//A ^ B % C = A ^ (B % phi(C) + phi(C)) % C

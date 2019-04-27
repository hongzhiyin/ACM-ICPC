## Combinatorics

### 排列组合

- 计算 $C(n, m)$
  ```c++
  ll C(int n, int m) {
  	ll res = 1;
  	rep(i, 0, m) res = res * (n-i) / (i+1);  // 保证可整除
  	return res;
  }
  ```

- $k$ 种颜色、每种颜色 $cnt[i]$ 个数的球，排列方案数（某个位置上的球颜色不一样算不同方案）
  $$
  \frac{(\sum_i cnt[i])!}{\prod_i cnt[i]!}
  $$
  
- $n$ 个球放到 $m$ 个盒子里的方案数（某个盒子里球的个数不同算不同方案）
  $$
  ans = C_{n+m-1}^{\ m-1} = C_{n+m-1}^{\ n}
  $$
  

## Number Theory

### gcd

- gcd(a, b) == gcd(a, b-a)

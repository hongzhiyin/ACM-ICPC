# Conclusion / 结论、定理、经验

[TOC]

<div STYLE="page-break-after: always;"></div>
## Combinatorics / 组合数学

### 杨辉三角

- 求第 $1$ 行第 $m$ 列到第 $n$ 行第 $m$ 列的和

$$
\large \sum_{i=0}^{n}C_{i}^{m} = \sum_{i=m}^nC_i^m = C_{n+1}^{m+1}
$$



---



### 排列方案

- $k$ 种颜色、每种颜色 $cnt[i]$ 个数的球，排列方案数（某个位置上的球颜色不一样算不同方案）

$$
\large \frac{(\sum_i cnt[i])!}{\prod_i cnt[i]!}
$$



### n 个球放入 m 个盒子问题

https://blog.csdn.net/sunandstarws/article/details/77440171

https://blog.csdn.net/qq_33951440/article/details/78341805





---

<div STYLE="page-break-after: always;"></div>
## Dynamic programming / 动态规划

### 背包DP

#### 01 背包

- **dp 转移优化** 

设 $V = 前\  i\  个物品的体积和$ ， $M = 背包容量$ ，$mx = 最大物品的体积$ ， $cur = 当前物品的体积$ 则：

先将物品按单位价值从大到小排序，然后更新答案 $dp[i]$ 的区间就只需要在

上界 $min(V, M)$  到下界 $max( cur, min(V, M) - (mx-1)^2 )$ 的范围内。



---

<div STYLE="page-break-after: always;"></div>
## Geometry / 计算几何

### 坐标变换

**平移矩阵** 
$$
\left[
\begin{matrix}
   x' \\
   y' \\
   1 
\end{matrix}
\right]
=
\left[
\begin{matrix}
   1 & 0 & dx \\
   0 & 1 & dy \\
   0 & 0 & 1
\end{matrix}
\right]
\left[
\begin{matrix}
   x \\
   y \\
   1 
\end{matrix}
\right]
$$
**旋转矩阵** （向量 $[x, y]$ 绕原点旋转 $\theta$ 度，逆时针为正，顺时针为负）
$$
\left[
\begin{matrix}
   x' \\
   y' \\
   1 
\end{matrix}
\right]
=
\left[
\begin{matrix}
   cos\theta & -sin\theta & 0 \\
   sin\theta & cos\theta & 0 \\
   0 & 0 & 1
\end{matrix}
\right]
\left[
\begin{matrix}
   x \\
   y \\
   1 
\end{matrix}
\right]
$$
**缩放矩阵** 
$$
\left[
\begin{matrix}
   x' \\
   y' \\
   1 
\end{matrix}
\right]
=
\left[
\begin{matrix}
   Sx & 0 & 0 \\
   0 & Sy & 0 \\
   0 & 0 & 1
\end{matrix}
\right]
\left[
\begin{matrix}
   x \\
   y \\
   1 
\end{matrix}
\right]
$$

```c++
void move(pii &p, int dx, int dy) { p.fi += dx; p.se += dy; }
void rotate(pii &p, int theta) {
    pii tmp(
        cos(theta) * p.fi - sin(theta) * p.se,
        sin(theta) * p.fi + cos(theta) * p.se);
    p = tmp;
}
void scale(pii &p, int Sx, int Sy) { p.fi *= Sx; p.se *= Sy; }
```



**应用**

1. 点 $(x, y)$ 绕点 $(x_0, y_0)$ 旋转 $\theta$ 度，可先将点 $(x_0, y_0)$ 平移到原点，然后绕原点旋转，再平移回来。
2. 当旋转中心点非整数坐标时，可缩放图形（如放大 2 倍），再进行变换。



---


<div STYLE="page-break-after: always;"></div>
## Number theory / 数论

### 质数

- 唯一分解定理

$$
x = p_1^{q_1} p_2^{q_2} ... p_k^{q_k}
$$



- 因子种类数

$$
cnt = (q_1 + 1) (q_2 + 1) ... (q_k + 1)
$$



---



### gcd

- 公式

$$
gcd(a, b) = gcd(a, a-b) = gcd(b, a-b)
$$



- 

$$
\{\ gcd(x,y)\ |\ x\ 是某个正整数， y\in[1,x]\ \} = \{\ x\ 的所有因子\ \}
$$


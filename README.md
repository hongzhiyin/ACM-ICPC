# Summary

![Progress](http://progressed.io/bar/24?title=Difficulty:2300~2400|tag:dp)

|　　一　　|　　二　　|　　三　　|　　四　　|　　五　　|　　六　　|　　日　　|
| :--: | :--: | :--: | :--: | :--: | :--: | :--: |
|      |      |     |  |     |  1   |  2   |
|      |      |      |    | ✔14 | ✔3 |  |
|  3   |  4   |  5   |  6   |  7  |  8  |  9  |
| ✔2 | ✔5 |      |      |      |  |      |
|  10  |  11  |  12  |  13  |  14  |  15  |  16  |
|      |      |      |      |      |      |      |
|  17  |  18  |  19  |  20  |  21  |  22  |  23  |
|      |  |  |      |      |  |      |
|  24  |  25  |  26  |  27  |  28  | 29 | 30 |
|      |      |  |  |  |      |      |

---

# Dairy

## 2019.06.04

### Codeforces 552E (递归下降语法分析)

### Codeforces 1142B (倍增)

### Codeforces 543D (树形dp + 前后缀)

### Codeforces 372C (dp + 单调队列)

### Codeforces 1156D (树形dp)

## 2019.06.03

### Codeforces 623B (dp)

### Codeforces 1154F (dp)

## 2019.06.01

### Codeforces 158E (dp)

### Codeforces 314C (dp + 计数 + 树状数组)

### Codeforces 449D (位运算 + 容斥原理)

- x 的贡献要传递给 x ^ (1 << j) ，首先，第一层循环要按位循环，第二层要按数值从大到小，防止重复计算贡献

## 2019.05.31

### Codeforces 650C (离散化 + 并查集)

## 2019.05.30

### Codeforces 55D (数位dp + lcm)

- a 是 b1 ~ bn 的倍数 等价于 a % lcm(b1, ... , bn) == 0
- b1 ~ bn 全集的 lcm 是 子集的 lcm 的倍数
- b1 ~ bn 所有子集能组成的 lcm 都是 全集lcm 的约数
- 数位 dp 里面 for 循环里，转移到下一层 dfs 的参数是涉及 i 的

### Codeforces 713C (dp + 排序)

- 把数列变成非严格递增
- dp[i]\[j] 表示前 i 个数，最后一个数等于 a[j] 的最小代价
- 变成严格递增，只需要对原序列操作： a[i] = a[i] - i

### Codeforces 360B (dp + 二分)

### Codeforces 466D (dp + 括号匹配)

- 可相交但不完全覆盖的若干线段可以看成括号匹配
- dp 第二维表示待匹配左括号

### Codeforces 1006F (meet in the middle)

- 起点和终点确定的曼哈顿路径数等于 C(n+m, n)

### Codeforces 383D (dp + 计数)

## 2019.05.29

### Codeforces 679B (dp + 递归)

### Codeforces 571B (dp + 贪心)

- dp 方程不一定要 i-1 转移到 i ，也可以用 dp[next] = min(dp[next], dp[cur]) ，用当前已知去更新之后的未知。

### Codeforces 494B (dp + string)

- 还是数学归纳法，假设 i-1 已经完成，那 dp[i] 就只有取第 i 位和不取第 i 位，那么不取就直接等于 dp[i-1] ，如果取，就想该怎么取。
- dp[i] = dp[j] + cost(i, j) ，这里 cost(i, j) 要整段考虑，不要再拆分了。

### Codeforces 487B (dp + multiset)

- 遇到涉及区间更新，区间查询最值的问题时，试试看能不能用 set 或 multiset 实现，比自己写数据结构简洁得多。
- 最小值 S.begin() ，最大值 S.rbegin()
- 类似用数学归纳法，假设已知 dp[i-1] 及其对应的 dp[j] 的信息，如何获取转移到 dp[i] 所需要的信息。

### Codeforces 319C (斜率优化)

### Essay

- 学习了斜率优化，整理了模板

---

## 2019.05.22

### Codeforces 486D (树形dp)

- 枚举结点作为根节点，即必须要取这个结点
- 那么这个结点的答案由与其相连的子节点的答案构成
- 如：方案数等于若干子节点方案数相乘
- 因为子节点可以不取，所以子节点方案数为必须(取自己的方案数) + 1
- 可用比较结点下标的方式防止重复计数

### Codeforces 519E (lca)

### Essay

制定了新的计划：
- 难度：2300 ~ 2400
- tag：dp
- 数量：一页（100题）


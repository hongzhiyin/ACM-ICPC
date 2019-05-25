# Why can't Accept

## Solution

- 程序中插入 assert(布尔表达式);  当表达式为假时，返回 Runtime Error 。

---

## base

### General

- 【1】【WA】 add() / mul() 操作时，传入的参数超过 int ，没有先取模而直接操作造成 long long 溢出。
- 【1】【WA】 没注意数据范围，int 溢出。
- 【1】【WA】 所询问区间的边界未初始化或赋值

---

### powmod

- 【1】【TLE】 快速幂指数为负数，造成死循环

---

<div STYLE="page-break-after: always;"></div>

## data structure

### disjoint set union

- 【1】【WA】 并查集的合并操作前，没有考虑是否属于同一个集合，造成重复计算属性值。

---

<div STYLE="page-break-after: always;"></div>

## string

### kmp

- 【1】【WA】 kmp 算法在失配跳转之后，保证失配位置之前的前缀是与自身后缀完全匹配的，没有考虑清楚题目是否要求完全匹配。

---

<div STYLE="page-break-after: always;"></div>

## tree

### General

- 【1】【RE】 树的总结点数超过 N

---

### lca

- 【1】【WA】 求 lca 的两点相同

---

<div STYLE="page-break-after: always;"></div>

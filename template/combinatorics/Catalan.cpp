Cat[n] = C(2 * n, n) / (n + 1);

1. n 个左括号和 n 个右括号组成的合法括号序列的方案数为 Cat[n]
2. 1 ~ n 按顺序入栈，形成的合法出栈序列的方案数为 Cat[n]
3. n 个节点构成的不同二叉树的方案数为 Cat[n]
4. 在平面直角坐标系，每一步只能向上或向右走，从 (0, 0) 走到 (n, n) 并且除两个端点外不接触直线 y = x 的路线方案数为 2 * Cat[n-1]

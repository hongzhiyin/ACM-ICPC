// 通项公式
Cat[n] = C(2 * n, n) / (n + 1);

// 递推公式
Cat[n] = Cat[n-1] * (4 * n - 2) / (n + 1);

// 质因数分解求 Cat[n]

Cat[n] = (n + 2) * (n + 3) * .. * (n + n) / ( 2 * 3 * .. * n )  // 特判 Cat[1] = 1

public static int n;
public static int fz[] = new int[N<<1];
public static int fm[] = new int[N<<1];
public static void Solve() {
    n = in.nextInt();
    for (int i = 2; i <= n; ++i) {
        int tmp = n + i;
        for (int j = 2; j * j <= tmp; ++j)
            while (tmp % j == 0) { fz[j]++; tmp /= j; }
        if (tmp > 1) fz[tmp]++;
        tmp = i;
        for (int j = 2; j * j <= tmp; ++j)
            while (tmp % j == 0) { fm[j]++; tmp /= j; }
        if (tmp > 1) fm[tmp]++;
    }
    BigInteger ans = BigInteger.ONE;
    for (int i = 2; i <= 2 * n; ++i) {
        if (fz[i] == 0 || fz[i] - fm[i] == 0) continue;
        ans = ans.multiply(qpow(BigInteger.valueOf(i), fz[i] - fm[i]));
    }
    out.println(ans);
}

// 应用
1. n 个左括号和 n 个右括号组成的合法括号序列的方案数为 Cat[n]
2. 1 ~ n 按顺序入栈，形成的合法出栈序列的方案数为 Cat[n]
3. n 个节点构成的不同二叉树的方案数为 Cat[n]
4. 在平面直角坐标系，每一步只能向上或向右走，从 (0, 0) 走到 (n, n) 并且除两个端点外不接触直线 y = x 的路线方案数为 2 * Cat[n-1]

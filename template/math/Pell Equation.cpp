// 一般形式： x^2 - d * y^2 = 1
// 其中， d > 1 且 d 不是完全平方数，当 d 为完全平方数时，只有 ( +/- 1, 0) 这一组特解
// 递推公式： x[n] = x[n-1] * x[1] + d * y[n-1] * y[1] , y[n] = x[n-1] * y[1] + y[n-1] * x[1]

================================================== Problem Set ==================================================

// hdu 6222
// 题意：给定一个整数 n ，找到一个整数 t 使得 t-1, t, t+1 组成三角形，且面积为整数
// 题解：海伦公式，佩尔方程，打表
public class Main {
    public static void Pre() {
        t[1] = BigInteger.valueOf(4);
        x[1] = BigInteger.valueOf(2);
        y[1] = BigInteger.valueOf(1);
        for (int i = 2; i < 60; ++i) {
            x[i] = x[i-1].multiply(x[1]).add(BigInteger.valueOf(3).multiply(y[i-1].multiply(y[1])));
            y[i] = x[i-1].multiply(y[1]).add(y[i-1].multiply(x[1]));
            t[i] = x[i].multiply(BigInteger.valueOf(2));
        }
    }
    public static void Solve() {
        n = in.nextBigInteger();
        for (int i = 1; i < 60; ++i) {
            if (t[i].compareTo(n) >= 0) {
                out.println(t[i]);
                break;
            }
        }
    }
    public static void main(String[] args) {
        Pre();
        int t; t = in.nextInt(); while (t-- >= 1) {
        //while (in.hasNext()) {
            Init();
            Solve();
        }
    }
}

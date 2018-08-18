import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
	public static Scanner in = new Scanner(System.in);
	public static PrintStream out = new PrintStream(System.out);

	public static void Pre() {}
	
	public static void Init() {}
	
	public static void Solve() {}
	
	public static void main(String[] args) {
		Pre();
		while (in.hasNext()) {
			Init();
			Solve();
		}
	}
}

// -------------------------------------------------- Extend -------------------------------------------------- //

/**
 * Functions of BigInteger
 * add、subtract、multiply、divide、mod、pow、modPow
 * BigInteger[] divideAndRemainder(BigInteger val)
 * BigInteger modPow(BigInteger exponent, BigInteger m)
 * modInverse(BigInteger mod) - 逆元，需互质
 */

/**
 * Functions of BigDecimal
 * BigDecimal divide(BigDecimal divisor, int scale, RoundingMode roundingMode)
 * RoundingMode: ROUND_HALF_[DOWN|UP|EVEN], ROUND_FLOOR, ROUND_CEILING
 * BigDecimal negate(): return value is (-this)
 * BigDecimal setScale(int newScale, [int roundingMode]): 保留小数位数
 */

// file input/output
Scanner in = new Scanner(new File("input.txt"));
PrintWriter out = new PrintWriter(new File("output.txt"));

// Note: must close file!
in.close();out.close();
		
// -------------------------------------------------- Example -------------------------------------------------- //

import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
	public static Scanner in = new Scanner(System.in);
	public static PrintStream out = new PrintStream(System.out);
	
	public static BigInteger jc[] = new BigInteger[1007];
	public static int n;
	
	public static void Pre() {
		jc[0] = BigInteger.valueOf(1);
		for (int i = 1; i < 1007; ++i)
			jc[i] = jc[i-1].multiply(BigInteger.valueOf(i));
	}
	
	public static void Init() {
		n = in.nextInt();
		out.println(n + "!");
	}
	
	public static void Solve() {
		out.println(jc[n]);
	}
	
	public static void main(String[] args) {
		Pre();
		while (in.hasNext()) {
			Init();
			Solve();
		}
	}
}

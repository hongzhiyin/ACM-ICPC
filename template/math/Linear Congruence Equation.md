#### 解线性同余方程
设方程 ： $ax \equiv b \pmod n$
因为 $ax - b$ 是 $n$ 的整数倍，设倍数为 $y$ ，则 $ax-b=ny$ ，移项得 $ax-ny=b$ 
设 $A = a$ ， $B=-n$ ，$C=b$ ，则为解不定方程 ： 
$$Ax + By = C$$ 
用扩展欧几里德算法求得方程
$$Ax+By=gcd(A,B)$$ 
的一组解 $(x_0,y_0)$ ，设 $g=gcd(A,B)$ ，则当 $C$ 是 $g$ 的倍数时（即 $C \mod g=0$），方程 
$$Ax + By = C$$
的一组解是 $\displaystyle(\frac{x_0C}{g},\frac{y_0C}{g})$ ，当 $C$ 不是 $g$ 的倍数时无整数解。
又，若方程 $Ax + By = C$ 的一组整数解为 $(x',y')$ ，则它的任意整数解都可以写成 
$$(x'-kb',y'+ka')$$ 
其中 $a'=A/g$ , $b'=B/g$ ， $k$ 取任意整数。（利用 $Ax_1+By_1=Ax_2+By_2$ ，$a'$ 和 $b'$ 互质推导可得）。
若要使 $x'$ 最小，则不断减去 $b'$ ，此过程相当于模运算，即 $$x_{min} = x' \mod b' $$ 其中 $\displaystyle x' = \frac{x_0C}{g}$ ， $b' = B/g$ ，因为 $x_{min}$ 有可能为负，所以最后的结果再修正为 
$$x_{min} = (x_{min} + b') \mod b'$$

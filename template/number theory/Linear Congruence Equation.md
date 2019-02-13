#### 解线性同余方程
设方程 ： $ax \equiv b \pmod n$

![](http://latex2png.com/output//latex_e40bbe6c28bbd020d555065841c86316.png)

因为 ax - b 是 n 的整数倍，设倍数为 y ，则 $ax-b=ny$ ，

![](http://latex2png.com/output//latex_27bd6162f791c748538433dc958e0a35.png)

移项得 $ax-ny=b$ 

![](http://latex2png.com/output//latex_523ff3a18ae163764268bf5ae542f1a3.png)

设 A = a ， B=-n ，C=b ，则为解不定方程 ： $$Ax + By = C$$ 

![](http://latex2png.com/output//latex_0c321ba84f9b3db8ac50e395c03016b6.png)

用扩展欧几里德算法求得方程 $$Ax+By=gcd(A,B)$$ 

![](http://latex2png.com/output//latex_87a9afb89a515bc009164c587e43cfb8.png)

的一组解 (x0,y0) ，设 g=gcd(A,B) ，则当 C 是 g 的倍数时（即 C % g == 0），方程 $$Ax + By = C$$

![](http://latex2png.com/output//latex_0c321ba84f9b3db8ac50e395c03016b6.png)

的一组解是 $\displaystyle(\frac{x_0C}{g},\frac{y_0C}{g})$ ，

![](http://latex2png.com/output//latex_adec02841ab3d1de066ccd45094b07f4.png)

当 C 不是 g 的倍数时无整数解。

又，若方程 $Ax + By = C$ 

![](http://latex2png.com/output//latex_f84f71d0694dc140535a4e5b042b2807.png)

的一组整数解为 (x',y') ，则它的任意整数解都可以写成 $$(x'-kb',y'+ka')$$

![](http://latex2png.com/output//latex_289f13a7304a91c43e2571cafe7b2397.png)

其中 a'=A/g , b'=B/g ， k 取任意整数。（利用 Ax_1+By_1=Ax_2+By_2 ，a' 和 b' 互质推导可得）。
若要使 x' 最小，则不断减去 b' ，此过程相当于模运算，即 $$x_{min} = x' \mod b' $$ 

![](http://latex2png.com/output//latex_60dd225e638745a0050b2fd95cba893a.png)

其中 $\displaystyle x' = \frac{x_0C}{g}$ ， $b' = B/g$ ，

![](http://latex2png.com/output//latex_b9bcec6dc98aa4e7dce61dea5feb72a3.png)

因为 $x_{min}$ 有可能为负，所以最后的结果再修正为 $$x_{min} = (x_{min} + b') \mod b'$$

![](http://latex2png.com/output//latex_37d628cdebb1e80bcb389e62da9b1ddb.png)

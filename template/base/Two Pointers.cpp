int ans = 0;
for (int pl = 0, pr = 0; pl < n; ++pl) {  // 枚举左指针
    while (pr < n && check(pr)) pr++;     // 右指针尽可能右移
    ans = max(ans, pr - pl);              // 更新答案
    work(pl);                             // 消除当前左指针的影响
}

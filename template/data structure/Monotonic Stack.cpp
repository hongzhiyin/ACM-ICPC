/*
1. l[i] 表示左边第一个 < a[i] 的数的位置 , r[i] 表示右边第一个 < a[i] 的数的位置
2. 根据需要改变程序中的比较运算符 ( 第一个小于 : >= / 第一个小于等于 : > / 其他同理 )
3. 有时两个数覆盖的范围重合，造成重复计算贡献时，可使用类似 左边第一个小于，右边第一个小于等于 这样的处理区间方法
*/

vi s;
int l[N], r[N];
void work(int a[], int n) { // a[] 从 0 开始
    s.clear();
    rep(i, 0, n) {
        while (!s.empty() && a[s.back()] >= a[i]) s.pop_back();
        if (s.empty()) l[i] = -1;
        else l[i] = s.back();
        s.pb(i);
    }
    s.clear();
    per(i, 0, n) {
        while (!s.empty() && a[s.back()] >= a[i]) s.pop_back();
        if (s.empty()) r[i] = n;
        else r[i] = s.back();
        s.pb(i);
    }
}

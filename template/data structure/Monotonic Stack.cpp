// 找到左右两边第一个小于 a[i] 的位置

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

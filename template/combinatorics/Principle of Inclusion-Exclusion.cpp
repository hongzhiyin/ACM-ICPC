// [1, num] 中与 x 互质的数的个数
// vector <int> pf 中存储 x 的质因数
// 刚开始假设全都是，个数为 num
// 扣掉包含一个质因数的，加上包含两个质因数的 ...
// 以此类推

vi pf;
int Cnt(int num) {
    int res = num;
    rep(mask, 1, 1 << sz(pf)) {
        int cnt = 0, tmp = 1;
        rep(i, 0, sz(pf)) if ((mask >> i) & 1) {
            ++cnt;
            tmp *= pf[i];
        }
        if (cnt & 1) res -= num / tmp;
        else res += num / tmp;
    }
    return res;
}

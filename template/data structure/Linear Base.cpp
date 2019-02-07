ll base[100];
void GetBase(ll a[], int n) {  // 注意 a[] 被修改了
    rep(i, 0, n) per(j, 0, 63) {
        if (!(a[i] >> j)) continue;
        if (!base[j]) { base[j] = a[i]; break; }
        a[i] ^= base[j];
    }
}

ll GetMax() {
    ll res = 0;
    per(i, 0, 63) if ((res ^ base[i]) > res) res ^= base[i];
    return res;
}

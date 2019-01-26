void qsort(int l, int r) {
    if (l >= r) return ;
    int i = l, j = r;
    ll mid = a[(l+r)>>1];
    while (i <= j) {
        while (a[i] < mid) ++i;
        while (a[j] > mid) --j;
        if (i <= j) swap(a[i++], a[j--]);
    }
    qsort(l, j);
    qsort(i, r);
}

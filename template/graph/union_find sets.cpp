void Init(int n) {
    rep(i, 0, n) fa[i] = i;
}

int Find(int x) {
    return fa[x] == x ? x : fa[x] = Find(fa[x]);
}

void Union(int a,int b) {
    int Fa = Find(a),Fb = Find(b);
    if (Fa != Fb) fa[Fb] = Fa;
}

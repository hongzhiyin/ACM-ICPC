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

void Split(int a, int b)
{
    int Fa = Find(a), Fb = b;
    int tmp = to[a]; to[a] = to[b]; to[b] = tmp;
    while (Find(b) == Fa) {
        fa[b] = Fb;
        b = to[b];
    }
}

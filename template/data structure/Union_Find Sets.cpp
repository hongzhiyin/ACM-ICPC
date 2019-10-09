void Init(int n) { rep(i, 0, n) fa[i] = i; }

int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }

void Union(int x, int y) { if (Find(x) != Find(y)) fa[Find(y)] = Find(x); }

void Split(int a, int b)
{
    int Fa = Find(a), Fb = b;
    int tmp = to[a]; to[a] = to[b]; to[b] = tmp;
    while (Find(b) == Fa) {
        fa[b] = Fb;
        b = to[b];
    }
}

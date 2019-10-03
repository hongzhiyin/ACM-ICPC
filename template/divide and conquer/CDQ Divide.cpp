/*
< 注意 >
    1. 偏序关系为小于等于：
    .. cmp 中三维都按从小到大排序
    .. 因为归并过程中，若左部元素与右部元素 x 相等
    .. 当左部元素 y 小于右部元素 y 时，可加入贡献
    2. 偏序关系为小于：
    .. cmp 中 x 从小到大排序， y 和 z 从大到小排序
    .. 因为归并过程中，若左部元素与右部元素 x 相等
    .. 当左部元素 y 小于右部元素 y 时，不可加入贡献
    .. 因此初始排序时，若 x 相等， y 值大的应该放在左边
*/

/* << head >> */
const int N = (int)2e5+7;

// ------- 变量 ------- //

int n, k, ans[N];
struct node {
    int x, y, z, num, ans;
    bool operator == (const node &b) const {
        return x == b.x && y == b.y && z == b.z;
    }
} a[N], b[N];

typedef int T;
int fn; T t[N];
struct Fenwick {
    void init(int n) { fn = n; memset(t, 0, sizeof(t[0]) * (fn+1)); }
    void upd(int x, T d) { for (; x <= fn; x += x&-x) t[x] += d; }
    T sum(int x) { T r = 0; for (; x; x -= x&-x) r += t[x]; return r; }
    T qry(int l, int r) { return sum(r) - sum(l-1); }
} fen;

// ------- 函数 ------- //

bool cmp(node a, node b) {
    return a.x < b.x || (a.x == b.x && (a.y < b.y || a.y == b.y && a.z < b.z));
}

void msort(int l, int r) {
    // 因为是小于等于，所以元素自己对自己有 a[l].num - 1 的贡献
    if (l == r) { a[l].ans = a[l].num - 1; return ; }

    // 因为有对第一维排序，所以首先保证左边部分的 x 一定小于等于右边部分的 x
    // 然后先对左右两部分归并，归并之后，保证当前左右两部分的 y 各自都是有序的
    int m = l + r >> 1;
    msort(l, m); msort(m + 1, r);

    int pos = l;
    rep(i, m + 1, r + 1) {
        // 将左边 x 和 y 都小于等于右边的元素的 z 加入树状数组
        for (; pos <= m && a[pos].y <= a[i].y; pos++)
            fen.upd(a[pos].z, a[pos].num);

        // 统计 z 小于等于 a[i].z 的元素个数
        a[i].ans += fen.sum(a[i].z);
    }

    // 清空树状数组
    rep(i, l, pos) fen.upd(a[i].z, -a[i].num);
    
    // 归并 y ，使 y 有序
    int i = l, j = m + 1;
    rep(k, l, r + 1) {
        if (j > r || i <= m && a[i].y <= a[j].y) b[k] = a[i++];
        else b[k] = a[j++];
    }
    rep(k, l, r + 1) a[k] = b[k];
}

void Init() {
    fen.init(N-2);

    scanf("%d", &n);
    rep(i, 1, n+1) scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
}

int Solve() {
    // 对第一维排序
    sort(a + 1, a + n + 1, cmp);

    // 去重
    int tn = 0;
    rep(i, 1, n+1) {
        if (i > 1 && a[i] == a[i-1]) a[tn].num++;
        else a[++tn] = a[i], a[tn].num = 1, a[tn].ans = 0;
    }

    // 对第二维归并
    msort(1, tn);

    // a[i].ans : 有 a[i].ans 个元素小于等于 a[i]
    // a[i].num : 与 a[i] 相等的元素有 a[i].num 个
    // 因为去重过，所以 a[i].num 个元素都有 a[i].ans 个元素小于等于它
    rep(i, 1, tn + 1) ans[a[i].ans] += a[i].num;
    
    // ans[i] : 有 i 个元素小于等于自己 的元素有 ans[i] 个
    rep(i, 0, n) printf("%d\n", ans[i]);
    return 0;
}

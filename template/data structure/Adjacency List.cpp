T node[N];      // 树： N = 点数 * 2
int no, net[N];
struct Vector {
    int head;
    Vector() { head = 0; }
    void clear() { head = 0; }
    void push_back(T x) {
        no++;
        node[no] = x;
        net[no] = head;
        head = no;
    }
};
Vector e[N];
void Init() {
    no = 0;
    rep(i, 0, n) e[i].clear();
}
// 遍历
for (int i = e[u].head; i; i = net[i]) {

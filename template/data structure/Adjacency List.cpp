T node[N];      // 无向边 : N << 1
int no, net[N];
struct Vector {
    int head;
    void clear() { head = 0; }
    void push_back(T x) {
        node[++no] = x; net[no] = head; head = no;
    }
};
Vector e[N];
void Init() {
    no = 0; rep(i, 0, n) e[i].clear();
}
// 遍历
for (int i = e[u].head; i; i = net[i]) {
    T v = node[i];

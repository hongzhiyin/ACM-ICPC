struct DDQ {  //单调队列
    int id, l, r;
    pii mx;
    deque <pii> q;
    void init() { id = 0; while (!q.empty()) q.pop_back(); }
    int front() { return q.front().fi; }
    void push(int x) {
        id++; r++;
        while (!q.empty() && q.back().fi < x) q.pop_back();     // 单调递减，求最大值
        // while (!q.empty() && q.back().fi > x) q.pop_back();     // 单调递增，求最小值
        q.pb(mp(x, id));
        maintain();
    }
    void maintain() {
        while (q.back().se - q.front().se > len) q.pop_front();   // 窗口长度限制 len
    }
};


// 窗口内 max - min <= k
struct DDQ {  //单调队列
    int id, l, r;
    pii mi, ma;
    deque <pii> maxq, minq;
    void init() { id = r = 0; l = 1; }
    void push(int x) {
        id++; r++;
        while (!maxq.empty() && maxq.back().fi <= x) maxq.pop_back();   //单调递减，队首最大
        maxq.push_back({x, id});
        while (!minq.empty() && minq.back().fi >= x) minq.pop_back();   //单调递增，队首最小
        minq.push_back({x, id});
        maintain();
    }
    void maintain() {
        while (maxq.front().fi - minq.front().fi > k) {
            if (maxq.front().se < minq.front().se) {
                l = maxq.front().se + 1;
                maxq.pop_front();
            } else {
                l = minq.front().se + 1;
                minq.pop_front();
            }
        }
    }
    int size() { return r - l + 1; }
} Q;

struct DDQ {  //单调队列
    int id, l, r;
    pii mi, ma;
    deque <pii> maxq, minq;
    DDQ() { id = r = 0; l = 1; }
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

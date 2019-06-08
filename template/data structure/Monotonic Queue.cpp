deque < pair<ll, int> > Q;
void Clear() { Q.clear(); }

void Push(ll val, int id) {
    while (!Q.empty() && Q.back().fi < val) Q.pop_back();
    Q.pb(mp(val, id));
}

ll Front(int id) {
    while (!Q.empty() && id - Q.front().se > K) Q.pop_front(); 
    return Q.front().fi;
}

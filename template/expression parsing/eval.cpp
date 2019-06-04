char buf[N];

#define ss stringstream

ll parseOr(ss &s);

ll parseInt(ss &s) {
    ll res; s >> res; return res;
}

ll parseBracket(ss &s) {
    if (s.peek() == '(') {
        s.get();
        ll res = parseOr(s);
        s.get();
        return res;
    }
    return parseInt(s);
}

ll parseSign(ss &s) {
    if (s.peek() == '+') { s.get(); return parseSign(s); }
    if (s.peek() == '-') { s.get(); return -parseSign(s); }
    if (s.peek() == '~') { s.get(); return ~parseSign(s); }
    return parseBracket(s);
}

ll parseMul(ss &s) {
    ll res = parseSign(s);
    if (s.peek() == '*') s.get(), res *= parseMul(s);
    if (s.peek() == '/') s.get(), res /= parseMul(s);
    return res;
}

ll parseAdd(ss &s) {
    ll res = parseMul(s);
    if (s.peek() == '+') s.get(), res += parseAdd(s);
    if (s.peek() == '-') s.get(), res -= parseAdd(s);
    return res;
}

ll parseAnd(ss &s) {
    ll res = parseAdd(s);
    if (s.peek() == '&') s.get(), res &= parseAnd(s);
    return res;
}

ll parseXor(ss &s) {
    ll res = parseAnd(s);
    if (s.peek() == '^') s.get(), res ^= parseXor(s);
    return res;
}

ll parseOr(ss &s) {
    ll res = parseXor(s);
    if (s.peek() == '|') s.get(), res |= parseOr(s);
    return res;
}

ll eval(string str) {
    ss s(str);
    return parseOr(s);
}

int Solve() {
    scanf("%s", buf);
    string str(buf);
    ll ans = eval(str);
    return printf("%lld\n", ans);
}

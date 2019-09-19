template <class T>
struct Fra {
    T a, b;
    Fra () : a(0), b(1) {}
    Fra (T _a, T _b) {
        T g = __gcd(_a, _b);
        a = _a / g, b = _b / g;
        if (b < 0) a = -a, b = -b;
    }
    Fra operator + (const Fra &c) { return Fra(a * c.b + b * c.a, b * c.b); }
    Fra operator - (const Fra &c) { return Fra(a * c.b - b * c.a, b * c.b); }
    Fra operator * (const Fra &c) { return Fra(a * c.a, b * c.b); }
    Fra operator / (const Fra &c) { return Fra(a * c.b, b * c.a); }
    Fra operator * (const T &c) { return Fra(a * c, b); }
    Fra operator / (const T &c) { return Fra(a, b * c); }
    bool operator == (const Fra &c) const { return a == c.a && b == c.b; }
    bool operator != (const Fra &c) const { return !(*this == c); }
    void print() { printf("%lld / %lld\n", a, b); }
};

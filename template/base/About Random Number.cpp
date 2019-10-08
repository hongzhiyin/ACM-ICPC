/*
< 说明 >
    mt19937 : 基于梅森旋转法的随机数生成引擎
    uniform_int_distribution  : 整型数 [l, r] 均匀分布
    uniform_real_distribution : 浮点数 [l, r) 均匀分布

< 使用 >
    1. rll(l, r)  : 返回 [l, r] 之间的一个整型随机数
    2. rdb(l, r)  : 返回 [l, r) 之间的一个浮点随机数
    3. shuf(a)    : 将容器 a 随机混洗
    4. shuf(a, n) : 将长度为 n 的数组 a[] 随机混洗，下标从 0 开始
*/

mt19937 rng(time(0));
struct Random_Number_Generator {
    ll rll(ll l, ll r) { return uniform_int_distribution <ll> (l, r) (rng); }
    db rdb(db l, db r) { return uniform_real_distribution <db> (l, r) (rng); }
    template <typename T> void shuf(vector<T> &a) { shuffle(a.begin(), a.end(), rng); } 
    template <typename T> void shuf(T a[], int n) { shuffle(a, a + n, rng); }
} rnd;

/*
< 说明 >
    mt19937 : 基于梅森旋转法的随机数生成引擎
    uniform_int_distribution  : 整型数 [l, r] 均匀分布
    uniform_real_distribution : 浮点数 [l, r) 均匀分布

< 使用 >
    1. rnd_ll(l, r) 返回 [l, r] 之间的一个整型随机数
    2. rnd_db(l, r) 返回 [l, r) 之间的一个浮点随机数
    3. shuffle(a.begin(), a.end(), rng); 可将容器 a 随机混洗
*/

mt19937 rng(time(0));
ll rnd_ll(ll l, ll r) {
    return uniform_int_distribution <ll> (l, r) (rng);
}
db rnd_db(db l, db r) {
    return uniform_real_distribution <db> (l, r) (rng);
}

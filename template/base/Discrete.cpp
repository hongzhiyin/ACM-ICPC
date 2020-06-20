/* ----- 离散化 -----
< 参数 >
    1. first 和 last 为随机访问迭代器

< 使用 >
    1. 使用方法同 std::sort()
*/

template <class Iter>
auto Discrete(Iter first, Iter last) {
    typedef typename iterator_traits<Iter>::value_type T;
    vector <T> dis, res(last - first + 1);                                          // 临时容器和待返回容器
    for (Iter i = first; i != last; ++i) dis.push_back(*i);                         // 放入临时容器
    sort(dis.begin(), dis.end());                                                   // 排序
    dis.erase(unique(dis.begin(), dis.end()), dis.end());                           // 去重
    for (Iter i = first; i != last; ++i)                                            // 二分获取离散值
        res[i-first+1] = lower_bound(dis.begin(), dis.end(), *i) - dis.begin() + 1; // 下标和离散值都从 1 开始
    return res;                                                                     // 返回离散后的容器
}
/* ----- 快速排序 -----
< 参数 >
    1. first 和 last 为随机访问迭代器

< 使用 >
    1. 使用方法同 std::sort()
*/

template <class T>
T median(T &a, T &b, T &c) {
    if (a < b)
        if (b < c) return b;        // a < b, b < c
        else if (a < c) return c;   // a < b, b >= c, a < c
        else return a;              // a < b, b >= c, a >= c
    else if (a < c) return a;       // a >= b, a < c 
    else if (b < c) return c;       // a >= b, a >= c, b < c
    else return b;                  // a >= b, a >= c, b >= c
}

template <class Iter>
void Quick_Sort(Iter first, Iter last) {
    if (first == last) return;                          // 容器
    Iter i = first, j = last - 1;                       // 双指针分割区间
    typename iterator_traits<Iter>::value_type pivot;   // 枢轴
    pivot = median(*i, *(i + (j - i) / 2), *j);         // 三数取中值
    while (i <= j) {                                    // 指针相等也要移动指针，否则区间无分割
        while (*i < pivot) ++i;                         // 第一个大于等于 pivot 的元素
        while (*j > pivot) --j;                         // 第一个小于等于 pivot 的元素
        if (i <= j) swap(*(i++), *(j--));               // 交换元素，就算相等也要让指针移动
    }
    Quick_Sort(first, j + 1);                           // 左区间
    Quick_Sort(i, last);                                // 右区间
}
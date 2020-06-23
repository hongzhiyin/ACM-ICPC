/* ----- 归并排序 -----
< 参数 >
    1. first 和 last 为随机访问迭代器

< 使用 >
    1. 使用方法同 std::sort()
*/

template <class Iter>
void Merge_Sort(Iter first, Iter last) {
    if (first == last || last - first == 1) return;                             // 容器为空或容量为 1
    Iter middle = first + (last - first) / 2;                                   // 区间中点 middle
    Merge_Sort(first, middle); Merge_Sort(middle, last);                        // 排序左右区间
    inplace_merge(first, middle, last);                                         // 归并左右区间
}
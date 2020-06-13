/* ----- 选择排序 -----
< 参数 >
    1. first 和 last 为随机访问迭代器

< 使用 >
    1. 使用方法同 std::sort()
*/

template <class Iter>
void Selection_Sort(Iter first, Iter last) {
    if (first == last) return;
    for (Iter tmp = first; first != last; tmp = ++first) {
        for (Iter i = first + 1; i != last; ++i) {
            if (*i < *tmp) tmp = i;
        }
        swap(*first, *tmp);
    }
}
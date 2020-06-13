/* ----- 冒泡排序 -----
< 参数 >
    1. first 和 last 为随机访问迭代器

< 使用 >
    1. 使用方法同 std::sort()
*/

template <class Iter>
void Bubble_Sort(Iter first, Iter last) {
    if (first == last) return;
    for (--last; first != last; --last) {
        for (Iter i = first; i != last; ++i) {
            if (*i > *(i + 1)) swap(*i, *(i+1));
        }
    }
}
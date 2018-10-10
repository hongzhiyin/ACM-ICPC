// 找到已排序的容器内 x 的出现范围，可用于计算容器内 x 的出现次数
// 返回 pair ，first 为 x 首次出现的位置， second 为 x 最后一次出现的位置的下一个位置
// 复杂度：随机迭代器 O(logN) ，非随机迭代器 O(N)
auto it = equal_range(all(v), x);
cnt = it.se - it.fi

// 消除字符串 s 首尾空格
s.erase(0, s.find_first_not_of(" "));
s.erase(s.find_last_not_of(" ") + 1);

// 分割字符串 s
int pos = s.find("  ");
s1 = s.substr(0, pos);
s2 = s.substr(pos, sz(str)-pos);

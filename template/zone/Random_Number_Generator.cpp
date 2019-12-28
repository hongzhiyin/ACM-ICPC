#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=(a);i<(b);++i)
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)

// How to do
// 浏览 generators 文件夹下所有样例代码
// 将其调用到的函数在 testlib.h 源码下查看文档
// 详细翻译 testlib.h 中相应的文档
// 简略更新进本文件中，包括使用方法、输入输出等。

// Currently "gen-tree-graph.cpp"

// 生成范围在 [0, n) 内的随机数，根据 t 的大小及正负决定偏移程度和方向。
template <typename T>
T Gen_Number(T n, int t = 0) {
    return t ? rnd.wnext(n, t) : rnd.next(n);
}

// 整型： [from, to]  |  浮点型： [from, to)
template <typename T>
T Gen_Range_Number(T from, T to, int t = 0) {
    return t ? rnd.wnext(from, to, t) : rnd.next(from, to);
}

// 通过给定模式生成的随机字符串值。
// ptrn = "[a-z]{1,5}";         生成长度从 1 到 5 的小写字母随机字符串
// ptrn = "mike|john";          生成 "mike" 或 "john"
// ptrn = "-?[1-9][0-9]{0,3}";  生成从 -9999 到 9999 的非零整数
// ptrn = "id-([ac]|b{2})";     生成 "id-a", "id-bb", "id-c"
// ptrn 可包含占位符，如 rnd.next("[a-zA-Z0-9]{1,%d}", length) 。
string Gen_String(string ptrn) {
    return rnd.next(ptrn);
}

// 生成一个大小为 size ，索引从 first 开始的随机排列
template<typename T>
vector <T> Gen_Permutation(int size, T first) {
    return rnd.perm(size, first);
}

// 返回容器内的随机元素
template <typename Container>
typename Container::value_type Get_Element(const Container &con, int t = 0) {
    return t ? rnd.wany(con, t) : rnd.any(con);
}

// 返回迭代器范围内的随机元素
template <typename Iter>
typename Iter::value_type Get_Range_Element(const Iter &begin, const Iter &end, int t = 0) {
    return t ? rnd.wany(begin, end, t) : rnd.any(begin, end);
}

// 生成 n 个范围在 [from, to] 的随机数
template <typename T>
vector <T> Gen_Array(int n, T from, T to) {
    vector <T> res(n);
    rep(i, 0, n) res[i] = rnd.next(from, to);
    return res;
}

// 生成一个左部 n 个点，右部 m 个点， k 条边的二分图
vector < pair<int, int> > Gen_Bipartite_Graph(int n, int m, int k) {
    vector < pair <int, int> > edges(k);
    int t = rnd.next(-2, 2);
    
    rep(i, 0, k) {
        int u = rnd.wnext(n, t), v = rnd.wnext(m, t);
        edges[i] = make_pair(u, v);
    }
    shuffle(edges.begin(), edges.end());

    vector <int> id_u(n);
    rep(i, 0, n) id_u[i] = i + 1;
    shuffle(id_u.begin(), id_u.end());

    vector <int> id_v(m);
    rep(i, 0, m) id_v[i] = i + 1;
    shuffle(id_v.begin(), id_v.end());

    rep(i, 0, k) {
        edges[i].first = id_u[edges[i].first];
        edges[i].second = id_v[edges[i].second];
    }

    return edges;
}

// 生成一棵 n 个节点，根节点为 1 的有根树
// [ 菊花图 ] -INF <=== t ===> +INF [ 单链 ]
// parent[] 保存除根节点外每个节点的父节点
vector <int> Gen_Rooted_Tree(int n, int t) {
    vector <int> fa(n);
    rep(i, 1, n) fa[i] = rnd.wnext(i, t);

    vector <int> id(n);
    rep(i, 0, n) id[i] = i + 1;
    shuffle(id.begin() + 1, id.end());

    vector <int> parent(n+1);
    rep(i, 1, n) parent[id[i]] = id[fa[i]];

    return parent;
}

// 生成一颗 n 个节点的无根树
vector < pair<int, int> > Gen_Tree(int n, int t) {
    vector <int> parent(n);
    rep(i, 1, n) parent[i] = rnd.wnext(i, t);

    vector <int> id(n);
    rep(i, 0, n) id[i] = i + 1;
    shuffle(id.begin() + 1, id.end());

    vector < pair<int, int> > edges;
    rep(i, 1, n) {
        if (rnd.next(2)) edges.push_back(make_pair(id[i], id[parent[i]]));
        else edges.push_back(make_pair(id[parent[i]], id[i]));
    }
    shuffle(edges.begin(), edges.end());
    
    return edges;
}

int main(int argc, char* argv[])
{
    // 开启 Generator 模式，并通过命令行参数初始化随机种子
    registerGen(argc, argv, 1);
    
    // 程序地址保存在 argv[0] 中，因此命令行参数从 argv[1] 开始
    int argument = atoi(argv[1]);

    // 在一行内输出元素并换行
    vector <int> container;
    println(container[0]);                          /* 输出一个元素 */
    println(container);                             /* 输出一个容器内的所有元素 */
    println(container.begin(), container.end());    /* 输出一个迭代器范围内的元素 */

    return 0;
}

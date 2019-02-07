// https://www.luogu.org/blog/Chanis/gnu-pbds

// 可并堆
#include <ext/pb_ds/priority_queue.hpp>
__gnu_pbds::priority_queue <pii, greater<pii>, __gnu_pbds::pairing_heap_tag> heap[N];

heap[x].join(heap[y]);

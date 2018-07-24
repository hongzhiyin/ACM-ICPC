struct Node {//
	int key, pri, sz, son[2];
	void setval(int x, int z = 1) {
		static int seed = 3312;
		key = x;
		pri = seed = (int)((ll)seed * 48271 % 2147483647);
		sz = z;
		son[0] = son[1] = 0;
	}
};

struct Treap {
	int root, cnt;
	Node T[N];
	void init() { root = 0; cnt = 1; }
	void rotate(int &x, int p) {
		int y = T[x].son[!p];
		T[x].son[!p] = T[y].son[p];
		T[y].son[p] = x;
		T[y].sz = T[x].sz;
		T[x].sz = T[T[x].son[0]].sz + 1 + T[T[x].son[1]].sz;
		x = y;
	}
	void ins(int &x, int val) {
		if (x == 0) {
			T[x = cnt++].setval(val);
		} else {
			++T[x].sz;
			int p = val > T[x].key;
			ins(T[x].son[p], val);
			if (T[x].pri > T[T[x].son[p]].pri)
				rotate(x, !p);
		}
	}
	void del(int &x, int val) {
		if (T[x].key == val) {
			if (T[x].son[0] && T[x].son[1]) {
				--T[x].sz;
				int p = T[T[x].son[0]].pri < T[T[x].son[1]].pri;
				rotate(x, p);
				del(T[x].son[p], val);
			} else {
				if (!T[x].son[0]) x = T[x].son[1];
				else x = T[x].son[0];
			}
		} else {
			--T[x].sz;
			int p = T[x].key < val;
			del(T[x].son[p], val);
		}
	}
	int findKth(int &x, int k) {
		if (k <= 0 || x == 0 || k > T[x].sz) return -1;
		if (k == T[T[x].son[0]].sz + 1) return x;
		if (k > T[T[x].son[0]].sz + 1)
			return findKth(T[x].son[1], k - T[T[x].son[0]].sz - 1);
		return findKth(T[x].son[0], k);
	}
	int find(int &x, int val) {
		if (x == 0) return -1;
		if (val == T[x].key) return x;
		return find(T[x].son[T[x].key < val], val);
	}
	int Count(int &x, int val) {
		if (x == 0) return 0;
		if (val < T[x].key) return Count(T[x].son[0], val);
		if (val == T[x].key) return T[T[x].son[0]].sz;
		return T[x].sz - T[T[x].son[1]].sz + Count(T[x].son[1], val);
	}
};


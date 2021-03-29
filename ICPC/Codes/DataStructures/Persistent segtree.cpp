struct Per {
  int l, r;
  Per *left, *right;
  lli sum = 0;

  Per(int l, int r) : l(l), r(r), left(0), right(0) {}

  Per* pull() {
    sum = left->sum + right->sum;
    return this;
  }

  void build() {
    if (l == r)
      return;
    int m = (l + r) >> 1;
    (left = new Per(l, m))->build();
    (right = new Per(m + 1, r))->build();
    pull();
  }

  Per* update(int p, lli v) {
    if (p < l || r < p)
      return this;
    Per* t = new Per(l, r);
    if (l == r) {
      t->sum = v;
      return t;
    }
    t->left = left->update(p, v);
    t->right = right->update(p, v);
    return t->pull();
  }

  lli query(int ll, int rr) {
    if (r < ll || rr < l)
      return 0;
    if (ll <= l && r <= rr)
      return sum;
    return left->query(ll, rr) + right->query(ll, rr);
  }
};

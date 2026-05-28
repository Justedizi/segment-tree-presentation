#include "segment_tree.hpp"
#include <algorithm>
#include <iostream>

Node SegmentTree::combine(const Node &left, const Node &right) {
  if (left.ans == MIN_INF)
    return right;
  if (right.ans == MIN_INF)
    return left;

  Node res;
  res.sum = left.sum + right.sum;
  res.pref = std::max(left.pref, left.sum + right.pref);
  res.suff = std::max(right.suff, right.sum + left.suff);
  res.ans = std::max({left.ans, right.ans, left.suff + right.pref});
  return res;
}

Node SegmentTree::make_node(long long val) { return {val, val, val, val}; }

SegmentTree::SegmentTree(int capacity)
    : max_capacity(capacity), current_size(0) {
  tree.assign(4 * max_capacity, {0, MIN_INF, MIN_INF, MIN_INF});
}

void SegmentTree::update_tree(int node, int left, int right, int index,
                              long long value) {
  if (left == right) {
    tree[node] = make_node(value);
    return;
  }
  int mid = left + (right - left) / 2;
  if (index <= mid) {
    update_tree(2 * node, left, mid, index, value);
  } else {
    update_tree(2 * node + 1, mid + 1, right, index, value);
  }
  tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
}

Node SegmentTree::query_tree(int node, int left, int right, int q_left,
                             int q_right) {
  if (q_left > right || q_right < left)
    return {0, MIN_INF, MIN_INF, MIN_INF};
  if (q_left <= left && right <= q_right)
    return tree[node];

  int mid = left + (right - left) / 2;
  return combine(query_tree(2 * node, left, mid, q_left, q_right),
                 query_tree(2 * node + 1, mid + 1, right, q_left, q_right));
}

void SegmentTree::addElement(long long value) {
  if (current_size >= max_capacity) {
    std::cerr << "Przekroczono maksymalną pojemność drzewa!\n";
    return;
  }
  update_tree(1, 0, max_capacity - 1, current_size, value);
  current_size++;
}

void SegmentTree::updateElement(int index, long long value) {
  update_tree(1, 0, max_capacity - 1, index, value);
}

long long SegmentTree::queryMaxSubarray(int l, int r) {
  if (l < 0 || r >= current_size || l > r)
    return 0;
  return query_tree(1, 0, max_capacity - 1, l, r).ans;
}

int SegmentTree::getSize() const { return current_size; }

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
  tree.assign(2 * max_capacity, {0, MIN_INF, MIN_INF, MIN_INF});
}

void SegmentTree::addElement(long long value) {
  if (current_size >= max_capacity) {
    std::cerr << "Przekroczono maksymalną pojemność drzewa!\n";
    return;
  }
  updateElement(current_size, value);
  current_size++;
}

void SegmentTree::updateElement(int index, long long value) {
  index += max_capacity;
  tree[index] = make_node(value);

  for (index /= 2; index > 0; index /= 2) {
    tree[index] = combine(tree[2 * index], tree[2 * index + 1]);
  }
}

long long SegmentTree::queryMaxSubarray(int l, int r) {
  if (l < 0 || r >= current_size || l > r)
    return 0;

  l += max_capacity;
  r += max_capacity;

  Node resL = {0, MIN_INF, MIN_INF, MIN_INF};
  Node resR = {0, MIN_INF, MIN_INF, MIN_INF};

  while (l <= r) {
    if (l % 2 == 1) {
      resL = combine(resL, tree[l]);
      l++;
    }
    if (r % 2 == 0) {
      resR = combine(tree[r], resR);
      r--;
    }
    l /= 2;
    r /= 2;
  }

  return combine(resL, resR).ans;
}

int SegmentTree::getSize() const { return current_size; }

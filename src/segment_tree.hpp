#pragma once
#include <vector>

const long long MIN_INF = -1e15;

struct Node {
  long long sum;
  long long pref;
  long long suff;
  long long ans;
};

class SegmentTree {
private:
  std::vector<Node> tree;
  int max_capacity;
  int current_size;

  Node combine(const Node &left, const Node &right);
  Node make_node(long long val);

public:
  SegmentTree(int capacity);
  void addElement(long long value);
  void updateElement(int index, long long value);
  long long queryMaxSubarray(int l, int r);
  int getSize() const;
};

#include "segment_tree.hpp"
#include <iostream>
#include <vector>

int main() {
  std::vector<long long> nums = {14, -5, 12, -8, 11, -2, 7};
  SegmentTree tree(100);
  for (auto n : nums)
    tree.addElement(n);
  std::cout << tree.queryMaxSubarray(1, 4);
}

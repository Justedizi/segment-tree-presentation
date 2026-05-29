#include "segment_tree.hpp"
#include <iostream>
#include <vector>

int main() {
  std::vector<long long> nums = {
      14, -5, 12, -8, 11,
  };
  SegmentTree tree(nums.size());
  for (auto n : nums)
    tree.addElement(n);
  std::cout << tree.queryMaxSubarray(0, 4) << '\n';
  std::cout << tree.queryMaxSubarray(1, 3) << '\n';
}

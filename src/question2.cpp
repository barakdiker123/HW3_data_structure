
#include <algorithm>
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <set>

template <typename Data> struct BinTree {
  Data data;
  BinTree<Data> *left;
  BinTree<Data> *right;
  BinTree(Data data) : data(data) {
    left = nullptr;
    right = nullptr;
  }
};
template <typename Data> struct HeadBinTree {
  /**
   * @brief calculate how much nodes has each level
   * assumes arr_depth_count has all 0
   * assumes arr_depth_count array size is bigger than the depth of the tree
   *  */
  template <int N>
  static void helper_get_num_of_each_level(BinTree<Data> *node,
                                           std::array<int, N> &arr_depth_count,
                                           int current_depth = 1) {
    arr_depth_count[current_depth] += 1;
    if (node->left == nullptr && node->right == nullptr) {
      return;
    }
    if (node->left == nullptr) {
      helper_get_num_of_each_level<N>(node->right, arr_depth_count,
                                      current_depth + 1);
      return;
    }
    if (node->right == nullptr) {
      helper_get_num_of_each_level<N>(node->left, arr_depth_count,
                                      current_depth + 1);
      return;
    }
    helper_get_num_of_each_level<N>(node->right, arr_depth_count,
                                    current_depth + 1);
    helper_get_num_of_each_level<N>(node->left, arr_depth_count,
                                    current_depth + 1);
  }
  template <int N>
  static std::array<int, N> &get_num_of_each_level(BinTree<Data> *node) {
    std::array<int, N> *arr_depth_count = new std::array<int, N>();
    std::for_each(arr_depth_count->begin(), arr_depth_count->end(),
                  [](int &element) { element = 0; });
    helper_get_num_of_each_level<N>(node, *arr_depth_count);
    return *arr_depth_count;
  }
};

TEST_CASE("Tree first Test", "[tree]") {
  INFO("BARAK");
  REQUIRE(true);
  BinTree<int> tree1(1);
  BinTree<int> tree2(2);
  BinTree<int> tree3(3);
  BinTree<int> tree4(4);
  BinTree<int> tree5(5);
  BinTree<int> tree6(6);
  BinTree<int> tree7(7);

  tree1.left = &tree2;
  tree1.right = &tree3;
  tree3.left = &tree4;
  tree3.right = &tree5;
  tree2.left = &tree6;
  auto arr = HeadBinTree<int>::get_num_of_each_level<20>(&tree1);
  REQUIRE(arr[1] == 1);
  REQUIRE(arr[2] == 2);
  REQUIRE(arr[3] == 3);
}
/**
 *          tree1
 *         /      \
 *       tree2     tree3
 *       / \         / \
 *   tree6       tree4 tree5
 *  */

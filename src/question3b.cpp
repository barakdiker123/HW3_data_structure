

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

/**
 * @brief This function checks only if the root is between
 * all the grandchildrens
 * */
template <typename Data> struct HeadBinTree {
  // static void reverse_binary_tree(BinTree<Data> *node) {
  //   if (node->left == nullptr && node->right == nullptr) {
  //     return;
  //   }
  //   if (node->left == nullptr) {
  //     reverse_binary_tree(node->right);
  //     std::swap(node->right, node->left);
  //     return;
  //   }
  //   if (node->right == nullptr) {
  //     reverse_binary_tree(node->left);
  //     return;
  //   }
  //   reverse_binary_node(node->right);
  //   reverse_binary_tree(node->left);
  //   return;
  // }
  /**
   * Carefull this implementation is not true! */
  static void reverse_tree_naive(BinTree<Data> *node) {
    if (node != nullptr) {
      std::swap(node->left, node->right);
      reverse_tree_naive(node->left);
      reverse_tree_naive(node->right);
    }
  }
};

/**
 *          tree2
 *         /      \
 *       tree1     tree4
 *       / \         / \
 *               tree0       <----= This mistake 2 < 0 is false
 *  */
TEST_CASE("Checks if the root is not in between") {
  BinTree<int> tree1(1);
  BinTree<int> tree2(2);
  BinTree<int> tree0(0);
  BinTree<int> tree4(4);
  tree2.left = &tree1;
  tree2.right = &tree4;
  tree4.left = &tree0;
  HeadBinTree<int>::reverse_tree_naive(&tree2);
  REQUIRE(tree2.left->data == tree4.data);
}



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
  static bool
  check_if_all_nodes_satisfy_condition(BinTree<Data> *node,
                                       std::function<bool(int)> condition) {
    if (node->left == nullptr && node->right == nullptr) {
      return condition(node->data);
    }
    if (node->left == nullptr) {
      return condition(node->data) &&
             check_if_all_nodes_satisfy_condition(node->right, condition);
    }
    if (node->right == nullptr) {
      return condition(node->data) &&
             check_if_all_nodes_satisfy_condition(node->left, condition);
    }
    return condition(node->data) &&
           check_if_all_nodes_satisfy_condition(node->left, condition) &&
           check_if_all_nodes_satisfy_condition(node->right, condition);
  }
  /**
   * complexity O(n) where n is all the element in the tree */
  static bool is_root_between_grandchildren(BinTree<Data> *node) {
    Data data_head = node->data;
    if (node->left == nullptr && node->right == nullptr) {
      return true;
    }
    if (node->left == nullptr) {
      return check_if_all_nodes_satisfy_condition(
          node->right, [data_head](int num) { return data_head <= num; });
    }
    if (node->right == nullptr) {
      return check_if_all_nodes_satisfy_condition(
          node->left, [data_head](int num) { return data_head >= num; });
    }
    return check_if_all_nodes_satisfy_condition(
               node->left, [data_head](int num) { return data_head >= num; }) &&
           check_if_all_nodes_satisfy_condition(
               node->right, [data_head](int num) { return data_head <= num; });
  }
  /**
   * complexity O(n^2) where n is all the element in the tree */
  static bool is_binary_search_tree(BinTree<Data> *node) {
    if (node->left == nullptr && node->right == nullptr) {
      return true;
    }
    if (node->left == nullptr) {
      return is_root_between_grandchildren(node) &&
             is_binary_search_tree(node->right);
    }
    if (node->right == nullptr) {
      return is_root_between_grandchildren(node) &&
             is_binary_search_tree(node->left);
    }
    return is_root_between_grandchildren(node) &&
           is_binary_search_tree(node->right) &&
           is_root_between_grandchildren(node) &&
           is_binary_search_tree(node->left);
  }
};

/**
 *          tree2
 *         /      \
 *       tree1     tree4
 *       / \         / \
 *
 *   tree0       tree3 tree5
 *  */
TEST_CASE("Checks If the only the root is between grandchildren", "[tree]") {
  INFO("BARAK");
  BinTree<int> tree1(1);
  BinTree<int> tree2(2);
  BinTree<int> tree3(3);
  BinTree<int> tree4(4);
  BinTree<int> tree5(5);
  BinTree<int> tree0(0);

  tree2.left = &tree1;
  tree2.right = &tree4;
  tree4.left = &tree3;
  tree4.right = &tree5;
  tree1.left = &tree0;
  REQUIRE(HeadBinTree<int>::is_root_between_grandchildren(&tree2) == true);

  REQUIRE(HeadBinTree<int>::is_root_between_grandchildren(&tree3) == true);
}
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
  REQUIRE(HeadBinTree<int>::is_root_between_grandchildren(&tree2) == false);
}

/**
 *          tree2
 *         /      \
 *       tree1     tree4
 *       / \         / \
 *
 *   tree0       tree3 tree5
 *  */
TEST_CASE("Checks If the tree is binary search tree", "[tree]") {
  INFO("BARAK");
  BinTree<int> tree1(1);
  BinTree<int> tree2(2);
  BinTree<int> tree3(3);
  BinTree<int> tree4(4);
  BinTree<int> tree5(5);
  BinTree<int> tree0(0);

  tree2.left = &tree1;
  tree2.right = &tree4;
  tree4.left = &tree3;
  tree4.right = &tree5;
  tree1.left = &tree0;
  REQUIRE(HeadBinTree<int>::is_binary_search_tree(&tree2) == true);
  REQUIRE(HeadBinTree<int>::is_binary_search_tree(&tree3) == true);
}

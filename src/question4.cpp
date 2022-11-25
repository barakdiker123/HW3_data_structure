
// To run the tests
//   ./question4 --success
//   You'll the that the average of 10'000 element in bintree
//   is approximately 31 -> 36
//   note also that log2(10'000) = 13

#include "question4.h"
#include <algorithm>
#include <array>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <random>
#include <set>
#include <stdexcept>

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
  static void insert_into_binary_tree(BinTree<Data> *node, Data data) {
    BinTree<Data> *inserted_node = new BinTree<Data>(data);
    if (node == nullptr) {
      delete inserted_node;
      std::__throw_overflow_error("Inserting into empty tree");
      // Throws exception
      return;
    }
    BinTree<Data> *current_node = node;
    while (current_node != nullptr) {
      if (current_node->data <= inserted_node->data) {
        if (current_node->right == nullptr) {
          current_node->right = inserted_node;
          return;
        }
        current_node = current_node->right;
      } else {
        if (current_node->left == nullptr) {
          current_node->left = inserted_node;
          return;
        }
        current_node = current_node->left;
      }
    }
  }
  static BinTree<Data> *insert_into_binary_tree_full(BinTree<Data> *node,
                                                     Data data) {
    BinTree<Data> *inserted_node = new BinTree<Data>(data);
    if (node == nullptr) {
      return inserted_node;
    }
    insert_into_binary_tree(node, data);
    return node;
  }
  /**
   * @brief This function calculate the depth of the tree
   * @param [BinTree<Data>] The Head node
   * @returns The depth of the tree relative to the provided head
   *
   * */
  static int getDepth(BinTree<Data> *node, int currentDepth = 0) {
    if (node == nullptr) {
      return currentDepth;
    }
    return std::max(getDepth(node->left, currentDepth + 1),
                    getDepth(node->right, currentDepth + 1));
  }
};

/**
 *          tree2
 *         /      \
 *       tree0     tree4
 *       / \         / \
 *               tree3       <----= This mistake 2 < 0 is false
 *  */
TEST_CASE("Checks if the root is not in between") {
  BinTree<int> tree0(0);
  BinTree<int> tree2(2);
  BinTree<int> tree3(3);
  BinTree<int> tree4(4);
  tree2.left = &tree0;
  tree2.right = &tree4;
  tree4.left = &tree3;
  HeadBinTree<int>::insert_into_binary_tree(&tree2, 5);
  REQUIRE(tree2.right->right->data == 5);
  HeadBinTree<int>::insert_into_binary_tree(&tree2, 1);
  REQUIRE(tree2.left->right->data == 1);
}
TEST_CASE("Insert into empty tree") {
  BinTree<int> *tree0 = nullptr;
  REQUIRE_THROWS(HeadBinTree<int>::insert_into_binary_tree(tree0, 1));
  tree0 = HeadBinTree<int>::insert_into_binary_tree_full(tree0, 3);
  REQUIRE(tree0->data == 3);
}
TEST_CASE("Inserts 1000 elements into Bintree") {}

/**
 * Approximately 31 to 36 depth of the binary tree with 10'000 elements
 *
 * */
TEST_CASE("Generating random ints", "[example][generator]") {
  SECTION("Deducing functions") {
    std::uniform_int_distribution<> m_dist;
    BinTree<int> *head = nullptr;
    std::random_device r;
    // Choose a random mean between 1 and 6
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(-1'000'000, 1'000'000);
    INFO("Test case start");
    for (int i = 0; i < 10'000; i++) {
      head = HeadBinTree<int>::insert_into_binary_tree_full(head,
                                                            uniform_dist(e1));
    }
    std::cout << "The number is " << HeadBinTree<int>::getDepth(head) << '\n';
    // To run the tests
    //   ./question4 --success
    SECTION("A") {}
    SECTION("B") {}
    SECTION("C") {}
    SECTION("D") {}
    SECTION("e") {}
    SECTION("t") {}
    SECTION("g") {}
    SECTION("v") {}
  }
}

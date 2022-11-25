
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
  static bool searchElement(BinTree<Data> *node, Data data) {
    if (node == nullptr) {
      return false;
    }
    if (data == node->data) {
      return true;
    }
    return searchElement(node->left, data) || searchElement(node->right, data);
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
  /**
   * @brief calculate the number of leafs
   * @param node -> the head to the tree */
  static int getLeafs(BinTree<Data> *node) {
    if (node->left == nullptr && node->right == nullptr) {
      return 1;
    }
    if (node->left == nullptr) {
      return getLeafs(node->right);
    }
    if (node->right == nullptr) {
      return getLeafs(node->left);
    }
    return getLeafs(node->left) + getLeafs(node->right);
  }
  static bool helpIsPerfectTree(BinTree<Data> *node, int depth,
                                int current_depth = 1) {
    if (node->left == nullptr && node->right == nullptr) {
      return current_depth == depth;
    }
    if (node->left == nullptr) {
      return false;
    }
    if (node->right == nullptr) {
      return false;
    }
    return helpIsPerfectTree(node->left, depth, current_depth + 1) &&
           helpIsPerfectTree(node->right, depth, current_depth + 1);
  }
  static bool isPerfectTree(BinTree<Data> *node) {
    int depth = getDepth(node);
    return helpIsPerfectTree(node, depth);
  }
  static void balancedTree(BinTree<Data> *node, std::set<int> &depths,
                           int depth = 1) {
    if (node->left == nullptr && node->right == nullptr) {
      depths.insert(depth);
      return;
    }
    if (node->right == nullptr) {
      balancedTree(node->left, depths, depth + 1);
      return;
    }
    if (node->left == nullptr) {
      balancedTree(node->right, depths, depth + 1);
      return;
    }
    balancedTree(node->left, depths, depth + 1);
    balancedTree(node->right, depths, depth + 1);
  }
  static bool isBalancedTree(BinTree<Data> *node) {
    std::set<int> depths;
    balancedTree(node, depths);
    if (depths.size() == 0 || depths.size() == 1) {
      return true;
    }
    if (depths.size() > 2) {
      return false;
    }
    std::vector<int> depthsVector;
    std::copy(depths.begin(), depths.end(), std::back_inserter(depthsVector));
    if (std::abs(depthsVector[0] - depthsVector[1]) > 1)
      return false;
    else
      return true;
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
  REQUIRE(HeadBinTree<int>::searchElement(&tree1, 1) == true);
  REQUIRE(HeadBinTree<int>::searchElement(&tree1, 6) == true);
  REQUIRE(HeadBinTree<int>::searchElement(&tree1, 10) == false);
  REQUIRE(HeadBinTree<int>::getDepth(&tree1) == 3);
  // CAPTURE(HeadBinTree<int>::getDepth(&tree2));
  REQUIRE(HeadBinTree<int>::getDepth(&tree2) == 2);
  REQUIRE(HeadBinTree<int>::getDepth(&tree7) == 1);
  // INFO(HeadBinTree<int>::searchElement(&tree1, 10));
}

TEST_CASE("Tree second Test", "[tree]") {
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
  tree3.right = &tree5;
  REQUIRE(HeadBinTree<int>::getDepth(&tree1) == 3);
}

TEST_CASE("Test num of leaf function getLeaf()", "[leaf]") {
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

  REQUIRE(HeadBinTree<int>::getLeafs(&tree1) == 3);
  REQUIRE(HeadBinTree<int>::getLeafs(&tree2) == 1);
  REQUIRE(HeadBinTree<int>::getLeafs(&tree3) == 2);
}
TEST_CASE("test the function isPerfectTree", "[perfecttree]") {
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

  REQUIRE(HeadBinTree<int>::isPerfectTree(&tree1) == false);
  REQUIRE(HeadBinTree<int>::isPerfectTree(&tree2) == false);
  tree2.right = &tree7;
  REQUIRE(HeadBinTree<int>::isPerfectTree(&tree1) == true);
  REQUIRE(HeadBinTree<int>::isPerfectTree(&tree2) == true);
}
TEST_CASE("Test is balance tree balancedTree", "[balance]") {
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
  REQUIRE(HeadBinTree<int>::isBalancedTree(&tree1) == true);
}
// TEST_CASE("HADFGA DSG A", "[sadfa]") {
//   BinTree<int> tree1(1);
//   BinTree<int> tree2(2);
//   BinTree<int> tree3(3);
//   BinTree<int> tree4(4);
//   BinTree<int> tree5(5);
//   BinTree<int> tree6(6);
//   BinTree<int> tree7(7);
//
//   tree1.left = &tree2;
//   tree1.right = &tree3;
//   tree3.left = &tree4;
//   tree3.right = &tree5;
//   tree2.left = &tree6;
//   std::set<int> depths;
//   HeadBinTree<int>::balancedTree(&tree1, depths);
//   for (auto element : depths) {
//     INFO(element << '\n');
//     CHECK(false);
//   }
//   //  if (depths.size() == 0 || depths.size() == 1) {
//   //    return true;
//   //  }
//   //  if (depths.size() > 2) {
//   //    return false;
//   //  }
//   std::vector<int> depthsVector;
//   std::copy(depths.begin(), depths.end(), std::back_inserter(depthsVector));
//   INFO(depthsVector.size() << '\n');
//   INFO(depthsVector[0] << '\n');
//   INFO(depthsVector[1] << '\n');
//   CHECK(false);
//   // if (std::abs(depthsVector[0] - depthsVector[1]) > 1)
//
//   //   return false;
//   // else
//   //   return true;
// }
/**
 *          tree1
 *         /      \
 *       tree2     tree3
 *       / \         / \
 *   tree6       tree4 tree5
 *  */

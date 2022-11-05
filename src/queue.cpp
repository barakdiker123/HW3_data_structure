//#include "queue.h"

#include <array>
#include <catch2/catch_test_macros.hpp>

template <typename T, int N> class Queue {
private:
  std::array<T, N> arr;
  int last = 0;
  int first = 0;

public:
  explicit Queue() {
    first = 0;
    last = 0;
  }
  std::array<T, N> &get_arr() { return arr; }
  bool is_empty() { return 0 == last ? true : false; }
  /**
   * @brief insert element into the queue
   * @param T var = the var want to insert
   * @returns true = if empty , false = if not empty
   *
   *
   * */
  bool enqueue(T var) {
    if (last > N)
      return false;
    arr[++last] = var;
    return true;
  }
};

TEST_CASE("Queue Check", "[queue]") {
  REQUIRE(2 == 2);
  REQUIRE(1 == 1);
}

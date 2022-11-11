//#include "queue.h"
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <optional>

template <typename T, int N> class Queue {
private:
  std::array<T, N> arr;
  int first = 0;
  int last = 0;

public:
  explicit Queue() {}
  std::array<T, N> &get_arr() { return arr; } // for testing !
  int get_first() { return first; }           // for testing !!
  int get_last() { return last; }             // for testing !!
  bool is_empty() { return 0 == last - first ? true : false; }
  /**
   * @brief insert element into the queue
   * @param T var = the var want to insert
   * @returns true = if empty , false = if not empty
   * */
  bool enqueue(T var) {
    if (last >= N)
      return false;
    arr[last++] = var;
    return true;
  }
  std::optional<T> dequeue() {
    if ((first >= N) || (first >= last)) {
      return std::nullopt; /// FAILED
    }
    return arr[first++];
  }
};

TEST_CASE("Queue Check", "[queue]") {
  Queue<int, 10> queue;
  REQUIRE(queue.is_empty() == true);
  for (int i = 0; i < 10; i++) {
    queue.enqueue(i);
  }
  REQUIRE(queue.get_arr()[0] == 0);
  REQUIRE(queue.enqueue(10) == false);
  REQUIRE(queue.enqueue(10) == false);

  REQUIRE(queue.dequeue() == 0);
  REQUIRE(queue.dequeue() == 1);
}
TEST_CASE("Queue pop", "[queue]") {
  Queue<int, 10> queue;
  for (int i = 0; i < 5; i++) {
    queue.enqueue(i);
  }
  REQUIRE(queue.dequeue() == 0);
  REQUIRE(queue.dequeue() == 1);
  queue.enqueue(100);
  REQUIRE(queue.dequeue() == 2);
  REQUIRE(queue.dequeue() == 3);
  REQUIRE(queue.dequeue() == 4);
  REQUIRE(queue.dequeue() == 100);
  INFO("First is " << queue.get_first());
  INFO("Last is " << queue.get_last());
  queue.dequeue();
  INFO("First is " << queue.get_first());
  INFO("Last is " << queue.get_last());
  queue.enqueue(1000);
  REQUIRE(queue.dequeue() == 1000);
  REQUIRE(queue.dequeue() == std::nullopt);
}

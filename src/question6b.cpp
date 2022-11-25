

#include <algorithm>
#include <array>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <numeric>
#include <vector>
template <int n> std::array<int, n> init_new_state() {
  std::array<int, n> game_state;
  std::for_each(std::begin(game_state), std::end(game_state),
                [](int &element) { element = 1; });
  return game_state;
}
template <int n> bool is_game_over(std::array<int, n> game_state) {
  int sum = std::accumulate(game_state.begin(), game_state.end(), 0);
  if (sum == 0) {
    return true;
  }
  return false;
}
template <int n>
std::vector<int> possible_moves(std::array<int, n> game_state) {
  std::vector<int> all_possible_moves;
  for (int i = 0; i < n; i++) {
    if (game_state[i] == 1) {
      all_possible_moves.push_back(i);
    }
  }
  return all_possible_moves;
}
template <int n>
std::array<int, n> make_move(std::array<int, n> game_state, int move) {
  std::array<int, n> copy_state = game_state;
  if (move == n - 1) {
    copy_state[move] = 0;
    copy_state[move - 1] = 0;
    return copy_state;
  }
  if (move == 0) {
    copy_state[0] = 0;
    copy_state[1] = 0;
    return copy_state;
  }
  copy_state[move] = 0;
  copy_state[move - 1] = 0;
  copy_state[move + 1] = 0;
  return copy_state;
}
template <typename T> bool allEqual(std::vector<T> const &v) {
  return std::adjacent_find(v.begin(), v.end(), std::not_equal_to<T>()) ==
         v.end();
}
int change_turn(int a) {
  if (a == 1)
    return 0;
  if (a == 0)
    return 1;
  return -1; // errr
}
/**
 *
 *
 * @param int turn -> if 0 then its the first to play turn's else 1 is the
 * second to play
 * */
template <int n> int who_is_winning(std::array<int, n> game_state, int turn) {
  if (is_game_over<n>(game_state))
    return change_turn(turn);
  std::vector<int> all_possible_moves = possible_moves<n>(game_state);
  std::vector<int> get_all_results;

  for (int possible_move : all_possible_moves) {
    std::array<int, n> copy_state = game_state;
    copy_state = make_move<n>(game_state, possible_move);
    get_all_results.push_back(who_is_winning<n>(copy_state, change_turn(turn)));
  }
  if (get_all_results[0] == 1 && allEqual(get_all_results)) {
    return 1;
  }
  if (get_all_results[0] == 0 && allEqual(get_all_results)) {
    return 0;
  }
  return turn;
}
/**
 *
 *
 * @note when a = 0 the starting player has a winning strategy
 * when a = 1 the starting player will always lose to second player best
 * strategy */
TEST_CASE("Insert into empty tree") {
  std::array<int, 3> game_state = init_new_state<3>();
  int a = who_is_winning<3>(game_state, 0);
  REQUIRE(a == 0);
}
TEST_CASE("Second player winss") {
  std::array<int, 4> game_state = init_new_state<4>();
  int a = who_is_winning<4>(game_state, 0);
  REQUIRE(a == 1);
}
TEST_CASE("first  player winss") {
  std::array<int, 5> game_state = init_new_state<5>();
  int a = who_is_winning<5>(game_state, 0);
  REQUIRE(a == 0);
}
TEST_CASE("first asdf a  player winss") {
  std::array<int, 8> game_state = init_new_state<8>();
  int a = who_is_winning<8>(game_state, 0);
  REQUIRE(a == 1);
}

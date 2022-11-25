

#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <optional>
#include <string>
struct double_linked_list {
  int id;
  std::string name;
  double_linked_list *prev;
  double_linked_list *next;
  double_linked_list(int id, std::string name, double_linked_list *prev,
                     double_linked_list *next)
      : id(id), name(name), prev(prev), next(next) {}
};

struct HeadDLL {
  double_linked_list *head;
  double_linked_list *tail;
  HeadDLL(double_linked_list *head) : head(head), tail(head) {}
  void insert_front(double_linked_list *data) {
    if (head == nullptr) {
      head = data;
      return;
    }
    data->next = head;
    head->prev = data;
    head = data;
  }
  void insert_back(double_linked_list *data) {
    if (head == nullptr) {
      head = data;
      return;
    }
    double_linked_list *ptr = head;
    while (ptr->next != nullptr) {
      ptr = ptr->next;
    }
    data->prev = ptr->next;
    ptr->next = data;
  }
  void insert_back(int id, std::string name) {
    double_linked_list *element =
        new double_linked_list(id, name, nullptr, nullptr);
    if (head == nullptr) {
      head = element;
    }
    insert_back(element);
  }
  double_linked_list *search(int id) {
    if (head == nullptr)
      return nullptr; // The element has not been found
    if (head->id == id)
      return head;
    double_linked_list *ptr = head;
    while (ptr->next != nullptr) {
      if (ptr->id == id) {
        return ptr;
      }
      ptr = ptr->next;
    }
    return nullptr; // The element has not been found
  }
};

TEST_CASE("Testing double linked list", "[doube_link_list]") {
  double_linked_list l1 = {1, "barak", nullptr, nullptr};
  double_linked_list l2 = {2, "ariel", nullptr, nullptr};
  double_linked_list l3 = {3, "moshea", nullptr, nullptr};

  HeadDLL head(&l1);

  head.insert_back(&l2);
  head.insert_back(&l3);

  REQUIRE(head.head->id == 1);
  REQUIRE(head.head->next->id == 2);
  REQUIRE(head.head->next->next->id == 3);
}

TEST_CASE("search DDL", "[double_link_list]") {
  double_linked_list l1 = {1, "barak", nullptr, nullptr};
  double_linked_list l2 = {2, "ariel", nullptr, nullptr};
  double_linked_list l3 = {3, "moshea", nullptr, nullptr};
  HeadDLL head(&l1);
  head.insert_back(&l2);
  head.insert_back(&l3);
  REQUIRE(head.search(1)->name == "barak");
  REQUIRE(head.search(2)->name == "ariel");
  REQUIRE(head.search(4) == nullptr);
}
TEST_CASE("Search single element", "[ddl]") {
  double_linked_list l1 = {1, "barak", nullptr, nullptr};
  HeadDLL head(&l1);
  REQUIRE(head.search(1)->name == "barak");
  REQUIRE(head.search(2) == nullptr);
  REQUIRE(head.search(4) == nullptr);
}
TEST_CASE("Search single stufff asdf asf a", "[ddl]") {
  HeadDLL head(nullptr);
  double_linked_list l1 = {1, "barak", nullptr, nullptr};
  head.insert_front(&l1);
  INFO("barak ");
}
// TEST_CASE("STUFF ", "[try]") { REQUIRE(false); }

//(set 'barak '(1 2 "barak"))
//(message "Hello %s %s" "World" (nth 2 barak))

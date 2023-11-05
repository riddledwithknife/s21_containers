#include "../Containers/s21_list.h"

#include <gtest/gtest.h>

#include <list>

template <typename value_type>
bool CompareLists(s21::list<value_type> my_list,
                  std::list<value_type> std_list) {
  bool result = true;

  if (my_list.size() == std_list.size()) {
    auto my_it = my_list.begin();
    auto std_it = std_list.begin();

    for (size_t i = 0; i != my_list.size(); ++i) {
      if (*my_it != *std_it) {
        result = false;
        break;
      }
      my_it++;
      std_it++;
    }
  } else {
    result = false;
  }

  return result;
}

TEST(ListCompare, CompareLists) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  EXPECT_TRUE(CompareLists(my_list, std_list));

  std_list.push_back(6);
  EXPECT_FALSE(CompareLists(my_list, std_list));

  std_list.pop_back();
  my_list.push_front(0);
  std_list.push_front(0);
  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListConstructors, DefaultConstructor) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(my_list.size(), 0);
  EXPECT_TRUE(my_list.empty());

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListConstructors, SizeConstructor) {
  s21::list<int> my_list(1000000);
  std::list<int> std_list(1000000);
  EXPECT_EQ(my_list.size(), 1000000);

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListConstructors, SizeConstructorThrow) {
  try {
    s21::list<int> my_list(-1);
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("Out of container's limit"));
  }
}

TEST(ListConstructors, InitializerListConstructor) {
  s21::list<int> my_list = {1, 2, 3, 7, 9};
  std::list<int> std_list = {1, 2, 3, 7, 9};

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListConstructors, CopyConstructor) {
  s21::list<int> my_list = {1, 2, 3};
  s21::list<int> my_list_copy(my_list);
  std::list<int> std_list = {1, 2, 3};
  std::list<int> std_list_copy(std_list);

  EXPECT_TRUE(CompareLists(my_list_copy, std_list_copy));
}

TEST(ListConstructors, CopyConstructorEmpty) {
  s21::list<int> my_list;
  s21::list<int> my_list_copy(my_list);
  std::list<int> std_list;
  std::list<int> std_list_copy(std_list);

  EXPECT_TRUE(CompareLists(my_list_copy, std_list_copy));
}

TEST(ListConstructors, MoveConstructor) {
  s21::list<int> my_list = {1, 2, 3};
  s21::list<int> my_list_copy(my_list);
  s21::list<int> my_list_move(std::move(my_list));
  std::list<int> std_list = {1, 2, 3};
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move(std::move(std_list));

  EXPECT_TRUE(CompareLists(my_list_copy, std_list_copy));
}

TEST(ListConstructors, MoveConstructorEmpty) {
  s21::list<int> my_list;
  s21::list<int> my_list_copy(my_list);
  s21::list<int> my_list_move(std::move(my_list));
  std::list<int> std_list;
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move(std::move(std_list));

  EXPECT_TRUE(CompareLists(my_list_copy, std_list_copy));
}

TEST(ListConstructors, MoveAssignmentOperator) {
  s21::list<int> my_list = {1, 2, 3};
  s21::list<int> my_list_copy(my_list);
  s21::list<int> my_list_move = std::move(my_list);
  std::list<int> std_list = {1, 2, 3};
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move = std::move(std_list);

  EXPECT_TRUE(CompareLists(my_list_move, std_list_move));
}

TEST(ListConstructors, MoveAssignmentOperatorEmpty) {
  s21::list<int> my_list;
  s21::list<int> my_list_copy(my_list);
  s21::list<int> my_list_move = std::move(my_list);
  std::list<int> std_list;
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move = std::move(std_list);

  EXPECT_TRUE(CompareLists(my_list_move, std_list_move));
}

TEST(ListElementAccess, Front) {
  s21::list<int> my_list = {99, 2, 3, 4, 5};
  std::list<int> std_list = {99, 2, 3, 4, 5};

  EXPECT_EQ(my_list.front(), std_list.front());
}

TEST(ListElementAccess, Back) {
  s21::list<int> my_list = {1, 2, 3, 4, 99};
  std::list<int> std_list = {1, 2, 3, 4, 99};

  EXPECT_EQ(my_list.back(), std_list.back());
}

TEST(ListIterators, Begin) {
  s21::list<int> my_list = {500, 15000, 30000};
  std::list<int> std_list = {500, 15000, 30000};

  EXPECT_EQ(*my_list.begin(), *std_list.begin());
}

TEST(ListIterators, End) {
  s21::list<int> my_list = {500, 15000, 3};
  std::list<int> std_list = {500, 15000, 3};

  EXPECT_EQ(*my_list.end(), *std_list.end());
}

TEST(ListCapacity, Empty) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(my_list.empty(), std_list.empty());

  my_list.push_back(10);
  std_list.push_back(10);
  EXPECT_EQ(my_list.empty(), std_list.empty());
}

TEST(ListCapacity, Size) {
  s21::list<int> my_list = {1, 2, 3, 4, 5, 6, 7, 8};
  std::list<int> std_list = {1, 2, 3, 4, 5, 6, 7, 8};

  EXPECT_EQ(my_list.size(), std_list.size());
}

TEST(ListCapacity, SizeEmpty) {
  s21::list<int> my_list;
  std::list<int> std_list;

  EXPECT_EQ(my_list.size(), std_list.size());
}

TEST(ListCapacity, MaxSize) {
  s21::list<size_t> my_list_empty;
  std::list<size_t> std_list_empty;

  EXPECT_EQ(my_list_empty.max_size(), std_list_empty.max_size());
}

TEST(ListModifiers, Clear) {
  s21::list<int> my_list = {1, 2, 3, 4};
  my_list.clear();
  std::list<int> std_list = {1, 2, 5, 4, 3};
  std_list.clear();

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListModifiers, ClearEmpty) {
  s21::list<int> my_list;
  my_list.clear();
  std::list<int> std_list;
  std_list.clear();

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListModifiers, InsertBegin) {
  s21::list<int> my_list = {1, 9999, 20000};
  my_list.insert(my_list.begin(), 5);

  std::list<int> std_list = {1, 9999, 20000};
  std_list.insert(std_list.begin(), 5);

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListModifiers, InsertMiddle) {
  s21::list<int> my_list = {1, 9999, 20000};
  my_list.insert(my_list.begin()++, 5);

  std::list<int> std_list = {1, 9999, 20000};
  std_list.insert(std_list.begin().operator++(), 5);

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListModifiers, InsertEnd) {
  s21::list<int> my_list = {1, 9999, 20000};
  my_list.insert(my_list.end(), 5);

  std::list<int> std_list = {1, 9999, 20000};
  std_list.insert(std_list.end(), 5);

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListModifiers, EraseBegin) {
  s21::list<int> my_list = {1, 9999, 20000};
  my_list.erase(my_list.begin());

  std::list<int> std_list = {1, 9999, 20000};
  std_list.erase(std_list.begin());

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListModifiers, EraseMiddle) {
  s21::list<int> my_list = {1, 9999, 20000};
  my_list.erase(my_list.begin()++);

  std::list<int> std_list = {1, 9999, 20000};
  std_list.erase(std_list.begin().operator++());

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListModifiers, EraseThrow) {
  s21::list<int> my_list = {1, 9999, 20000};

  EXPECT_THROW(my_list.erase(my_list.end()), std::invalid_argument);
}

TEST(ListModifiers, PushBack) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  my_list.push_back(6);
  std::list<int> std_list = {1, 2, 3, 4, 5};
  std_list.push_back(6);

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListModifiers, PopBack) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  my_list.pop_back();
  std::list<int> std_list = {1, 2, 3, 4, 5};
  std_list.pop_back();

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListModifiers, PushFront) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  my_list.push_front(0);
  std::list<int> std_list = {1, 2, 3, 4, 5};
  std_list.push_front(0);

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListModifiers, PopFront) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  my_list.pop_front();
  std::list<int> std_list = {1, 2, 3, 4, 5};
  std_list.pop_front();

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListModifiers, Swap) {
  s21::list<int> my_list1 = {1, 2, 3, 4, 5};
  s21::list<int> my_list2 = {6, 7, 8, 9, 10, 11};
  my_list1.swap(my_list2);

  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  std::list<int> std_list2 = {6, 7, 8, 9, 10, 11};
  std_list1.swap(std_list2);

  EXPECT_TRUE(CompareLists(my_list1, std_list1));
  EXPECT_TRUE(CompareLists(my_list2, std_list2));
}

TEST(ListOperations, MergeEq) {
  s21::list<int> my_list1 = {1, 9999, 20000};
  s21::list<int> my_list2 = {500, 15000, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1 = {1, 9999, 20000};
  std::list<int> std_list2 = {500, 15000, 30000};
  std_list1.merge(std_list2);

  EXPECT_TRUE(CompareLists(my_list1, std_list1));
}

TEST(ListOperations, MergeSecondLess) {
  s21::list<int> my_list1 = {1, 9999, 20000};
  s21::list<int> my_list2 = {15000, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1 = {1, 9999, 20000};
  std::list<int> std_list2 = {15000, 30000};
  std_list1.merge(std_list2);

  EXPECT_TRUE(CompareLists(my_list1, std_list1));
}

TEST(ListOperations, MergeFirstLess) {
  s21::list<int> my_list1 = {1, 20000};
  s21::list<int> my_list2 = {15000, 154, 124};
  my_list1.merge(my_list2);

  std::list<int> std_list1 = {1, 20000};
  std::list<int> std_list2 = {15000, 154, 124};
  std_list1.merge(std_list2);

  EXPECT_TRUE(CompareLists(my_list1, std_list1));
}

TEST(ListOperations, SpliceEq) {
  s21::list<int> my_list1 = {1, 9999, 20000};
  s21::list<int> my_list2 = {500, 15000, 30000};

  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1 = {1, 9999, 20000};
  std::list<int> std_list2 = {500, 15000, 30000};
  std_list1.splice(std_list1.begin(), std_list2);

  EXPECT_TRUE(CompareLists(my_list1, std_list1));
}

TEST(ListOperations, SpliceFirstEmpty) {
  s21::list<int> my_list1;
  s21::list<int> my_list2 = {500, 15000, 30000};
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2 = {500, 15000, 30000};
  std_list1.splice(std_list1.begin(), std_list2);

  EXPECT_TRUE(CompareLists(my_list1, std_list1));
}

TEST(ListOperations, SpliceSecondEmpty) {
  s21::list<int> my_list1 = {1, 9999, 20000};
  s21::list<int> my_list2;
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1 = {1, 9999, 20000};
  std::list<int> std_list2;
  std_list1.splice(std_list1.begin(), std_list2);

  EXPECT_TRUE(CompareLists(my_list1, std_list1));
}

TEST(ListOperations, SpliceBothEmpty) {
  s21::list<int> my_list1;
  s21::list<int> my_list2;
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2;
  std_list1.splice(std_list1.begin(), std_list2);

  EXPECT_TRUE(CompareLists(my_list1, std_list1));
}

TEST(ListOperations, ReverseInitList) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  my_list.reverse();
  std_list.reverse();

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListOperations, ReverseSize) {
  s21::list<int> my_list(4);
  std::list<int> std_list(4);
  my_list.reverse();
  std_list.reverse();

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListOperations, ReverseEmpty) {
  s21::list<int> my_list;
  std::list<int> std_list;
  my_list.reverse();
  std_list.reverse();

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListOperations, ReverseCheckOne) {
  s21::list<int> my_list = {1};
  std::list<int> std_list = {1};
  my_list.reverse();
  std_list.reverse();

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListOperations, Unique) {
  s21::list<int> my_list = {90, 10, 3, 40, 30, 20, 10, 10, 90, 90, 90};
  std::list<int> std_list = {90, 10, 3, 40, 30, 20, 10, 10, 90, 90, 90};
  my_list.unique();
  std_list.unique();

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListOperations, Sort) {
  s21::list<int> my_list = {1, 2, 3, 2, 1};
  std::list<int> std_list = {1, 2, 3, 2, 1};
  my_list.sort();
  std_list.sort();

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListOperations, SortZeroSize) {
  s21::list<int> my_list = {1};
  std::list<int> std_list = {1};
  my_list.sort();
  std_list.sort();

  EXPECT_TRUE(CompareLists(my_list, std_list));
}
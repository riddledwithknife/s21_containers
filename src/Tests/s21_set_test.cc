#include "../Containers/s21_set.h"

#include <gtest/gtest.h>

#include <set>

TEST(SetConstructors, DefaultConstructor) {
  s21::set<int> s21_set;
  std::set<int> std_set;

  EXPECT_EQ(s21_set.size(), 0);
  EXPECT_TRUE(s21_set.empty());

  EXPECT_EQ(std_set.size(), 0);
  EXPECT_TRUE(std_set.empty());
}

TEST(SetConstructors, InitializerListConstructor) {
  s21::set<int> s21_set = {1, 2, 3};
  std::set<int> std_set = {1, 2, 3};

  EXPECT_EQ(s21_set.size(), 3);
  EXPECT_FALSE(s21_set.empty());
  EXPECT_EQ(*(s21_set.find(1)), 1);
  EXPECT_EQ(*(s21_set.find(2)), 2);
  EXPECT_EQ(*(s21_set.find(3)), 3);

  EXPECT_EQ(std_set.size(), 3);
  EXPECT_FALSE(std_set.empty());
  EXPECT_EQ(*(std_set.find(1)), 1);
  EXPECT_EQ(*(std_set.find(2)), 2);
  EXPECT_EQ(*(std_set.find(3)), 3);
}

TEST(SetConstructors, CopyConstructor) {
  s21::set<int> s21_set = {1, 2, 3};
  s21::set<int> s21_setcopy(s21_set);

  std::set<int> std_set = {1, 2, 3};
  std::set<int> std_setcopy(std_set);

  EXPECT_EQ(s21_setcopy.size(), 3);
  EXPECT_FALSE(s21_setcopy.empty());
  EXPECT_EQ(*(s21_setcopy.find(1)), 1);
  EXPECT_EQ(*(s21_setcopy.find(2)), 2);
  EXPECT_EQ(*(s21_setcopy.find(3)), 3);

  EXPECT_EQ(std_setcopy.size(), 3);
  EXPECT_FALSE(std_setcopy.empty());
  EXPECT_EQ(*(std_setcopy.find(1)), 1);
  EXPECT_EQ(*(std_setcopy.find(2)), 2);
  EXPECT_EQ(*(std_setcopy.find(3)), 3);
}

TEST(SetConstructors, MoveConstructor) {
  s21::set<int> s21_set = {1, 2, 3};
  s21::set<int> s21_setmove(std::move(s21_set));

  std::set<int> std_set = {1, 2, 3};
  std::set<int> std_setmove(std::move(std_set));

  EXPECT_EQ(s21_setmove.size(), 3);
  EXPECT_TRUE(s21_set.empty());
  EXPECT_EQ(*(s21_setmove.find(1)), 1);
  EXPECT_EQ(*(s21_setmove.find(3)), 3);

  EXPECT_EQ(std_setmove.size(), 3);
  EXPECT_TRUE(std_set.empty());
  EXPECT_EQ(*(std_setmove.find(1)), 1);
  EXPECT_EQ(*(std_setmove.find(3)), 3);
}

TEST(SetConstructors, MoveAssignmentOperator) {
  s21::set<int> s21_set = {1, 2, 3};
  s21::set<int> s21_setmove = std::move(s21_set);

  std::set<int> std_set = {1, 2, 3};
  std::set<int> std_setmove = std::move(std_set);

  EXPECT_EQ(s21_setmove.size(), 3);
  EXPECT_TRUE(s21_set.empty());
  EXPECT_EQ(*(s21_setmove.find(1)), 1);
  EXPECT_EQ(*(s21_setmove.find(3)), 3);

  EXPECT_EQ(std_setmove.size(), 3);
  EXPECT_TRUE(std_set.empty());
  EXPECT_EQ(*(std_setmove.find(1)), 1);
  EXPECT_EQ(*(std_setmove.find(3)), 3);
}

TEST(SetIterators, Begin) {
  s21::set<int> s21_set = {1, 2, 3};

  std::set<int> std_set = {1, 2, 3};

  EXPECT_EQ(*s21_set.begin(), 1);

  EXPECT_EQ(*std_set.begin(), 1);
}

TEST(SetIterators, End) {
  s21::set<int> s21_set = {1, 1, 1};

  std::set<int> std_set = {1, 1, 1};

  for (auto it = s21_set.begin(); it != s21_set.end(); ++it) {
    auto a = *it;
    EXPECT_EQ(a, 1);
  }

  for (auto it = std_set.begin(); it != std_set.end(); ++it) {
    auto a = *it;
    EXPECT_EQ(a, 1);
  }
}

TEST(SetCapacity, Empty) {
  s21::set<int> s21_set = {1, 2, 3};

  std::set<int> std_set = {1, 2, 3};

  EXPECT_FALSE(s21_set.empty());
  EXPECT_FALSE(std_set.empty());
}

TEST(SetCapacity, Size) {
  s21::set<int> s21_set = {1, 2, 3};

  std::set<int> std_set = {1, 2, 3};

  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(SetModifiers, Clear) {
  s21::set<int> s21_set = {1, 2, 3};

  std::set<int> std_set = {1, 2, 3};

  s21_set.clear();
  std_set.clear();

  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(SetModifiers, Insert) {
  s21::set<int> s21_set = {1, 2, 3};

  std::set<int> std_set = {1, 2, 3};

  s21_set.insert(4);
  std_set.insert(4);

  EXPECT_EQ(*(s21_set.find(4)), 4);
  EXPECT_EQ(*(std_set.find(4)), 4);
}

TEST(SetModifiers, InsertExistedKey) {
  s21::set<int> s21_set = {1, 2, 3};

  std::set<int> std_set = {1, 2, 3};

  s21_set.insert(3);
  std_set.insert(3);

  EXPECT_EQ(*(s21_set.find(3)), 3);
  EXPECT_EQ(*(std_set.find(3)), 3);
}

TEST(SetModifiers, Erase) {
  s21::set<int> s21_set = {1, 2, 3};

  std::set<int> std_set = {1, 2, 3};

  s21_set.erase(s21_set.begin());
  std_set.erase(1);

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(*(s21_set.find(2)), 2);
  EXPECT_EQ(*(std_set.find(2)), 2);
}

TEST(SetModifiers, EraseRoot) {
  s21::set<int> s21_set = {1, 2, 3};

  std::set<int> std_set = {1, 2, 3};

  s21_set.erase(s21_set.begin()++);
  std_set.erase(2);

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(*(s21_set.find(1)), 1);
  EXPECT_EQ(*(std_set.find(1)), 1);

  EXPECT_EQ(*(s21_set.find(3)), 3);
  EXPECT_EQ(*(std_set.find(3)), 3);
}

TEST(SetModifiers, Swap) {
  s21::set<int> s21_set = {1, 2, 3};
  s21::set<int> s21_setswap = {4, 5, 6};

  std::set<int> std_set = {1, 2, 3};
  std::set<int> std_setswap = {4, 5, 6};

  s21_set.swap(s21_setswap);
  std_set.swap(std_setswap);

  EXPECT_EQ(*s21_setswap.find(3), 3);
  EXPECT_EQ(*s21_set.find(6), 6);

  EXPECT_EQ(*std_setswap.find(3), 3);
  EXPECT_EQ(*std_set.find(6), 6);
}

TEST(SetModifiers, Merge) {
  s21::set<int> s21_set = {1, 2, 3};
  s21::set<int> s21_setmerge = {4, 5, 6};

  std::set<int> std_set = {1, 2, 3};
  std::set<int> std_setmerge = {4, 5, 6};

  s21_set.merge(s21_setmerge);
  std_set.merge(std_setmerge);

  EXPECT_EQ(*s21_set.find(6), 6);
  EXPECT_EQ(*std_set.find(6), 6);

  EXPECT_TRUE(s21_setmerge.empty());
  EXPECT_TRUE(std_setmerge.empty());
}

TEST(SetLookup, Find) {
  s21::set<int> s21_set = {1, 2, 3};

  std::set<int> std_set = {1, 2, 3};

  EXPECT_EQ(*s21_set.find(3), 3);
  EXPECT_EQ(*std_set.find(3), 3);
}

TEST(SetLookup, Contains) {
  s21::set<int> s21_set = {1, 2, 3};

  EXPECT_TRUE(s21_set.contains(3));
}
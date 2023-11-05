#include "../Containers/s21_map.h"

#include <gtest/gtest.h>

#include <map>

TEST(MapConstructors, DefaultConstructor) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  EXPECT_EQ(s21_map.size(), 0);
  EXPECT_TRUE(s21_map.empty());

  EXPECT_EQ(std_map.size(), 0);
  EXPECT_TRUE(std_map.empty());
}

TEST(MapConstructors, InitializerListConstructor) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};
  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_EQ(s21_map.size(), 3);
  EXPECT_FALSE(s21_map.empty());
  EXPECT_EQ(s21_map.at(1), "one");
  EXPECT_EQ(s21_map.at(2), "two");
  EXPECT_EQ(s21_map.at(3), "three");

  EXPECT_EQ(std_map.size(), 3);
  EXPECT_FALSE(std_map.empty());
  EXPECT_EQ(std_map.at(1), "one");
  EXPECT_EQ(std_map.at(2), "two");
  EXPECT_EQ(std_map.at(3), "three");
}

TEST(MapConstructors, CopyConstructor) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> copy_s21(s21_map);

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};
  std::map<int, std::string> copy_std(std_map);

  EXPECT_EQ(copy_s21.size(), 3);
  EXPECT_FALSE(copy_s21.empty());
  EXPECT_EQ(copy_s21.at(1), "one");
  EXPECT_EQ(copy_s21.at(3), "three");

  EXPECT_EQ(copy_std.size(), 3);
  EXPECT_FALSE(copy_std.empty());
  EXPECT_EQ(copy_std.at(1), "one");
  EXPECT_EQ(copy_std.at(3), "three");
}

TEST(MapConstructors, MoveConstructor) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> move_s21(std::move(s21_map));

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};
  std::map<int, std::string> move_std(std::move(std_map));

  EXPECT_EQ(move_s21.size(), 3);
  EXPECT_TRUE(s21_map.empty());
  EXPECT_EQ(move_s21.at(1), "one");
  EXPECT_EQ(move_s21.at(3), "three");

  EXPECT_EQ(move_std.size(), 3);
  EXPECT_TRUE(std_map.empty());
  EXPECT_EQ(move_std.at(1), "one");
  EXPECT_EQ(move_std.at(3), "three");
}

TEST(MapConstructors, MoveAssignmentOperator) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> move_s21 = std::move(s21_map);

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};
  std::map<int, std::string> move_std = std::move(std_map);

  EXPECT_EQ(move_s21.size(), 3);
  EXPECT_TRUE(s21_map.empty());
  EXPECT_EQ(move_s21.at(1), "one");
  EXPECT_EQ(move_s21.at(3), "three");

  EXPECT_EQ(move_std.size(), 3);
  EXPECT_TRUE(std_map.empty());
  EXPECT_EQ(move_std.at(1), "one");
  EXPECT_EQ(move_std.at(3), "three");
}

TEST(MapElementAccess, At) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_EQ(s21_map.at(1), "one");
  EXPECT_EQ(s21_map.at(2), "two");
  EXPECT_EQ(s21_map.at(3), "three");

  EXPECT_EQ(std_map.at(1), "one");
  EXPECT_EQ(std_map.at(2), "two");
  EXPECT_EQ(std_map.at(3), "three");
}

TEST(MapElementAccess, Brackets) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_EQ(s21_map[1], "one");
  EXPECT_EQ(s21_map[2], "two");
  EXPECT_EQ(s21_map[3], "three");

  EXPECT_EQ(std_map[1], "one");
  EXPECT_EQ(std_map[2], "two");
  EXPECT_EQ(std_map[3], "three");
}

TEST(MapIterators, Begin) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_EQ((*s21_map.begin()).second, "one");

  EXPECT_EQ((*std_map.begin()).second, "one");
}

TEST(MapIterators, End) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "one"}, {3, "one"}};

  std::map<int, std::string> std_map = {{1, "one"}, {2, "one"}, {3, "one"}};

  for (auto it = s21_map.begin(); it != s21_map.end(); ++it) {
    auto a = (*it).second;
    EXPECT_EQ(a, "one");
  }

  for (auto it = std_map.begin(); it != std_map.end(); ++it) {
    auto a = (*it).second;
    EXPECT_EQ(a, "one");
  }
}

TEST(MapCapacity, Empty) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_FALSE(s21_map.empty());
  EXPECT_FALSE(std_map.empty());
}

TEST(MapCapacity, Size) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(MapCapacity, MaxSize) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_EQ(s21_map.max_size(), std_map.max_size());
}

TEST(MapModifiers, Clear) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  s21_map.clear();
  std_map.clear();

  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(MapModifiers, InsertPair) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  s21_map.insert(4, "four");
  std_map.insert({4, "four"});

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map[4], "four");
  EXPECT_EQ(std_map[4], "four");
}

TEST(MapModifiers, InsertKeyValue) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  auto it1 = s21_map.insert({4, "four"});
  auto it2 = std_map.insert({4, "four"});

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ((*(it1.first)).second, "four");
  EXPECT_EQ((*(it2.first)).second, "four");
}

TEST(MapModifiers, InsertExistedKey) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  auto it1 = s21_map.insert({3, "four"});
  auto it2 = std_map.insert({3, "four"});

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ((*(it1.first)).second, "three");
  EXPECT_EQ((*(it2.first)).second, "three");
}

TEST(MapModifiers, InsertOrAssn) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  s21_map.insert_or_assign(3, "four");
  std_map.insert_or_assign(3, "four");

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map[3], "four");
  EXPECT_EQ(std_map[3], "four");
}

TEST(MapModifiers, InsertOrAssnNew) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  s21_map.insert_or_assign(4, "four");
  std_map.insert_or_assign(4, "four");

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map[4], "four");
  EXPECT_EQ(std_map[4], "four");
}

TEST(MapModifiers, Erase) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  s21_map.erase(s21_map.begin());
  std_map.erase(1);

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map[2], "two");
  EXPECT_EQ(s21_map[3], "three");

  EXPECT_EQ(s21_map[2], "two");
  EXPECT_EQ(s21_map[3], "three");
}

TEST(MapModifiers, EraseRoot) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  s21_map.erase(++s21_map.begin());
  std_map.erase(2);

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map[1], "one");
  EXPECT_EQ(s21_map[3], "three");

  EXPECT_EQ(s21_map[1], "one");
  EXPECT_EQ(s21_map[3], "three");
}

TEST(MapModifiers, Swap) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  s21::map<int, std::string> s21_mapswap = {
      {4, "four"}, {5, "five"}, {6, "six"}};

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  std::map<int, std::string> std_mapswap = {
      {4, "four"}, {5, "five"}, {6, "six"}};

  s21_map.swap(s21_mapswap);
  std_map.swap(std_mapswap);

  EXPECT_EQ(s21_mapswap[3], "three");
  EXPECT_EQ(s21_map[6], "six");

  EXPECT_EQ(std_mapswap[3], "three");
  EXPECT_EQ(std_map[6], "six");
}

TEST(MapModifiers, Merge) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  s21::map<int, std::string> s21_mapmerge = {
      {4, "four"}, {5, "five"}, {6, "six"}};

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  std::map<int, std::string> std_mapmerge = {
      {4, "four"}, {5, "five"}, {6, "six"}};

  s21_map.merge(s21_mapmerge);
  std_map.merge(std_mapmerge);

  EXPECT_EQ(s21_map[6], "six");
  EXPECT_EQ(std_map[6], "six");

  EXPECT_TRUE(s21_mapmerge.empty());
}

TEST(MapLookup, Contains) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_TRUE(s21_map.contains(3));
}
#include "../Containers/s21_vector.h"

#include <gtest/gtest.h>

#include <vector>

TEST(VectorConstructors, DefaultConstructor) {
  s21::vector<int> s21_vector;
  std::vector<int> std_vector;

  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(VectorConstructors, SizeConstructor) {
  s21::vector<double> s21_vector(10);
  std::vector<double> std_vector(10);

  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
}

TEST(VectorConstructors, InitializerListConstructor) {
  s21::vector<int> s21_vector = {3, 3, 1, 2};
  std::vector<int> std_vector = {3, 3, 1, 2};

  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.front(), std_vector.front());
  EXPECT_EQ(s21_vector.back(), std_vector.back());
}

TEST(VectorConstructors, CopyConstructor) {
  s21::vector<char> s21_vector_1 = {'q', 'w', 'e', 'r', 't',
                                    'y', 'u', 'i', 'o', 'p'};
  std::vector<char> std_vector_1 = {'q', 'w', 'e', 'r', 't',
                                    'y', 'u', 'i', 'o', 'p'};

  s21::vector<char> s21_vector_2 = s21_vector_1;
  std::vector<char> std_vector_2 = std_vector_1;

  EXPECT_EQ(s21_vector_1.size(), s21_vector_2.size());
  EXPECT_EQ(std_vector_1.size(), std_vector_2.size());

  auto it1 = s21_vector_1.begin();
  auto it2 = s21_vector_2.begin();

  while (it1 != s21_vector_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(VectorConstructors, MoveConstructor) {
  s21::vector<char> s21_vector_1 = {'a', 's', 'd', 'f'};
  std::vector<char> std_vector_1 = {'a', 's', 'd', 'f'};
  s21::vector<char> s21_vector_2(std::move(s21_vector_1));
  std::vector<char> std_vector_2(std::move(std_vector_1));

  EXPECT_EQ(s21_vector_1.empty(), std_vector_1.empty());
  EXPECT_EQ(s21_vector_2.size(), std_vector_2.size());
  EXPECT_EQ(s21_vector_1.size(), std_vector_1.size());

  auto it1 = s21_vector_2.begin();
  auto it2 = std_vector_2.begin();

  while (it1 != s21_vector_2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(VectorDestructor, Destructor) {
  s21::vector<int> s21_v = {1, 2, 3, 4, 5};
  s21_v.~vector();

  EXPECT_EQ(0, s21_v.size());
  EXPECT_EQ(0, s21_v.capacity());
  EXPECT_EQ(nullptr, s21_v.data());
}

TEST(VectorConstructors, MoveAssignmentOperator) {
  s21::vector<char> s21_vector_1 = {'a', 's', 'd', 'f'};
  std::vector<char> std_vector_1 = {'a', 's', 'd', 'f'};
  s21::vector<char> s21_vector_2 = std::move(s21_vector_1);
  std::vector<char> std_vector_2 = std::move(std_vector_1);

  EXPECT_EQ(s21_vector_1.empty(), std_vector_1.empty());
  EXPECT_EQ(s21_vector_2.size(), std_vector_2.size());
  EXPECT_EQ(s21_vector_1.size(), std_vector_1.size());

  auto it1 = s21_vector_2.begin();
  auto it2 = std_vector_2.begin();

  while (it1 != s21_vector_2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(VectorElementAccess, At) {
  s21::vector<int> s21_v = {1, 2, 3, 4, 5};
  std::vector<int> std_v = {1, 2, 3, 4, 5};

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
  EXPECT_EQ(s21_v.at(4), std_v.at(4));
}

TEST(VectorElementAccess, AtThrow) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  EXPECT_ANY_THROW(s21_v.at(1));
  EXPECT_ANY_THROW(std_v.at(1));
}

TEST(VectorElementAccess, Brackets) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};
  EXPECT_EQ(s21_v[0], std_v[0]);
  EXPECT_EQ(s21_v[1], std_v[1]);
  EXPECT_EQ(s21_v[2], std_v[2]);
}

TEST(VectorElementAccess, Front) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};
  EXPECT_EQ(s21_v.front(), std_v.front());
}

TEST(VectorElementAccess, Back) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};
  EXPECT_EQ(s21_v.back(), std_v.back());
}

TEST(VectorElementAccess, Data) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};

  EXPECT_EQ(*s21_v.data(), *std_v.data());
}

TEST(VectorIterators, Begin) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};

  EXPECT_EQ(*s21_v.begin(), *std_v.begin());
}

TEST(VectorIterators, End) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};

  EXPECT_EQ(*s21_v.end(), *std_v.end());
}

TEST(VectorCapacity, Empty) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};

  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorCapacity, Size) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(VectorCapacity, MaxSize) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};

  EXPECT_EQ(s21_v.max_size(), std_v.max_size());
}

TEST(VectorCapacity, Reserve) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  s21_v.reserve(2);
  std_v.reserve(2);

  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorCapacity, Capacity) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};

  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorCapacity, ShrinkToFit) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};
  s21_v.reserve(10);
  std_v.reserve(10);
  s21_v.shrink_to_fit();
  std_v.shrink_to_fit();

  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorModifiers, Clear) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};
  s21_v.clear();
  std_v.clear();

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(VectorModifiers, Insert) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};
  s21_v.insert(s21_v.begin()++, 5);
  std_v.insert(std_v.begin()++, 5);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
}

TEST(VectorModifiers, Erase) {
  s21::vector<int> s21_v = {1, 2, 3, 4};
  std::vector<int> std_v = {1, 2, 3, 4};

  s21_v.erase(s21_v.begin()++);
  std_v.erase(std_v.begin()++);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
}

TEST(VectorModifiers, EraseThrow) {
  s21::vector<int> s21_v = {1, 2, 3, 4};

  EXPECT_ANY_THROW(s21_v.erase(s21_v.end()++));
}

TEST(VectorModifiers, PushBackEmpty) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  s21_v.push_back(2);
  s21_v.push_back(3);
  s21_v.push_back(4);
  s21_v.push_back(5);

  std_v.push_back(2);
  std_v.push_back(3);
  std_v.push_back(4);
  std_v.push_back(5);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
}

TEST(VectorModifiers, PushBackFull) {
  s21::vector<int> s21_v = {1, 2};
  std::vector<int> std_v = {1, 2};

  s21_v.push_back(2);
  s21_v.push_back(3);
  s21_v.push_back(4);
  s21_v.push_back(5);

  std_v.push_back(2);
  std_v.push_back(3);
  std_v.push_back(4);
  std_v.push_back(5);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
  EXPECT_EQ(s21_v.at(4), std_v.at(4));
  EXPECT_EQ(s21_v.at(5), std_v.at(5));
}

TEST(VectorModifiers, PopBack) {
  s21::vector<int> s21_v = {1, 2};

  s21_v.pop_back();
  s21_v.pop_back();
  s21_v.pop_back();
  s21_v.pop_back();

  EXPECT_EQ(s21_v.size(), 0);
  EXPECT_EQ(s21_v.capacity(), 2);
}

TEST(VectorModifiers, SwapEmpty) {
  s21::vector<int> s21_v;
  s21::vector<int> s21_v_copy;

  std::vector<int> std_v;
  std::vector<int> std_v_copy;

  s21_v_copy.swap(s21_v);
  std_v_copy.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v_copy.size(), std_v_copy.size());
  EXPECT_EQ(s21_v_copy.capacity(), std_v_copy.capacity());
}

TEST(VectorModifiers, SwapFull) {
  s21::vector<int> s21_v = {1, 2, 3, 4};
  s21::vector<int> s21_v_copy;

  std::vector<int> std_v = {1, 2, 3, 4};
  std::vector<int> std_v_copy;

  s21_v_copy.swap(s21_v);
  std_v_copy.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v_copy.size(), std_v_copy.size());
  EXPECT_EQ(s21_v_copy.capacity(), std_v_copy.capacity());
}
// Copyright 2021 ak-kuznetsov <a.kuznetsov2701@mail.ru>

#include <gtest/gtest.h>
#include <Stack_1.hpp>
#include <Stack_2.hpp>
TEST(Example, EmptyTest) { EXPECT_TRUE(true); }

TEST(Stack_1, NoCopiable_Movable) {
  EXPECT_TRUE(std::is_move_constructible<Stack_1<int>>::value); /* Проверка на наличие конструктора перемещения */
  EXPECT_TRUE(std::is_move_assignable<Stack_1<int>>::value); /* Проверка на наличие оператора перемещения */
  EXPECT_FALSE(std::is_copy_constructible<Stack_1<int>>::value); /* Проверка на наличие конструктора копирования */
  EXPECT_FALSE(std::is_copy_assignable<Stack_1<int>>::value); /* Проверка на наличие оператора присваивания */
}

TEST(Stack_1, Rvalue_test) {
  Stack_1<double> a;
  a.push(3.14);
  EXPECT_EQ(a.head(), 3.14);
  double tmp = 41.3;
  a.push(std::move(tmp));
  EXPECT_EQ(a.head(), 41.3);
}

TEST(Stack_1, Lvalue_test){
  Stack_1<std::string> numbers;
  std::string one = "1";
  numbers.push(one);
  EXPECT_EQ(numbers.head(), "1");
  std::string two = "2";
  std::string three = "3";
  numbers.push(two);
  numbers.push(three);
  EXPECT_EQ(numbers.head(), "3");
}

TEST(Stack_1, Pop) {
  Stack_1<int> b;
  b.push(0);
  b.push(1);
  b.push(2);
  b.pop();
  EXPECT_EQ(b.head(), 1);
  b.pop();
  EXPECT_EQ(b.head(), 0);
  b.pop();
}

TEST(Stack_1, Head) {
  Stack_1<int> b;
  b.push(0);
  EXPECT_EQ(b.head(), 0);
  b.push(1);
  EXPECT_EQ(b.head(), 1);
  b.push(2);
  EXPECT_EQ(b.head(), 2);
}

template<typename T>
class Cars {
 public:
  Cars(T t1, T t2, T t3) : toyota{t1}, mazda{t2}, nissan{t3} {}
  Cars(const Cars& Weather_today) = delete;
  Cars(Cars&& Weather_today) = default;
  auto operator=(const Cars& Weather_today) = delete;
  auto operator=(Cars&& Weather_today) -> Cars& = default;
  T toyota;
  T mazda;
  T nissan;
};

TEST(Stack_2, Push) {
  Stack_2<Cars<int>> amount;
  Cars<int> test1(1, 2, 3);
  Cars<int> test2(4, 5, 6);
  Cars<int> test3(7, 8, 9);
  amount.push(std::move(test1));
  amount.push(std::move(test2));
  amount.push(std::move(test3));
  EXPECT_EQ(amount.head().toyota, 7);
  EXPECT_EQ(amount.head().mazda, 8);
  EXPECT_EQ(amount.head().nissan, 9);
}

TEST(Stack_2, Pop) {
  Stack_2<Cars<int>> amount;
  Cars<int> test1(1, 2, 3);
  Cars<int> test2(4, 5, 6);
  Cars<int> test3(7, 8, 9);
  amount.push(std::move(test1));
  amount.push(std::move(test2));
  amount.push(std::move(test3));
  EXPECT_EQ(amount.head().toyota, 7);
  EXPECT_EQ(amount.head().mazda, 8);
  EXPECT_EQ(amount.head().nissan, 9);
  amount.pop();
  EXPECT_EQ(amount.head().toyota, 4);
  EXPECT_EQ(amount.head().mazda, 5);
  EXPECT_EQ(amount.head().nissan, 6);
}

TEST(Stack_2, Push_emplace) {
  Stack_2<Cars<int>> amount;
  amount.push_emplace(1, 2, 3);
  amount.push_emplace(4, 5, 6);
  amount.push_emplace(7, 8, 9);
  EXPECT_EQ(amount.head().toyota, 7);
  EXPECT_EQ(amount.head().mazda, 8);
  EXPECT_EQ(amount.head().nissan, 9);
  amount.pop();
  EXPECT_EQ(amount.head().toyota, 4);
  EXPECT_EQ(amount.head().mazda, 5);
  EXPECT_EQ(amount.head().nissan, 6);
}

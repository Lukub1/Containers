#include <gtest/gtest.h>

#include <list>
#include <map>
#include <queue>
#include <stack>

#include "s21_containers.h"

TEST(list, default_constructor) {
  s21::list<int> mylist;
  std::list<int> liblist;
  ASSERT_EQ(mylist.empty(), liblist.empty());
  ASSERT_EQ(liblist.max_size() - mylist.max_size(), 42);
}

TEST(list, size_constructor) {
  std::list<int> mylist(5);
  ASSERT_EQ(mylist.size(), 5);
}

TEST(list, init_constructor) {
  s21::list<int> l1{1, 2, 3};
  ASSERT_EQ(l1.size(), 3);
  ASSERT_EQ(l1.front(), 1);
  ASSERT_EQ(l1.back(), 3);
}

TEST(list, push_back_constructor) {
  s21::list<std::string> mylist;
  mylist.push_back("apple");
  mylist.push_back("banana");
  mylist.push_back("orange");
  ASSERT_EQ(mylist.front(), "apple");
  ASSERT_EQ(mylist.back(), "orange");
}

TEST(list, copy_constructor) {
  s21::list<int> mylist{3, 2, 1};
  s21::list<int> mylistcopy(mylist);
  ASSERT_EQ(mylist.front(), mylistcopy.front());

  mylist.push_front(4);
  ASSERT_EQ(mylist.front(), 4);
  ASSERT_EQ(mylistcopy.front(), 3);
}

TEST(list, move_constructor) {
  s21::list<int> mylist{1, 2, 3};
  s21::list<int> mylistcopy(std::move(mylist));
  ASSERT_TRUE(mylist.empty());
  ASSERT_FALSE(mylistcopy.empty());
}

TEST(list, move_operator_constructor) {
  s21::list<int> mylist{1, 2, 3};
  s21::list<int> mylistcopy;
  mylistcopy = std::move(mylist);
  ASSERT_TRUE(mylist.empty());
  ASSERT_FALSE(mylistcopy.empty());
}
TEST(list, push_int) {
  s21::list<int> mylist;
  mylist.push_front(1);
  mylist.push_back(5);
  s21::list<int> stdlist;
  stdlist.push_front(1);
  stdlist.push_back(5);
  auto myiter = mylist.begin();
  auto stditer = stdlist.begin();
  while (myiter != mylist.end() && stditer != stdlist.end()) {
    ASSERT_EQ(*myiter, *stditer);
    ++myiter;
    ++stditer;
  }
}

TEST(list, pop_front_multiple) {
  s21::list<int> mylist{1, 2, 3};
  std::list<int> stdlist{1, 2, 3};
  while (!mylist.empty()) {
    ASSERT_EQ(mylist.front(), stdlist.front());
    mylist.pop_front();
    stdlist.pop_front();
  }
  ASSERT_EQ(mylist.empty(), stdlist.empty());
}

TEST(list, size_swap) {
  s21::list<int> mylist{1, 2, 3, 4, 5};
  s21::list<int> mylist2{1, 2};
  ASSERT_EQ(mylist.size(), 5);
  ASSERT_EQ(mylist2.size(), 2);
  mylist.swap(mylist2);
  ASSERT_EQ(mylist.size(), 2);
  ASSERT_EQ(mylist2.size(), 5);
}

TEST(list, insert_int) {
  s21::list<int> mylist{1, 2};
  std::list<int> stdlist{1, 2};
  s21::list<int>::ListIterator s21it;
  s21it = mylist.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  mylist.insert(s21it, 5);
  stdlist.insert(stdit, 5);
  ASSERT_EQ(mylist.front(), stdlist.front());
  ++s21it;
  ++stdit;
  mylist.insert(s21it, 7);
  stdlist.insert(stdit, 7);
  ASSERT_EQ(mylist.front(), stdlist.front());
  s21::list<int>::ListIterator s21iter;
  s21iter = mylist.end();
  std::list<int>::iterator stditer = stdlist.end();
  mylist.insert(s21iter, 5);
  stdlist.insert(stditer, 5);
  ASSERT_EQ(mylist.front(), stdlist.front());
}
TEST(list, insert_int_const) {
  s21::list<int> mylist{1, 2};
  std::list<int> stdlist{1, 2};
  s21::list<int>::ListConstIterator s21it;
  s21it = mylist.beginConst();
  std::list<int>::const_iterator stdit = stdlist.cbegin();
  mylist.insertConst(s21it, 5);
  stdlist.insert(stdit, 5);
  ASSERT_EQ(mylist.front(), stdlist.front());
  ++s21it;
  ++stdit;
  mylist.insertConst(s21it, 7);
  stdlist.insert(stdit, 7);
  ASSERT_EQ(mylist.front(), stdlist.front());
  s21::list<int>::ListConstIterator s21iter;
  s21iter = mylist.endConst();
  std::list<int>::const_iterator stditer = stdlist.cend();
  mylist.insertConst(s21iter, 5);
  stdlist.insert(stditer, 5);
  ASSERT_EQ(mylist.front(), stdlist.front());
}

TEST(list, sort) {
  s21::list<int> mylist{6, 4, 3, 2, 1, 4, 5};
  std::list<int> stdlist{6, 4, 3, 2, 1, 4, 5};
  std::list<int> sortedlist{1, 2, 3, 4, 5, 6};
  mylist.sort();
  stdlist.sort();
}

TEST(list, iter_eq) {
  s21::list<int> mylist{3, 5, 1, 4, 6, 2};
  s21::list<int>::ListIterator begin = mylist.begin();
  s21::list<int>::ListIterator begin1 = begin;
  s21::list<int>::ListConstIterator cbegin = mylist.beginConst();
  s21::list<int>::ListConstIterator cbegin1 = cbegin;
  ASSERT_TRUE(begin == begin1);
  ASSERT_FALSE(begin != begin1);
  ASSERT_TRUE(cbegin == cbegin1);
  ASSERT_FALSE(cbegin != cbegin1);
}

TEST(list, reverse) {
  s21::list<int> mylist{1, 2};
  std::list<int> stdlist{1, 2};
  mylist.reverse();
  stdlist.reverse();
  s21::list<int>::ListConstIterator s21it;
  s21it = mylist.beginConst();
  std::list<int>::const_iterator stdit = stdlist.cbegin();
  ASSERT_EQ(*s21it, *stdit);
  ++s21it;
  ++stdit;
  ASSERT_EQ(*s21it, *stdit);
}
TEST(list, merge) {
  s21::list<int> mylist1({1, 2});
  s21::list<int> mylist2({3, 4});
  std::list<int> stdlist1({1, 2});
  std::list<int> stdlist2({3, 4});
  mylist1.merge(mylist2);
  stdlist1.merge(stdlist2);
  ASSERT_DOUBLE_EQ(mylist1.size(), stdlist1.size());
  ASSERT_DOUBLE_EQ(mylist2.size(), stdlist2.size());
  auto s21it = mylist1.begin();
  auto stdit = stdlist1.begin();
  ASSERT_EQ(*s21it, *stdit);
  ++s21it;
  ++stdit;
  ASSERT_EQ(*s21it, *stdit);
  ++s21it;
  ++stdit;
  ASSERT_EQ(*s21it, *stdit);
  ++s21it;
  ++stdit;
  ASSERT_EQ(*s21it, *stdit);
}
TEST(list, splice) {
  s21::list<int> mylist1({1, 2});
  s21::list<int> mylist2({3, 4});
  std::list<int> stdlist1({1, 2});
  std::list<int> stdlist2({3, 4});
  auto s21it = mylist1.beginConst();
  auto stdit = stdlist1.begin();
  mylist1.splice(s21it, mylist2);
  stdlist1.splice(stdit, stdlist2);
  ASSERT_DOUBLE_EQ(mylist1.size(), stdlist1.size());
  ASSERT_DOUBLE_EQ(mylist2.size(), stdlist2.size());
}

TEST(list, unique) {
  s21::list<int> mylist{1, 1, 1, 1, 2, 2, 3, 3};
  std::list<int> stdlist{1, 2, 3};
  mylist.unique();
  s21::list<int>::ListIterator s21it = mylist.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(*s21it, *stdit);
  ++s21it;
  ++stdit;
  ASSERT_EQ(*s21it, *stdit);
  ++s21it;
  ++stdit;
  ASSERT_EQ(*s21it, *stdit);
}
TEST(queue, default_constructor) {
  s21::queue<int> s21queue;
  std::queue<int> stdqueue;
  ASSERT_EQ(s21queue.empty(), stdqueue.empty());
}

TEST(queue, init_constructor) {
  s21::queue<int> s21queue{1, 2};
  ASSERT_FALSE(s21queue.empty());
}

TEST(queue, init_string_constructor) {
  s21::queue<std::string> s21queue{"hello", "world"};
  ASSERT_EQ(s21queue.back(), "world");
  ASSERT_EQ(s21queue.front(), "hello");
}

TEST(queue, copy_constructor) {
  s21::queue<int> s21queue{1};
  s21::queue<int> s21queueCopied(s21queue);
  ASSERT_EQ(s21queue.front(), s21queueCopied.front());
}

TEST(queue, move_constructor) {
  s21::queue<int> s21queue{1, 2, 3};
  s21::queue<int> s21queueMoved(std::move(s21queue));
  ASSERT_TRUE(s21queue.empty());
  ASSERT_FALSE(s21queueMoved.empty());
}

TEST(queue, push_int) {
  s21::queue<int> s21queue;
  s21queue.push(566);
  std::queue<int> stdqueue;
  stdqueue.push(566);
  ASSERT_EQ(s21queue.front(), stdqueue.front());
  ASSERT_EQ(s21queue.back(), stdqueue.back());
}

TEST(queue, push_int2) {
  s21::queue<int> s21queue;
  s21queue.push(3);
  s21queue.push(4);
  s21queue.pop();
  std::queue<int> stdqueue;
  stdqueue.push(4);
  ASSERT_EQ(s21queue.front(), stdqueue.front());
}

TEST(queue, pop_int) {
  s21::queue<int> s21queue{1, 2};
  std::queue<int> stdqueue;
  stdqueue.push(1);
  stdqueue.push(2);
  ASSERT_EQ(s21queue.front(), stdqueue.front());
  ASSERT_EQ(s21queue.back(), stdqueue.back());
  s21queue.pop();
  stdqueue.pop();
  ASSERT_EQ(s21queue.front(), stdqueue.front());
  ASSERT_EQ(s21queue.back(), stdqueue.back());
}

TEST(queue, pop_string) {
  s21::queue<std::string> s21queue{"hello", "world"};
  std::queue<std::string> stdqueue;
  stdqueue.push("hello");
  stdqueue.push("world");
  ASSERT_EQ(s21queue.front(), stdqueue.front());
  ASSERT_EQ(s21queue.back(), stdqueue.back());
  s21queue.pop();
  stdqueue.pop();
  ASSERT_EQ(s21queue.front(), stdqueue.front());
  ASSERT_EQ(s21queue.back(), stdqueue.back());
}

TEST(queue, size) {
  s21::queue<int> s21queue{1, 2, 3};
  s21::queue<int> s21queue2{1};
  ASSERT_EQ(s21queue.size(), 3);
  ASSERT_EQ(s21queue2.size(), 1);
}

TEST(queue, swap) {
  s21::queue<int> s21queue{1, 2, 3};
  s21::queue<int> s21queue2{1};
  s21queue.swap(s21queue2);
  ASSERT_EQ(s21queue.size(), 1);
  ASSERT_EQ(s21queue2.size(), 3);
}

TEST(stack, default_constructor) {
  s21::stack<int> s21stack;
  std::stack<int> stdstack;
  ASSERT_EQ(s21stack.empty(), stdstack.empty());
}

TEST(stack, init_constructor) {
  s21::stack<int> s21stack{1, 2, 3};
  ASSERT_FALSE(s21stack.empty());
}

TEST(stack, init_string_constructor) {
  s21::stack<std::string> s21stack{"hello", "world"};
  ASSERT_EQ(s21stack.top(), "world");
}

TEST(stack, copy_constructor) {
  s21::stack<int> s21stack{1};
  s21::stack<int> s21queueCopied(s21stack);
  ASSERT_EQ(s21stack.top(), s21queueCopied.top());
}

TEST(stack, move_constructor) {
  s21::stack<int> s21stack{1, 2, 3};
  s21::stack<int> s21queueMoved(std::move(s21stack));
  ASSERT_TRUE(s21stack.empty());
  ASSERT_FALSE(s21queueMoved.empty());
}

TEST(stack, push_int) {
  s21::stack<int> s21stack;
  std::stack<int> stdstack;
  s21stack.push(1);
  stdstack.push(1);
  ASSERT_EQ(s21stack.top(), stdstack.top());
}

TEST(stack, push_int2) {
  s21::stack<int> s21stack;
  std::stack<int> stdstack;
  s21stack.push(3);
  s21stack.push(4);
  s21stack.pop();
  stdstack.push(3);
  ASSERT_EQ(s21stack.top(), stdstack.top());
}

TEST(stack, pop_int) {
  s21::stack<int> s21stack{1, 2};
  std::stack<int> stdstack;
  stdstack.push(1);
  stdstack.push(2);
  ASSERT_EQ(s21stack.top(), stdstack.top());
  s21stack.pop();
  stdstack.pop();
  ASSERT_EQ(s21stack.top(), stdstack.top());
}

TEST(stack, pop_string) {
  s21::stack<std::string> s21stack{"hello", "world"};
  std::stack<std::string> stdstack;
  stdstack.push("hello");
  stdstack.push("world");
  s21stack.pop();
  stdstack.pop();
  ASSERT_EQ(s21stack.top(), stdstack.top());
}

TEST(stack, size) {
  s21::stack<int> s21stack{1, 2, 3};
  s21::stack<int> s21stack2{1};
  ASSERT_EQ(s21stack.size(), 3);
  ASSERT_EQ(s21stack2.size(), 1);
}

TEST(stack, swap) {
  s21::stack<int> s21stack{1, 2, 3};
  s21::stack<int> s21stack2{1};
  s21stack.swap(s21stack2);
  ASSERT_EQ(s21stack.size(), 1);
  ASSERT_EQ(s21stack2.size(), 3);
}

TEST(vector, constructor) {
  s21::vector<int> v;
  ASSERT_TRUE(v.empty());
}

TEST(vector, initializer) {
  s21::vector<int> v{1, 2, 3};
  ASSERT_TRUE(!v.empty());
  ASSERT_EQ(v.size(), 3);
}

TEST(vector, copy_constructor) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> v2{v1};
  ASSERT_EQ(v1.size(), v2.size());
  for (std::size_t i = 0; i < v1.size(); i++) {
    ASSERT_EQ(v1[i], v2[i]);
  }
}

TEST(vector, copy_constructors) {
  s21::vector<int> original{1, 2, 3};
  s21::vector<int> copy{original};

  ASSERT_EQ(original.size(), copy.size());

  for (size_t i = 0; i < original.size(); ++i) {
    ASSERT_EQ(original[i], copy[i]);
  }
}

TEST(vector, move_operator_constructor) {
  s21::vector<int> myvector{1, 2, 3};
  s21::vector<int> myvectorcopy{myvector};
  s21::vector<int> myvectormove{std::move(myvector)};
  ASSERT_TRUE(myvector.empty());
  ASSERT_FALSE(myvectorcopy.empty());
  ASSERT_FALSE(myvectormove.empty());
}

TEST(vector, move_assignment_operator) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> v2;
  v2 = v1;
  ASSERT_FALSE(v1.empty());
  ASSERT_FALSE(v2.empty());
}

TEST(vector, move_assignment_operators) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> v2;
  v2 = std::move(v1);
  ASSERT_FALSE(v1.empty());
  ASSERT_FALSE(v2.empty());
  ASSERT_EQ(v2.size(), 3);
  ASSERT_EQ(v2[0], 1);
  ASSERT_EQ(v2[1], 2);
  ASSERT_EQ(v2[2], 3);
}

TEST(vector, at) {
  s21::vector<int> v{1, 2, 3, 4, 5};
  ASSERT_EQ(v.at(0), 1);
  ASSERT_EQ(v.at(4), 5);
  ASSERT_THROW(v.at(5), std::out_of_range);
}

TEST(vector, front) {
  s21::vector<int> vec{1, 2, 3};
  int frontValue = vec.front();
  ASSERT_EQ(frontValue, 1);
}

TEST(vector, front_const) {
  s21::vector<int> const vec{1, 2, 3};
  int frontValue = vec.front();
  ASSERT_EQ(frontValue, 1);
}

TEST(vector, back) {
  s21::vector<int> v{42};
  EXPECT_EQ(v.back(), 42);
}

TEST(vector, back_const) {
  s21::vector<int> const v{42};
  EXPECT_EQ(v.back(), 42);
}

TEST(vector, data) {
  s21::vector<int> v{1, 2, 3};
  int* data = v.data();
  ASSERT_EQ(data[0], 1);
  ASSERT_EQ(data[1], 2);
  ASSERT_EQ(data[2], 3);
}

TEST(vector, insert) {
  s21::vector<int> vec{1, 2, 3, 4};
  auto it = vec.insert(vec.begin() + 2, 5);
  ASSERT_EQ(vec.size(), 5);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 5);
  ASSERT_EQ(vec[3], 3);
  ASSERT_EQ(vec[4], 4);
  ASSERT_EQ(*it, 5);
}

TEST(vector, reserve) {
  s21::vector<int> v1{1, 2, 3};
  auto size_before = v1.size();
  v1.reserve(10);
  auto size_after = v1.size();
  EXPECT_EQ(size_before, size_after);
}

TEST(vector, erase) {
  s21::vector<int> myNumbers{1, 2, 3, 4, 5, 6};
  myNumbers.erase(myNumbers.begin() + 2);
  ASSERT_EQ(myNumbers.size(), 5);
  ASSERT_EQ(myNumbers[0], 1);
  ASSERT_EQ(myNumbers[1], 2);
  ASSERT_EQ(myNumbers[2], 4);
  ASSERT_EQ(myNumbers[3], 5);
  ASSERT_EQ(myNumbers[4], 6);
}

TEST(vector, push_back) {
  s21::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  ASSERT_EQ(v.size(), 2);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 2);
}

TEST(vector, pop_back) {
  s21::vector<int> vec{1, 2, 3};
  int last_element = vec.back();
  vec.pop_back();
  ASSERT_EQ(vec.size(), 2);
  ASSERT_EQ(last_element, 3);
}

TEST(vector, swap) {
  s21::vector<int> vector1{1, 2, 3};
  s21::vector<int> vector2{4, 5, 6, 7};
  vector1.swap(vector2);
  ASSERT_EQ(vector1.size(), 4);
  ASSERT_EQ(vector2.size(), 3);
  ASSERT_EQ(vector1[0], 4);
  ASSERT_EQ(vector1[1], 5);
  ASSERT_EQ(vector1[2], 6);
  ASSERT_EQ(vector1[3], 7);
  ASSERT_EQ(vector2[0], 1);
  ASSERT_EQ(vector2[1], 2);
  ASSERT_EQ(vector2[2], 3);
}

TEST(vector, max_size) {
  s21::vector<int> v;
  ASSERT_GE(v.max_size(), v.size());
}

TEST(mapConstructorTest, DefaultConstructor) {
  s21::map<int, std::string> m;
  EXPECT_EQ(m.size(), 0);
  EXPECT_TRUE(m.empty());
}

TEST(mapConstructorTest, InitializerListConstructor) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(m.size(), 3);
  EXPECT_FALSE(m.empty());
  EXPECT_EQ(m.at(1), "one");
  EXPECT_EQ(m.at(2), "two");
  EXPECT_EQ(m.at(3), "three");
}

TEST(mapTest, Moveoperator) {
  s21::map<int, std::string> map1;
  map1.insert(1, "one");
  map1.insert(2, "two");
  map1.insert(3, "three");
  s21::map<int, std::string> map2;
  map2.insert(4, "four");
  map2.insert(5, "five");
  map1 = std::move(map2);
}

TEST(mapConstructorTest, MoveConstructor) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> move = std::move(m);
  EXPECT_EQ(move.size(), 3);
  EXPECT_FALSE(move.empty());
  EXPECT_EQ(move.at(1), "one");
}

TEST(mapConstructorTest, CopyConstructor) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> move = m;
  EXPECT_EQ(move.size(), 3);
  EXPECT_FALSE(move.empty());
  EXPECT_EQ(move.at(1), "one");
}

TEST(mapTest, Operator1) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string>::Iterator iter = m.end();
  iter--;
  EXPECT_EQ(iter->first, 2);
  EXPECT_EQ(iter->second, "two");
}

TEST(mapDestructorTest, Remove2) {
  s21::map<int, std::string> m{{1, "one"}};
  m.~map();
}

TEST(mapTest, InsertKeyValue) {
  s21::map<int, std::string> map;
  map.insert(1, "one");
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  map.insert(2, "two");
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map.contains(2), true);
  EXPECT_EQ(map[2], "two");
}

TEST(mapTest, InsertPair) {
  s21::map<int, std::string> map;
  map.insert(std::make_pair(1, "one"));
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  map.insert(std::make_pair(2, "two"));
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map.contains(2), true);
  EXPECT_EQ(map[2], "two");
}

TEST(mapTest, AtAndOperatorBrackets) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(map.at(1), "one");
  EXPECT_EQ(map[2], "two");
  EXPECT_THROW(map.at(4), std::out_of_range);
  map.insert(4, "four");
  EXPECT_EQ(map[4], "four");
}

TEST(mapTest, EmptyAndSize) {
  s21::map<int, std::string> empty_map;
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_TRUE(empty_map.empty());
  EXPECT_EQ(empty_map.size(), 0);
  EXPECT_FALSE(map.empty());
  EXPECT_EQ(map.size(), 3);
}

TEST(mapTest, MaxSize) {
  s21::map<int, std::string> map;
  std::map<int, std::string> map1;
  EXPECT_GT(map.max_size(), map1.max_size());
}

TEST(mapTest, Erase1) {
  s21::map<int, std::string> map;
  map.insert({1, "one"});
  map.insert({2, "two"});
  map.insert({3, "three"});
  map.insert({5, "five"});
  s21::map<int, std::string>::Iterator it1 = map.begin();
  it1++;
  map.erase(it1->first);
  EXPECT_EQ(map.size(), 3);
  EXPECT_FALSE(map.contains(2));
}

TEST(mapTest, Erase2) {
  s21::map<int, std::string> map;
  map.insert({1, "one"});
  s21::map<int, std::string>::Iterator it1 = map.begin();
  map.erase(it1->first);
  EXPECT_EQ(map.size(), 0);
}

TEST(mapTest, Erase3) {
  s21::map<int, std::string> map;
  map.insert(2, "two");
  map.insert(1, "one");
  map.insert(3, "three");
  s21::map<int, std::string>::Iterator it1 = map.begin();
  it1++;
  map.erase(it1->first);
  EXPECT_EQ(map.size(), 2);
}

TEST(mapTest, Erase4) {
  s21::map<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");
  s21::map<int, std::string>::Iterator it1 = map.begin();
  map.erase(it1->first);
  EXPECT_EQ(map.size(), 1);
}

TEST(mapTest, Erase5) {
  s21::map<int, std::string> map;
  map.insert(3, "three");
  map.insert(2, "two");
  map.insert(1, "one");
  s21::map<int, std::string>::Iterator it1 = map.end();
  map.erase(it1->first);
  EXPECT_EQ(map.size(), 2);
}

TEST(mapTest, Swap) {
  s21::map<int, std::string> map1;
  map1.insert({1, "one"});
  map1.insert({2, "two"});
  s21::map<int, std::string> map2;
  map2.insert({3, "three"});
  map2.insert({4, "four"});
  map1.swap(map2);
  EXPECT_EQ(map1.size(), 2);
  EXPECT_TRUE(map1.contains(3));
  EXPECT_TRUE(map1.contains(4));
  EXPECT_EQ(map2.size(), 2);
  EXPECT_TRUE(map2.contains(1));
  EXPECT_TRUE(map2.contains(2));
}

TEST(mapTest, Merge) {
  s21::map<int, std::string> map1;
  map1.insert({1, "one"});
  map1.insert({2, "two"});
  s21::map<int, std::string> map2;
  map2.insert({3, "three"});
  map2.insert({4, "four"});
  map1.merge(map2);
  EXPECT_EQ(map1.size(), 4);
  EXPECT_TRUE(map1.contains(1));
  EXPECT_TRUE(map1.contains(2));
  EXPECT_TRUE(map1.contains(3));
  EXPECT_TRUE(map1.contains(4));
}

TEST(mapTest, Contains) {
  s21::map<int, std::string> map;
  map.insert({1, "one"});
  map.insert({2, "two"});
  EXPECT_TRUE(map.contains(2));
  EXPECT_FALSE(map.contains(3));
}

TEST(mapTest, Count) {
  s21::map<int, std::string> map;
  map.insert({1, "one"});
  map.insert({2, "two"});
  EXPECT_TRUE(map.count(2));
  EXPECT_FALSE(map.count(3));
}

TEST(set_test, constr1) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::set<int>::Iterator it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, constr2) {
  s21::set<int> s1 = {2, 1, 3, 5, 4, 6, 8, 7};
  std::set<int> s2 = {2, 1, 3, 5, 4, 6, 8, 7};
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, constr3) {
  s21::set<int> s1;
  std::set<int> s2;
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(set_test, constr4) {
  s21::set<int> s1 = {1, 2, 3};
  std::set<int> s2 = {1, 2, 3};
  auto s11 = std::move(s1);
  auto s22 = std::move(s2);
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s11.size(), s22.size());
}

TEST(set_test, constr5) {
  s21::set<int> s1 = {1, 2, 3};
  std::set<int> s2 = {1, 2, 3};
  auto s11 = s1;
  auto s22 = s2;
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s11.size(), s22.size());
}

TEST(set_test, constr6) {
  s21::set<int> s1 = {-100, -200, -15};
  std::set<int> s2 = {-100, -200, -15};
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(set_test, constr7) {
  s21::set<int> s1 = {1, 2, 3};
  std::set<int> s2 = {1, 2, 3};
  s21::set<int> s11;
  std::set<int> s22;
  s11 = std::move(s1);
  s22 = std::move(s2);
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s11.size(), s22.size());
}

TEST(set_test, begin1) {
  s21::set<int> s1 = {1, 2, 3};
  std::set<int> s2 = {1, 2, 3};
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  EXPECT_EQ(*it1, *it2);
}

TEST(set_test, empty1) {
  s21::set<int> s1 = {1, 2, 3};
  std::set<int> s2 = {1, 2, 3};
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(set_test, empty2) {
  s21::set<int> s1 = {1, 2, 3};
  std::set<int> s2 = {1, 2, 3};
  s1.clear();
  s2.clear();
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(set_test, size1) {
  s21::set<int> s1;
  std::set<int> s2;
  s1.insert(1);
  s2.insert(1);
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(set_test, size2) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(set_test, size3) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s1.clear();
  s2.clear();
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(set_test, count1) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_TRUE(s1.count(3));
}

TEST(set_test, count2) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_FALSE(s1.count(9));
}

TEST(set_test, clear1) {
  s21::set<double> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<double> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s1.clear();
  s2.clear();
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(set_test, clear2) {
  s21::set<double> s1;
  std::set<double> s2;
  s1.clear();
  s2.clear();
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(set_test, clear3) {
  s21::set<double> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<double> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s1.clear();
  s2.clear();
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
  s1.clear();
  s2.clear();
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(set_test, insert1) {
  s21::set<double> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<double> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(s1.size(), s2.size());
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(set_test, insert3) {
  s21::set<double> s1 = {3, 2, 1, 4, 6, 5, 7, 8};
  std::set<double> s2 = {3, 2, 1, 4, 6, 5, 7, 8};
  EXPECT_EQ(s1.size(), s2.size());
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(set_test, erase1) {
  s21::set<double> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<double> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(s1.size(), s2.size());
  s1.erase(*s1.begin());
  s2.erase(s2.begin());
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(set_test, erase2) {
  s21::set<double> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<double> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s1.erase(*s1.begin());
  s2.erase(s2.begin());
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(*it1, *it2);
}

TEST(set_test, erase3) {
  s21::set<double> s1 = {1, 5, 3, 4, 2, 6, 7, 8};
  s1.erase(5);
  EXPECT_EQ(s1.size(), 7);
  EXPECT_FALSE(s1.contains(5));
}

TEST(set_test, erase4) {
  s21::set<double> s1 = {2, 3, 8, 4, 1, 6, 7, 5};
  s1.erase(8);
  EXPECT_EQ(s1.size(), 7);
  EXPECT_FALSE(s1.contains(8));
}

TEST(set_test, swap1) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::set<int> s11;
  std::set<int> s22;
  s1.swap(s11);
  s2.swap(s22);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s11.size(), s22.size());
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, swap2) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::set<int> s11 = {389, 3829, 111, 189, 11};
  std::set<int> s22 = {389, 3829, 111, 189, 11};
  s1.swap(s11);
  s2.swap(s22);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s11.size(), s22.size());
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(set_test, find1) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(*(s1.find(3)), *(s2.find(3)));
}

TEST(set_test, contains1) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(s1.contains(1), true);
}

TEST(set_test, contains2) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(s1.contains(0), false);
}

TEST(set_test, iter1) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  for (int i = 0; i < 4; i++) ++it1, ++it2;
  EXPECT_EQ(*it1, *it2);
}

TEST(set_test, iter2) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::set<int>::Iterator it1 = s1.end();
  std::set<int>::iterator it2 = s2.end();
  for (int i = 0; i < 4; i++) {
    --it2;
    EXPECT_EQ(*it1, *it2);
    --it1;
  }
}

TEST(set_test, iter3) {
  s21::set<int> s1 = {1, 5, 2, 4, 3, 6, 7, 8};
  std::set<int> s2 = {1, 5, 2, 4, 3, 6, 7, 8};
  s21::set<int>::Iterator it1 = s1.end();
  std::set<int>::iterator it2 = s2.end();
  for (int i = 0; i < 7; i++) {
    --it2;
    EXPECT_EQ(*it1, *it2);
    --it1;
  }
}

TEST(set_test, iter4) {
  s21::set<int> s1 = {1, 3, 7, 4, 2, 6, 5, 8};
  std::set<int> s2 = {1, 3, 7, 4, 2, 6, 5, 8};
  s21::set<int>::Iterator it1 = s1.end();
  std::set<int>::iterator it2 = s2.end();
  for (int i = 0; i < 7; i++) {
    --it2;
    EXPECT_EQ(*it1, *it2);
    --it1;
  }
}

TEST(set_test, merge1) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::set<int> s11 = {11, 111, 189, 389, 3829};
  std::set<int> s22 = {11, 111, 189, 389, 3829};
  s1.merge(s11);
  s2.merge(s22);
  EXPECT_EQ(s1.size(), s2.size());
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

using namespace std;

TEST(Set_Functions, copy_constructor) {
  std::set<int> std_copy_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};
  std::set<int> std_set = std_copy_set;

  s21::set<int> s21_copy_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};
  s21::set<int> s21_set = s21_copy_set;

  auto std_it = std_set.begin();
  auto s21_it = s21_set.begin();

  for (; std_it != std_set.end(); ++std_it, ++s21_it)
    EXPECT_EQ(*std_it, *s21_it);
}

TEST(Set_Functions, move_constructor) {
  std::set<int> std_moving_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};
  std::set<int> std_set = std::move(std_moving_set);

  s21::set<int> s21_moving_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};
  s21::set<int> s21_set = std::move(s21_moving_set);

  auto std_it = std_set.begin();
  auto s21_it = s21_set.begin();

  for (; std_it != std_set.end(); ++std_it, ++s21_it)
    EXPECT_EQ(*std_it, *s21_it);

  std::set<int> std_null_set;
  std::set<int> std_set_2 = std::move(std_null_set);

  s21::set<int> s21_null_set;
  s21::set<int> s21_set_2 = std::move(s21_null_set);

  EXPECT_EQ(std_null_set.size(), s21_null_set.size());
  EXPECT_EQ(std_set_2.size(), s21_set_2.size());
}

TEST(Set_Functions, assignment_operator_overload) {
  std::set<int> std_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};
  s21::set<int> s21_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};

  std::set<int> std_set_2{55, 43, 45, 23, 46, 12, -123};
  s21::set<int> s21_set_2{55, 43, 45, 23, 46, 12, -123};

  std_set_2 = std::move(std_set);
  s21_set_2 = std::move(s21_set);

  auto std_it = std_set_2.begin();
  auto s21_it = s21_set_2.begin();

  for (; std_it != std_set_2.end(); ++std_it, ++s21_it)
    EXPECT_EQ(*std_it, *s21_it);
}

TEST(Set_Iterators, begin) {
  std::set<int> std_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};
  s21::set<int> s21_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};

  EXPECT_EQ(*(std_set.begin()), *(s21_set.begin()));
}

TEST(Set_Capacity, empty) {
  std::set<int> std_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};
  s21::set<int> s21_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};
  EXPECT_EQ(std_set.empty(), s21_set.empty());

  std::set<int, char> std_empty_set{};
  std::set<int, char> s21_empty_set{};
  EXPECT_EQ(std_empty_set.empty(), s21_empty_set.empty());
}

TEST(Set_Capacity, size) {
  std::set<int> std_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};
  s21::set<int> s21_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};
  EXPECT_EQ(std_set.size(), s21_set.size());

  std::set<int, char> std_empty_set{};
  std::set<int, char> s21_empty_set{};
  EXPECT_EQ(std_empty_set.size(), s21_empty_set.size());
}

TEST(Set_Capacity, max_size) {
  std::set<int, char> std_empty_set{};
  std::set<int, char> s21_empty_set{};
  EXPECT_EQ(std_empty_set.max_size(), s21_empty_set.max_size());
}

TEST(Set_Modifiers, clear) {
  std::set<int> std_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};
  s21::set<int> s21_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};

  std_set.clear();
  s21_set.clear();

  std::set<int, char> std_empty_set{};
  std::set<int, char> s21_empty_set{};

  EXPECT_EQ(std_set.size(), std_empty_set.size());
  EXPECT_EQ(s21_set.size(), s21_empty_set.size());
}

TEST(Set_Modifiers, erase) {
  std::set<int> std_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};
  s21::set<int> s21_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};

  auto std_it = std_set.begin();
  auto s21_it = s21_set.begin();

  std_set.erase(std_it);
  s21_set.erase(*s21_it);

  std_it = std_set.begin();
  s21_it = s21_set.begin();
  for (; std_it != std_set.end(); ++std_it, ++s21_it)
    EXPECT_EQ(*std_it, *s21_it);
}

TEST(Set_Modifier, swap) {
  std::set<int> std_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};
  s21::set<int> s21_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};

  std::set<int> std_set_2{55, 43, 45, 23, 46, 12, -123};
  s21::set<int> s21_set_2{55, 43, 45, 23, 46, 12, -123};

  std_set.swap(std_set_2);
  s21_set.swap(s21_set_2);

  auto std_it = std_set.begin();
  auto s21_it = s21_set.begin();

  for (; std_it != std_set.end(); ++std_it, ++s21_it)
    EXPECT_EQ(*std_it, *s21_it);

  std_it = std_set_2.begin();
  s21_it = s21_set_2.begin();
  for (; std_it != std_set_2.end(); ++std_it, ++s21_it)
    EXPECT_EQ(*std_it, *s21_it);
}

TEST(Set_Modifier, merge) {
  std::set<int> std_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};
  s21::set<int> s21_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};

  std::set<int> std_set_2{55, 43, 45, 23, 46, 12, -123};
  s21::set<int> s21_set_2{55, 43, 45, 23, 46, 12, -123};

  std_set.merge(std_set_2);
  s21_set.merge(s21_set_2);

  auto std_it = std_set.begin();
  auto s21_it = s21_set.begin();
  for (; std_it != std_set.end(); ++std_it, ++s21_it)
    EXPECT_EQ(*std_it, *s21_it);
}

TEST(Set_Lookup, find) {
  std::set<int> std_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};
  s21::set<int> s21_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};

  auto std_it = std_set.find(9);
  auto s21_it = s21_set.find(9);
  EXPECT_EQ(*std_it, *s21_it);
}

TEST(Set_Lookup, contains) {
  std::set<int> std_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};
  s21::set<int> s21_set{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};

  EXPECT_EQ(true, s21_set.contains(-10));
  EXPECT_EQ(false, s21_set.contains(9555));
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
//Test.cpp
// meirshuker15@gmail.com
//Description: This is the test file for the MyContainer class.
//It tests the MyContainer class by adding and removing elements, and printing the container in different orders.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.hpp"
#include "MyContainer.hpp"

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace container;

TEST_CASE("Integer Container") {
    MyContainer<int> container;
    
    SUBCASE("Initial state") {
        CHECK(container.size() == 0);
        CHECK_THROWS_AS(container.remove(5), std::invalid_argument);
    }

    SUBCASE("Add and Size") {
        container.add(10);
        container.add(20);
        CHECK(container.size() == 2);
        container.add(10); // Add duplicate
        CHECK(container.size() == 3);
    }

    SUBCASE("Remove Element") {
        container.add(10);
        container.add(20);
        container.add(10);
        container.add(30);

        container.remove(10);
        CHECK(container.size() == 2);
        // Check that the remaining elements are 20 and 30
        std::vector<int> expected = {20, 30};
        std::vector<int> actual;
        for(const auto& val : container) {
            actual.push_back(val);
        }
        CHECK(actual == expected);
        
        CHECK_THROWS_AS(container.remove(100), std::invalid_argument); // Element not found
    }

    // Setup for iterator tests
    MyContainer<int> iter_container;
    iter_container.add(7);
    iter_container.add(15);
    iter_container.add(6);
    iter_container.add(1);
    iter_container.add(2);
    // Original order: 7, 15, 6, 1, 2
    
    SUBCASE("Order Iterator") {
        std::vector<int> expected = {7, 15, 6, 1, 2};
        std::vector<int> actual;
        for(const auto& val : iter_container) {
            actual.push_back(val);
        }
        CHECK(actual == expected);
    }

    SUBCASE("Reverse Order Iterator") {
        std::vector<int> expected = {2, 1, 6, 15, 7};
        std::vector<int> actual;
        for(auto it = iter_container.begin_reverse_order(); it != iter_container.end_reverse_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("Ascending Order Iterator") {
        std::vector<int> expected = {1, 2, 6, 7, 15};
        std::vector<int> actual;
        for(auto it = iter_container.begin_ascending_order(); it != iter_container.end_ascending_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("Descending Order Iterator") {
        std::vector<int> expected = {15, 7, 6, 2, 1}; // As per README
        std::vector<int> actual;
        for(auto it = iter_container.begin_descending_order(); it != iter_container.end_descending_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }
    
    SUBCASE("Side Cross Order Iterator") {
        std::vector<int> expected = {1, 15, 2, 7, 6}; // As per README
        std::vector<int> actual;
        for(auto it = iter_container.begin_side_cross_order(); it != iter_container.end_side_cross_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("Middle Out Order Iterator") {
        std::vector<int> expected = {6, 15, 1, 7, 2}; // As per README
        std::vector<int> actual;
        for(auto it = iter_container.begin_middle_out_order(); it != iter_container.end_middle_out_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }
}

TEST_CASE("String Container") {
    MyContainer<std::string> container;
    container.add("hello");
    container.add("world");
    container.add("ariel");
    container.add("c++");

    CHECK(container.size() == 4);

    container.remove("world");
    CHECK(container.size() == 3);

    std::vector<std::string> expected_order = {"hello", "ariel", "c++"};
    std::vector<std::string> actual_order;
    for(const auto& s : container) { actual_order.push_back(s); }
    CHECK(actual_order == expected_order);

    std::vector<std::string> expected_asc = {"ariel", "c++", "hello"};
    std::vector<std::string> actual_asc;
    for(auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
        actual_asc.push_back(*it);
    }
    CHECK(actual_asc == expected_asc);

    std::vector<std::string> expected_desc = {"hello", "c++", "ariel"};
    std::vector<std::string> actual_desc;
    for(auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {
        actual_desc.push_back(*it);
    }
    CHECK(actual_desc == expected_desc);

    std::vector<std::string> expected_rev = {"c++", "ariel", "hello"};
    std::vector<std::string> actual_rev;
    for(auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) {
        actual_rev.push_back(*it);
    }
    CHECK(actual_rev == expected_rev);

    std::vector<std::string> expected_side = {"ariel", "hello", "c++"};
    std::vector<std::string> actual_side;
    for(auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
        actual_side.push_back(*it);
    }
    CHECK(actual_side == expected_side);

    // After removing "world", original order is: "hello", "ariel", "c++"
    // Middle-out from original order: ariel, hello, c++
    std::vector<std::string> expected_mid = {"ariel", "hello", "c++"};
    std::vector<std::string> actual_mid;
    for(auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
        actual_mid.push_back(*it);
    }
    CHECK(actual_mid == expected_mid);
}

TEST_CASE("Edge Case Container Scenarios") {
    SUBCASE("Container with a single element") {
        MyContainer<int> container;
        container.add(42);
        CHECK(container.size() == 1);

        std::vector<int> expected = {42};
        
        std::vector<int> actual_order;
        for(const auto& val : container) { actual_order.push_back(val); }
        CHECK(actual_order == expected);

        std::vector<int> actual_asc;
        for(auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) { actual_asc.push_back(*it); }
        CHECK(actual_asc == expected);
        
        std::vector<int> actual_rev;
        for(auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) { actual_rev.push_back(*it); }
        CHECK(actual_rev == expected);

        std::vector<int> actual_side;
        for(auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) { actual_side.push_back(*it); }
        CHECK(actual_side == expected);

        std::vector<int> actual_mid;
        for(auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) { actual_mid.push_back(*it); }
        CHECK(actual_mid == expected);

        container.remove(42);
        CHECK(container.size() == 0);
    }

    SUBCASE("Container with duplicate elements") {
        MyContainer<int> container;
        container.add(5);
        container.add(1);
        container.add(5);
        container.add(2);
        container.add(5);
        // Order: 5, 1, 5, 2, 5

        CHECK(container.size() == 5);

        // Ascending should be 1, 2, 5, 5, 5
        std::vector<int> expected_asc = {1, 2, 5, 5, 5};
        std::vector<int> actual_asc;
        for(auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            actual_asc.push_back(*it);
        }
        CHECK(actual_asc == expected_asc);

        // Side-cross should be 1, 5, 2, 5, 5
        std::vector<int> expected_cross = {1, 5, 2, 5, 5};
        std::vector<int> actual_cross;
        for(auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
            actual_cross.push_back(*it);
        }
        CHECK(actual_cross == expected_cross);

        // Original order: 5, 1, 5, 2, 5. Middle-out: 5, 1, 2, 5, 5
        std::vector<int> expected_mid = {5, 1, 2, 5, 5};
        std::vector<int> actual_mid;
        for(auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
            actual_mid.push_back(*it);
        }
        CHECK(actual_mid == expected_mid);
    }

    SUBCASE("Container with even number of elements") {
        MyContainer<int> container;
        container.add(10);
        container.add(20);
        container.add(30);
        container.add(40);
        // Order: 10, 20, 30, 40
        // MiddleOut for even n=4: Indices: 1, 0, 2, 3 -> Values: 20, 10, 30, 40
        std::vector<int> expected_mid = {20, 10, 30, 40};
        std::vector<int> actual_mid;
        for(auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
            actual_mid.push_back(*it);
        }
        CHECK(actual_mid == expected_mid);

        // SideCross for sorted [10, 20, 30, 40] should be: 10, 40, 20, 30
        std::vector<int> expected_cross = {10, 40, 20, 30};
        std::vector<int> actual_cross;
        for(auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
            actual_cross.push_back(*it);
        }
        CHECK(actual_cross == expected_cross);

        // Create an iterator. It creates an internal sorted copy: {10, 20, 30}
        auto it = container.begin_ascending_order();
        auto end_it = container.end_ascending_order(); // Create end iterator from the same snapshot
        
        // Modify the container
        container.add(5); // container is now {10, 30, 20, 5}
        
        // The iterator should still loop over its original snapshot
        std::vector<int> actual;
        while (it != end_it) { // Compare against the original end iterator
            actual.push_back(*it);
            ++it;
        }
        std::vector<int> expected_snapshot = {10, 20, 30,40};
        CHECK(actual == expected_snapshot);

        // A new iterator should reflect the change
        std::vector<int> actual_new;
         for(auto it_new = container.begin_ascending_order(); it_new != container.end_ascending_order(); ++it_new) {
            actual_new.push_back(*it_new);
        }
        std::vector<int> expected_new = {5, 10, 20, 30,40};
        CHECK(actual_new == expected_new);
    }
}

TEST_CASE("Empty Container Iterators") {
    MyContainer<int> empty_container;
    
    CHECK(empty_container.begin_order() == empty_container.end_order());
    CHECK(empty_container.begin_reverse_order() == empty_container.end_reverse_order());
    CHECK(empty_container.begin_ascending_order() == empty_container.end_ascending_order());
    CHECK(empty_container.begin_descending_order() == empty_container.end_descending_order());
    CHECK(empty_container.begin_side_cross_order() == empty_container.end_side_cross_order());
    CHECK(empty_container.begin_middle_out_order() == empty_container.end_middle_out_order());
}

TEST_CASE("Iterator In-Depth Functionality") {
    SUBCASE("Iterator prefix and postfix operators") {
        MyContainer<int> container;
        container.add(10);
        container.add(20);
        container.add(30);
        // Ascending order will be: 10, 20, 30

        // Test prefix increment
        auto pit = container.begin_ascending_order();
        CHECK(*pit == 10);
        ++pit;
        CHECK(*pit == 20);
        
        // Test postfix increment
        auto post = pit++;
        CHECK(*post == 20);
        CHECK(*pit == 30);

        // Repeat for ReverseOrder
        auto rit = container.begin_reverse_order(); // reverse: 30,20,10
        CHECK(*rit == 30);
        ++rit;
        CHECK(*rit == 20);
        auto rpost = rit++;
        CHECK(*rpost == 20);
        CHECK(*rit == 10);
    }

    SUBCASE("Iterator after container modification") {
        MyContainer<int> container;
        container.add(11);
        container.add(8);
        container.add(15);
        container.add(2);
        container.add(4);

        std::vector<int> expected_before = {15, 8, 2, 11, 4};
        std::vector<int> actual_before;
        for(auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
            actual_before.push_back(*it);
        }
        CHECK(actual_before == expected_before);

        
        container.remove(8); // Now container is [11, 15, 2, 4]
        CHECK(container.size() == 4);

        std::vector<int> expected_after = {15, 11, 2, 4};
        std::vector<int> actual_after;
        for(auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
            actual_after.push_back(*it);
        }
        CHECK(actual_after == expected_after);
    }
}

// NEW TEST CASE: streaming operator<<
TEST_CASE("Operator<< Streaming") {
    MyContainer<int> container;
    container.add(1);
    container.add(2);
    container.add(3);
    std::ostringstream oss;
    oss << container;
    CHECK(oss.str() == "[1, 2, 3]");
}

TEST_CASE("Iterator Comparisons and End Detection") {
    MyContainer<int> container;
    container.add(5);
    container.add(10);
    
    // begin()/end() comparison
    auto it1 = container.begin_order();
    auto it2 = container.end_order();
    CHECK((it1 != it2));
    ++it1; ++it1; // move to end
    CHECK((it1 == it2));
}

// Custom struct for testing templates with user-defined types
struct Person {
    std::string name;
    int age;

    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }

    bool operator<(const Person& other) const {
        return age < other.age;
    }
     bool operator>(const Person& other) const {
        return age > other.age;
    }
    // for doctest
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << "{" << p.name << ", " << p.age << "}";
        return os;
    }
};


TEST_CASE("Custom Object Container") {
    MyContainer<Person> people;
    Person alice{"Alice", 30};
    Person bob{"Bob", 25};
    Person charlie{"Charlie", 35};

    people.add(alice);
    people.add(bob);
    people.add(charlie);

    CHECK(people.size() == 3);

    SUBCASE("Ascending Order (by age)") {
        std::vector<Person> expected = {bob, alice, charlie};
        std::vector<Person> actual;
        for(auto it = people.begin_ascending_order(); it != people.end_ascending_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("Remove person") {
        people.remove(alice);
        CHECK(people.size() == 2);
        CHECK_THROWS_AS(people.remove(alice), std::invalid_argument);
    }
}

TEST_CASE("Iterator Snapshot Behavior") {
    MyContainer<int> container;
    container.add(10);
    container.add(30);
    container.add(20);

    // Create an iterator. It creates an internal sorted copy: {10, 20, 30}
    auto it = container.begin_ascending_order();
    size_t initial_size = container.size();
    
    // Modify the container
    container.add(5); // container is now {10, 30, 20, 5}
    
    // The iterator should still loop over its original snapshot of 3 elements
    std::vector<int> actual;
    for(size_t i = 0; i < initial_size; ++i) {
        actual.push_back(*it);
        ++it;
    }
    std::vector<int> expected_snapshot = {10, 20, 30};
    CHECK(actual == expected_snapshot);

    // A new iterator should reflect the change
    std::vector<int> actual_new;
     for(auto it_new = container.begin_ascending_order(); it_new != container.end_ascending_order(); ++it_new) {
        actual_new.push_back(*it_new);
    }
    std::vector<int> expected_new = {5, 10, 20, 30};
    CHECK(actual_new == expected_new);
}

TEST_CASE("Const Container") {
    MyContainer<int> container;
    container.add(1);
    container.add(2);
    
    const MyContainer<int>& const_container = container;

    CHECK(const_container.size() == 2);
    
    // Check that all begin/end methods are callable on a const object
    CHECK(const_container.begin() != const_container.end());
    CHECK(const_container.begin_order() != const_container.end_order());
    CHECK(const_container.begin_reverse_order() != const_container.end_reverse_order());
    CHECK(const_container.begin_ascending_order() != const_container.end_ascending_order());
    CHECK(const_container.begin_descending_order() != const_container.end_descending_order());
    CHECK(const_container.begin_side_cross_order() != const_container.end_side_cross_order());
    CHECK(const_container.begin_middle_out_order() != const_container.end_middle_out_order());
}

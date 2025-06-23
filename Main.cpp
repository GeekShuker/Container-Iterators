// meirshuker15@gmail.com
#include <iostream>
#include "MyContainer.hpp"
using namespace container;

int main() {
    // =================================================================
    // Integer Container Demonstration
    // =================================================================
    std::cout << "--- Integer Container Demonstration ---" << std::endl;
    MyContainer<int> container;
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);

    std::cout << "Original container: " << container << std::endl;
    std::cout << "Size of container: " << container.size() << std::endl << std::endl;

    std::cout << "--- Iterators for Integer Container ---" << std::endl;
    std::cout << "Order (default): ";
    for (const auto& val : container) {
        std::cout << val << ' ';  // 7 15 6 1 2
    }
    std::cout << std::endl;

    std::cout << "Reverse: ";
    for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) {
        std::cout << *it << ' ';  // 2 1 6 15 7
    }
    std::cout << std::endl;

    std::cout << "Ascending: ";
    for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
        std::cout << *it << ' ';   // 1 2 6 7 15
    }
    std::cout << std::endl;

    std::cout << "Descending: ";
    for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {
        std::cout << *it << ' ';  // 15 7 6 2 1
    }
    std::cout << std::endl;
    
    std::cout << "Side-Cross: ";
    for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
        std::cout << *it << ' ';  // 1 15 2 7 6
    }
    std::cout << std::endl;

    std::cout << "Middle-Out: ";
    for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
        std::cout << *it << ' ';  // 6 15 1 7 2
    }
    std::cout << std::endl;

    // =================================================================
    // String Container Demonstration
    // =================================================================
    std::cout << "\n--- String Container Demonstration ---" << std::endl;
    MyContainer<std::string> string_container;
    string_container.add("C++");
    string_container.add("Java");
    string_container.add("Python");
    string_container.add("Rust");
    string_container.add("Go");
    string_container.add("Java");
    
    std::cout << "Original string container: " << string_container << std::endl;
    
    std::cout << "\n--- Testing remove() and exception ---" << std::endl;
    string_container.remove("Java");
    std::cout << "After removing 'Java': " << string_container << std::endl;

    try {
        std::cout << "Attempting to remove 'JavaScript' (which doesn't exist)..." << std::endl;
        string_container.remove("JavaScript");
    } catch (const std::invalid_argument& e) {
        std::cerr << "Caught expected exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n--- Iterators for String Container ---" << std::endl;
    std::cout << "Ascending: ";
    for (auto it = string_container.begin_ascending_order(); it != string_container.end_ascending_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "Descending: ";
    for (auto it = string_container.begin_descending_order(); it != string_container.end_descending_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "Side-Cross: ";
    for (auto it = string_container.begin_side_cross_order(); it != string_container.end_side_cross_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

     std::cout << "Reverse (strings): ";
    for (auto it = string_container.begin_reverse_order(); it != string_container.end_reverse_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "Order (default, strings): ";
    for (const auto& s : string_container) {
        std::cout << s << ' ';
    }
    std::cout << std::endl;

    std::cout << "Middle-Out (strings): ";
    for (auto it = string_container.begin_middle_out_order(); it != string_container.end_middle_out_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    // =================================================================
    // Interaction Demonstration
    // =================================================================
    std::cout << "\n--- Interaction Demonstration ---" << std::endl;
    MyContainer<std::string> another_string_container;
    another_string_container.add("Start");
    std::cout << "Second container before adding elements: " << another_string_container << std::endl;
    
    for(const auto& lang : string_container) {
        another_string_container.add(lang);
    }
    std::cout << "Second container after adding elements from the first: " << another_string_container << std::endl;
    
    return 0;
}

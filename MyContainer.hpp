// meirshuker15@gmail.com
//MyContainer.hpp
//Description: This is the header file for the MyContainer class.
//It contains the class definition and the implementations of the methods.

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace container {
    
    /// @brief A generic container class that stores a dynamic collection of elements.
    /// @details This container allows for adding and removing elements, and provides
    ///          six different types of iterators for traversing the elements in various orders.
    /// @tparam T The type of elements to be stored in the container.
    template<typename T>

    class MyContainer {
    private:
        /// @brief The underlying std::vector used to store the container's elements.
        std::vector<T> elements;

    public:

        /*===============================================
        Container Management 
        ===============================================*/

        /// @brief Adds a new element to the container.
        /// @param element The element to be added to the container.
        void add(T element) {
            elements.push_back(element);
        }

        /// @brief Removes all occurrences of a specific element from the container.
        /// @param element The value of the element to remove.
        /// @throws std::invalid_argument if the specified element is not found in the container.
        void remove(T element) {
            auto original_size = elements.size();
            elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
            if (elements.size() == original_size) {
                throw std::invalid_argument("Element not found in container.");
            }
        }

        /// @brief Gets the current number of elements in the container.
        /// @return The total number of elements as an integer.
        int size() const {
            return elements.size();
        }

        /*========================== Iterator Definitions ==========================*/

        /*===============================================
        Insertion Order
        ===============================================*/

        /// @brief An iterator that traverses the container in the original insertion order.
        class Order {
        private:
            typename std::vector<T>::const_iterator current;

        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = const T*;
            using reference = const T&;

            /// @brief Constructs an Order.
            /// @param ptr A const_iterator pointing to the element.
            Order(typename std::vector<T>::const_iterator ptr) : current(ptr) {}

            /// @brief Dereferences the iterator to get the element.
            /// @return A const reference to the element.
            reference operator*() const { return *current; }
            
            /// @brief Provides pointer access to the element.
            /// @return A const pointer to the element.
            pointer operator->() const { return &(*current); }
            
            /// @brief Advances the iterator to the next element (prefix).
            Order& operator++() {
                ++current;
                return *this;
            }

            /// @brief Postfix increment.
            Order operator++(int) {
                Order temp = *this;
                ++(*this);
                return temp;
            }

            bool operator!=(const Order& other) const { return current != other.current; }
            bool operator==(const Order& other) const { return current == other.current; }
        };

        /*===============================================
        Reverse Order
        ===============================================*/

        /// @brief An iterator that traverses the container in the reverse of the insertion order.
        class ReverseOrder {
        private:
            typename std::vector<T>::const_reverse_iterator current;
        
        public:
            /// @brief Constructs a ReverseOrder.
            /// @param ptr A const_reverse_iterator pointing to the element.
            ReverseOrder(typename std::vector<T>::const_reverse_iterator ptr) : current(ptr) {}

            /// @brief Dereferences the iterator to get the element.
            const T& operator*() const { return *current; }
            
            /// @brief Provides pointer access to the element.
            const T* operator->() const { return &(*current); }
            
            /// @brief Advances the iterator to the next element (prefix).
            ReverseOrder& operator++() {
                ++current;
                return *this;
            }

            ReverseOrder operator++(int) {
                ReverseOrder temp = *this;
                ++(*this);
                return temp;
            }

            bool operator!=(const ReverseOrder& other) const { return current != other.current; }
            bool operator==(const ReverseOrder& other) const { return current == other.current; }
        };

        /*===============================================
        Ascending Order
        ===============================================*/

        /// @brief An iterator that traverses the container's elements in sorted ascending order.
        class AscendingOrder {
        private:
            std::vector<T> sorted_elements;
            size_t index;
        public:
            /// @brief Constructs an AscendingOrder.
            /// @param original_elements The container's elements to be sorted and traversed.
            /// @param is_end Flag to indicate if this should be an end iterator.
            explicit AscendingOrder(const std::vector<T>& original_elements, bool is_end = false) : sorted_elements(original_elements) {
                std::sort(sorted_elements.begin(), sorted_elements.end());
                this->index = is_end ? sorted_elements.size() : 0;
            }

            const T& operator*() const { return sorted_elements[index]; }
            
            AscendingOrder& operator++() {
                ++index;
                return *this;
            }
            
            AscendingOrder operator++(int) {
                AscendingOrder temp = *this;
                ++(*this);
                return temp;
            }

            bool operator!=(const AscendingOrder& other) const { return this->index != other.index; }
            bool operator==(const AscendingOrder& other) const { return this->index == other.index; }
        };

        /*===============================================
        Descending Order
        ===============================================*/
        
        /// @brief An iterator that traverses the container's elements in sorted descending order.
        class DescendingOrder {
        private:
            std::vector<T> sorted_elements;
            size_t index;
        public:
            /// @brief Constructs a DescendingOrder.
            /// @param original_elements The container's elements to be sorted and traversed.
            /// @param is_end Flag to indicate if this should be an end iterator.
            explicit DescendingOrder(const std::vector<T>& original_elements, bool is_end = false) : sorted_elements(original_elements) {
                std::sort(sorted_elements.begin(), sorted_elements.end(), std::greater<T>());
                this->index = is_end ? sorted_elements.size() : 0;
            }

            const T& operator*() const { return sorted_elements[index]; }
            
            DescendingOrder& operator++() {
                ++index;
                return *this;
            }

            DescendingOrder operator++(int) {
                DescendingOrder temp = *this;
                ++(*this);
                return temp;
            }

            bool operator!=(const DescendingOrder& other) const { return this->index != other.index; }
            bool operator==(const DescendingOrder& other) const { return this->index == other.index; }
        };

        /*===============================================
        Side Cross Order
        ===============================================*/
        
        /// @brief An iterator that traverses elements by alternating between the smallest and largest.
        /// @details Traversal order is: first, last, second, second-to-last, and so on.
        class SideCrossOrder {
        private:
            std::vector<T> sorted_elements;
            size_t left;
            size_t right;
            size_t count;
        public:
            /// @brief Constructs a SideCrossOrder.cut
            /// @param original_elements The container's elements to be sorted and traversed.
            /// @param is_end Flag to indicate if this should be an end iterator.
            explicit SideCrossOrder(const std::vector<T>& original_elements, bool is_end = false) : sorted_elements(original_elements) {
                std::sort(sorted_elements.begin(), sorted_elements.end());
                this->left = 0;
                this->right = sorted_elements.empty() ? 0 : sorted_elements.size() - 1;
                this->count = is_end ? sorted_elements.size() : 0;
            }

            const T& operator*() const {
                if (count % 2 == 0) return sorted_elements[left];
                return sorted_elements[right];
            }

            SideCrossOrder& operator++() {
                if (count % 2 == 0) left++;
                else right--;
                count++;
                return *this;
            }

            SideCrossOrder operator++(int) {
                SideCrossOrder temp = *this;
                ++(*this);
                return temp;
            }

            bool operator!=(const SideCrossOrder& other) const { return this->count != other.count; }
            bool operator==(const SideCrossOrder& other) const { return this->count == other.count; }
        };

        /*===============================================
        Middle Out Order
        ===============================================*/
        
        /// @brief An iterator that traverses elements by spiraling outwards from the middle.
        /// @details Traversal order is: middle, element left of middle, element right of middle, etc.
        class MiddleOutOrder {
        private:
            const std::vector<T>& original_elements_ref;
            std::vector<size_t> traversal_indices;
            size_t current_pos_in_indices;
        public:
            /// @brief Constructs a MiddleOutOrder.
            /// @param original_elements The container's elements to be traversed.
            /// @param is_end Flag to indicate if this should be an end iterator.
            explicit MiddleOutOrder(const std::vector<T>& original_elements, bool is_end = false) : original_elements_ref(original_elements) {
                size_t n = original_elements.size();
                if (n > 0) {
                    traversal_indices.reserve(n);
                    size_t mid = (n - 1) / 2;
                    traversal_indices.push_back(mid);
                    
                    size_t l = mid - 1;
                    size_t r = mid + 1;
                    while (traversal_indices.size() < n) {
                        if (l < n) { // Check for wrap around
                            traversal_indices.push_back(l--);
                        }
                        if (r < n) {
                            traversal_indices.push_back(r++);
                        }
                    }
                }
                this->current_pos_in_indices = is_end ? n : 0;
            }

            const T& operator*() const {
                return original_elements_ref[traversal_indices[current_pos_in_indices]];
            }
            
            MiddleOutOrder& operator++() {
                current_pos_in_indices++;
                return *this;
            }
            
            MiddleOutOrder operator++(int) {
                MiddleOutOrder temp = *this;
                ++(*this);
                return temp;
            }

            bool operator!=(const MiddleOutOrder& other) const { return this->current_pos_in_indices != other.current_pos_in_indices; }
            bool operator==(const MiddleOutOrder& other) const { return this->current_pos_in_indices == other.current_pos_in_indices; }
        };

        /*===============================================
        Iterator Accessor Methods
        ===============================================*/

        // Default iterators for range-based for loops (insertion order)
        Order begin() const { return begin_order(); }
        Order end() const { return end_order(); }

        /// @brief Gets an iterator to the beginning of the insertion-order sequence.
        Order begin_order() const { return Order(elements.cbegin()); }
        /// @brief Gets an iterator to the end of the insertion-order sequence.
        Order end_order() const { return Order(elements.cend()); }
        
        /// @brief Gets an iterator to the beginning of the reverse-order sequence.
        ReverseOrder begin_reverse_order() const { return ReverseOrder(elements.crbegin()); }
        /// @brief Gets an iterator to the end of the reverse-order sequence.
        ReverseOrder end_reverse_order() const { return ReverseOrder(elements.crend()); }

        /// @brief Gets an iterator to the beginning of the ascending-order sequence.
        AscendingOrder begin_ascending_order() const { return AscendingOrder(elements); }
        /// @brief Gets an iterator to the end of the ascending-order sequence.
        AscendingOrder end_ascending_order() const { return AscendingOrder(elements, true); }

        /// @brief Gets an iterator to the beginning of the descending-order sequence.
        DescendingOrder begin_descending_order() const { return DescendingOrder(elements); }
        /// @brief Gets an iterator to the end of the descending-order sequence.
        DescendingOrder end_descending_order() const { return DescendingOrder(elements, true); }

        /// @brief Gets an iterator to the beginning of the side-cross sequence.
        SideCrossOrder begin_side_cross_order() const { return SideCrossOrder(elements); }
        /// @brief Gets an iterator to the end of the side-cross sequence.
        SideCrossOrder end_side_cross_order() const { return SideCrossOrder(elements, true); }

        /// @brief Gets an iterator to the beginning of the middle-out sequence.
        MiddleOutOrder begin_middle_out_order() const { return MiddleOutOrder(elements); }
        /// @brief Gets an iterator to the end of the middle-out sequence.
        MiddleOutOrder end_middle_out_order() const { return MiddleOutOrder(elements, true); }
    };

    /// @brief Overloads the << operator for easy printing of MyContainer contents.
    /// @param os The output stream.
    /// @param container The MyContainer to be printed.
    /// @return A reference to the output stream.
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const MyContainer<T>& container) {
        os << "[";
        bool first = true;
        for (const T& element : container) {
            if (!first) {
                os << ", ";
            }
            os << element;
            first = false;
        }
        os << "]";
        return os;
    }
} 
# Container - Iterators Project

## Overview

This project implements a generic C++ container class, `MyContainer`, which can hold any comparable data type. It supports dynamic addition and removal of elements, and provides six distinct custom iterators for traversing the container's elements in different, meaningful orders.

## Features

*   **Generic Container**: `MyContainer<T>` can store elements of any type `T` that supports comparison operators (`!=`, `==`).
*   **Dynamic Size**: Elements can be added and removed dynamically.
*   **Multiple Traversal Orders**: The container comes with six different types of iterators.
*   **Custom Printing**: An overloaded `operator<<` is provided for easy printing of the container's contents to an output stream.

## Iterators Provided

1.  **`Order`** (default): Traverses elements in their original insertion order.
2.  **`ReverseOrder`**: Traverses elements in the reverse of their insertion order.
3.  **`AscendingOrder`**: Traverses elements in sorted ascending order.
4.  **`DescendingOrder`**: Traverses elements in sorted descending order.
5.  **`SideCrossOrder`**: Traverses elements by alternating between the smallest and largest remaining elements (e.g., first, last, second, second-to-last, etc.).
6.  **`MiddleOutOrder`**: Traverses elements starting from the middle element of the original sequence and spiraling outwards.


## Project Structure

```
.
├── MyContainer.hpp      # Main header with container and iterator implementations
├── Main.cpp             # Demo program showcasing container usage
├── Test.cpp             # Unit tests for all functionality
├── Makefile             # Build script for compiling, testing, and cleaning
├── doctest.hpp          # Single-header test framework
└── README.md            
```

## How to Build and Run

A `Makefile` is provided to streamline the process. The following commands are available:

*   `make`: Compiles both the main demo program and the test suite.
*   `make run`: Compiles and runs the demonstration program (`Main.cpp`).
*   `make test`: Compiles and executes the unit tests (`Test.cpp`) via `doctest`.
*   `make valgrind`: Runs the test suite under `valgrind` to check for memory leaks.
*   `make clean`: Removes all compiled executables and temporary files.

## Testing

The project is tested using the [doctest](https://github.com/doctest/doctest) framework. The test suite in `Test.cpp` covers:
*   Basic container operations (`add`, `remove`, `size`).
*   Correct traversal logic for all six iterator types.
*   Edge cases, such as empty containers, single-element containers, and containers with duplicate values.
*   Iterator snapshot behavior after container modification.
*   `const` correctness of the container.
*   Usage with both primitive (`int`) and complex (`std::string`, custom `struct`) data types.

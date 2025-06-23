# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -pedantic-errors

# Valgrind options
VALGRIND = valgrind
VFLAGS = --leak-check=full --show-leak-kinds=all --error-exitcode=1

# Source files and targets
MAIN_SRC = Main.cpp
TEST_SRC = Test.cpp
MAIN_EXEC = Main_run
TEST_EXEC = test_run

# Default target
all: $(MAIN_EXEC) $(TEST_EXEC)

# Rule to build the main executable
$(MAIN_EXEC): $(MAIN_SRC) MyContainer.hpp
	$(CXX) $(CXXFLAGS) -o $(MAIN_EXEC) $(MAIN_SRC)

# Rule to build the test executable
$(TEST_EXEC): $(TEST_SRC) MyContainer.hpp doctest.hpp
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $(TEST_SRC)

# Rule to run the main executable per README requirement
Main: $(MAIN_EXEC)
	./$(MAIN_EXEC)

# Rule to run the tests
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Rule to run tests and main with valgrind
valgrind: $(TEST_EXEC) $(MAIN_EXEC)
	$(VALGRIND) $(VFLAGS) ./$(TEST_EXEC)
	$(VALGRIND) $(VFLAGS) ./$(MAIN_EXEC)

# Rule to clean up generated files
clean:
	rm -f $(MAIN_EXEC) $(TEST_EXEC) *.o

# Phony targets
.PHONY: all Main test valgrind clean 
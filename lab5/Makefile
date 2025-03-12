# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Executable and source files
TARGET = runTest
SRC = jxchulab5.cpp
TEST_DIR = testFile
RESULT_FILE = results.txt

# Get all test files in testFile directory
TEST_FILES = $(wildcard $(TEST_DIR)/*.txt)

# Default target: Compile and run tests
all: $(TARGET) run-tests

# Compile the program
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Run all test files and save output to results.txt
run-tests: $(TARGET)
	@echo "Running all tests..." > $(RESULT_FILE)
	@echo "======================" >> $(RESULT_FILE)
	@for test in $(TEST_FILES); do \
		echo "Running test with file: $$test" >> $(RESULT_FILE); \
		echo "-----------------------------" >> $(RESULT_FILE); \
		./$(TARGET) "$$test" >> $(RESULT_FILE) 2>&1; \
		echo "\n" >> $(RESULT_FILE); \
	done
	@cat $(RESULT_FILE)

# Clean compiled files and result file
clean:
	rm -f $(TARGET) $(RESULT_FILE)

re: clean all
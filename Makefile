# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++20 -Wall -Wextra

# Source files directory
SRC_DIR := src

# Object files directory
OBJ_DIR := build

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Output executable
TARGET := ipk24chat-client

# Build rule
.PHONY: build
build: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Phony target to clean the project
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Phony target to run the executable
.PHONY: run
run: $(TARGET)
	./$(TARGET)

# Default target
.DEFAULT_GOAL := build

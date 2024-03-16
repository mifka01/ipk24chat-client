# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++20 -Wall -Wextra

# Source files directory
SRC_DIR := src

# Object files directory
BUILD_DIR:= build

# Include files directory
INCLUDE_DIR := include

# Source files
SRCS := $(shell find $(SRC_DIR) -type f -name "*.cpp")

# Header files
HDRS := $(shell find $(INCLUDE_DIR) -type f -name "*.hpp")

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Output executable
TARGET := ipk24chat-client

# Build rule
.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $^ -o $@ 

# Rule to compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HDRS) | create_obj_dir
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@ 

# Create the object directory if it doesn't exist
.PHONY: create_obj_dir
create_obj_dir:
	mkdir -p $(dir $(OBJS))

# Phony target to clean the project
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Phony target to run the executable
.PHONY: run
run: $(TARGET)
	./$(TARGET)

# Default target
.DEFAULT_GOAL := all


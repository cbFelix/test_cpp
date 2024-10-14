CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

INCLUDE_DIR = include
SRC_DIR = src
MAIN_DIR = main
BUILD_DIR = bin
OBJ_DIR = obj

MAIN_SRC = $(MAIN_DIR)/main.cpp
SRC_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

OBJECTS = $(SRC_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

TARGET = $(BUILD_DIR)/program

all: $(TARGET)

$(TARGET): $(OBJECTS) $(OBJ_DIR)/main.o
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) -o $@ $^

$(OBJ_DIR)/main.o: $(MAIN_SRC)
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(OBJ_DIR)

rebuild: clean all

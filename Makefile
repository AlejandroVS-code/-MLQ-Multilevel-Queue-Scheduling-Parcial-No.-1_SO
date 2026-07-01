CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
SRC = $(wildcard src/*.cpp)
TARGET = simulator

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean

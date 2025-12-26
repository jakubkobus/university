CXX = g++
CXXFLAGS = -Wall -pedantic
TARGET = bin/main
SOURCES = main.cpp BinaryTree.cpp
OBJECTS = $(SOURCES:%.cpp=bin/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

bin/%.o: %.cpp
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf bin
CXX = g++
CXXFLAGS = -Wall -pedantic -lm
TARGET = bin/main
SOURCES = main.cpp czworokat.cpp kolo.cpp kwadrat.cpp romb.cpp prostokat.cpp pieciokat.cpp szesciokat.cpp
OBJECTS = $(SOURCES:%.cpp=bin/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

bin/%.o: %.cpp
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf bin
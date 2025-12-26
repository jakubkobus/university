CXX = g++
CXXFLAGS = -Wall -pedantic
TARGET = main
SOURCES = main.cpp ArabRzym.cpp ArabRzymException.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET)

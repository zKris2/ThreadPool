CXX := g++ 
CXXFLAGS := -Wall -g -std=c++11 -pthread

TARGET := ThreadPool

SRCDIRS := . utils
SOURCES := $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.cpp))
OBJECTS := $(SOURCES:%.cpp=%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX)$(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX)$(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

.PHONY: all clean

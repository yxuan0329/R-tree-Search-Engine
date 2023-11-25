
CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -shared -fPIC `python3 -m pybind11 --includes`
SRCS = main.cpp rtree.cpp
CIMPORTPATH = "includes"
OBJS = $(SRCS:.cpp=.o)
TARGET = rtree.so

all: $(TARGET)


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

test:
	python3 -m pytest test_Rtree.py -v.

.PHONY: all clean test

CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -shared -fPIC `python3 -m pybind11 --includes`
SRCS = src/Node.cpp src/Rtree.cpp
INCLUDES = includes/Node.h includes/Rtree.h
CIMPORTPATH = "includes"
TARGET = _myRtree.so

all: $(TARGET)

$(TARGET): $(INCLUDES) $(SRCS) pybind.cpp
	$(CXX) $^ $(CXXFLAGS) -I/usr/include/mk -I$(CIMPORTPATH) -o $@

clean:
	rm -f *.so *.o

test:
	python3 -m pytest test_Rtree.py -v

.PHONY: all clean test
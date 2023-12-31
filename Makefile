
CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -shared -fPIC `python3 -m pybind11 --includes`
SRCS = src/Node.cpp src/Rtree.cpp src/pybind.cpp
INCLUDES = includes/Node.h includes/Rtree.h
CIMPORTPATH = "includes"
TARGET = _Rtree.so

all: $(TARGET)

$(TARGET): $(INCLUDES) $(SRCS) 
	$(CXX) $^ $(CXXFLAGS) -I/usr/include/mk -I$(CIMPORTPATH) -o $@

clean:
	rm -f *.so *.o

test:
	python3 -m pytest ./test/test_Rtree.py -v --capture=no

.PHONY: all clean test
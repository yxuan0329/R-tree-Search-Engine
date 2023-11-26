#include <iostream>
#include <vector>
#include <algorithm>

#include "Node.h"
#include "Rtree.h"


int main(){
    std::cout << "Rtree main function" << std::endl;

    Rtree rtree = Rtree();
    std::cout << "root=" << rtree.getRoot() << std::endl;
    rtree.insert(Rect(Point(1, 2), Point(3, 4), 1));
    std::cout << "root=" << rtree.getRoot() << std::endl;
    std::cout << "size=" << rtree.getSize() << std::endl;
    return 0;
}
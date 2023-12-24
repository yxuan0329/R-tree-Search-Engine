#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

#include "includes/Rtree.h"


int main(){
    auto start_time = std::chrono::high_resolution_clock::now(); // start timer
    std::cout << "Rtree main function" << std::endl;
    Rtree rtree = Rtree(2, 4);
    std::cout << "root=" << rtree.getRoot() << std::endl;
    rtree.insert(Rect(Point(0, 0), Point(2, 2), 1));
    rtree.insert(Rect(Point(3, 3), Point(4, 4), 2));
    rtree.insert(Rect(Point(0, 0), Point(1, 1), 3));
    rtree.insert(Rect(Point(5, 5), Point(6, 6), 4));
    rtree.insert(Rect(Point(7, 7), Point(8, 8), 5));
    rtree.insert(Rect(Point(9, 9), Point(10, 10), 6));
    rtree.insert(Rect(Point(3, 1), Point(4, 2), 7));
    rtree.insert(Rect(Point(4, 7), Point(5, 8), 8)); // this will cause split
    rtree.insert(Rect(Point(6, 3), Point(7, 6), 9));
    rtree.insert(Rect(Point(8, 2), Point(9, 6), 10));

    // remove rect
    Node *root = rtree.getRoot();
    rtree.remove(root, Rect(Point(9, 9), Point(10, 10), 6));
    rtree.remove(root, Rect(Point(8, 2), Point(9, 6), 10));
    rtree.remove(root, Rect(Point(5, 5), Point(6, 6), 4));
    rtree.remove(root, Rect(Point(7, 7), Point(8, 8), 5));

    // traverse the tree
    std::cout << std::endl;
    std::cout << "Traverse the tree:" << std::endl;
    std::vector<int> vec = rtree.traverse(root);

    // search
    std::cout << std::endl;
    std::cout << "Search:" << std::endl;
    std::vector<Rect> result;
    rtree.search(root, Rect(Point(3.5, 1.5), Point(6, 6), 0), result);
    std::cout << result.size() << " valid rectangles: " << std::endl;
    for (int i = 0; i < result.size(); i++) {
        std::cout << result[i] << std::endl;
    }

    auto end_time = std::chrono::high_resolution_clock::now(); // end timer
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    return 0;
}
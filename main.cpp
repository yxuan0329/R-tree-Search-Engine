#include <iostream>
#include <vector>
#include <algorithm>

#include "includes/Node.h"
#include "includes/Rtree.h"


int main(){
    std::cout << "Rtree main function" << std::endl;

    Rtree rtree = Rtree();
    std::cout << "root=" << rtree.getRoot() << std::endl;
    rtree.insert(Rect(Point(0, 0), Point(2, 2), 1));
    rtree.insert(Rect(Point(3, 3), Point(4, 4), 2));


    // insert 3rd rect which is inside r1 and find it's parent
    rtree.insert(Rect(Point(0, 0), Point(1, 1), 3));
    std::cout << "root=" << rtree.getRoot() << std::endl;
    std::cout << "size=" << rtree.getSize() << std::endl;
    std::cout << "root's children size=" << rtree.getRoot()->getChildren().size() << std::endl;
    std::cout << "root's children[0]=" << rtree.getRoot()->getChildren()[0] << std::endl;
    std::cout << "root's children[0] is leaf=" << rtree.getRoot()->getChildren()[0]->isLeaf() << std::endl;
    std::cout << "root's children[1]=" << rtree.getRoot()->getChildren()[1] << std::endl;
    std::cout << "root's children[1] is leaf=" << rtree.getRoot()->getChildren()[1]->isLeaf() << std::endl;
    std::cout << "root's children[0]'s children=" << rtree.getRoot()->getChildren()[0]->getChildren()[0] << std::endl;

    // insert rect
    rtree.insert(Rect(Point(5, 5), Point(6, 6), 4));
    rtree.insert(Rect(Point(7, 7), Point(8, 8), 5));
    rtree.insert(Rect(Point(9, 9), Point(10, 10), 6));
    rtree.insert(Rect(Point(3, 1), Point(4, 2), 7));

    // remove rect
    Node *root = rtree.getRoot();
    rtree.remove(root, Rect(Point(9, 9), Point(10, 10), 6));

    // traverse the tree
    std::cout << std::endl;
    std::cout << "traverse the tree" << std::endl;
    rtree.traverse(root);
    return 0;
}
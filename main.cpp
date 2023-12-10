#include <iostream>
#include <vector>
#include <algorithm>

#include <Node.h>
#include <Rtree.h>


int main(){
    std::cout << "Rtree main function" << std::endl;

    Rtree rtree = Rtree();
    std::cout << "root=" << rtree.getRoot() << std::endl;
    rtree.insert(Rect(Point(0, 0), Point(2, 2), 1));
    std::cout << "root=" << rtree.getRoot() << std::endl;
    std::cout << "size=" << rtree.getSize() << std::endl;
    std::cout << "root's children size=" << rtree.getRoot()->getChildren().size() << std::endl;
    std::cout << "root's children[0]=" << rtree.getRoot()->getChildren()[0] << std::endl;
    std::cout << "root's children[0]'s parent=" << rtree.getRoot()->getChildren()[0]->getParent() << std::endl;

    // insert 2nd rect and find it's parent
    std::cout << std::endl;
    std::cout << "insert 2nd rect and find it's parent" << std::endl;
    rtree.insert(Rect(Point(3, 3), Point(4, 4), 2));
    std::cout << "root=" << rtree.getRoot() << std::endl;
    std::cout << "size=" << rtree.getSize() << std::endl;
    std::cout << "root's children size=" << rtree.getRoot()->getChildren().size() << std::endl;
    std::cout << "root's children[0]=" << rtree.getRoot()->getChildren()[0] << std::endl;
    std::cout << "root's children[0] is leaf=" << rtree.getRoot()->getChildren()[0]->isLeaf() << std::endl;
    std::cout << "root's children[1]=" << rtree.getRoot()->getChildren()[1] << std::endl;
    // std::cout << "root's children[1]'s parent=" << rtree.getRoot()->getChildren()[1]->getParent() << std::endl;

    // insert 3rd rect which is inside r1 and find it's parent
    std::cout << std::endl;
    std::cout << "insert 3rd rect which is inside r1 and find it's parent" << std::endl;
    rtree.insert(Rect(Point(0, 0), Point(1, 1), 3));
    std::cout << "root=" << rtree.getRoot() << std::endl;
    std::cout << "size=" << rtree.getSize() << std::endl;
    std::cout << "root's children size=" << rtree.getRoot()->getChildren().size() << std::endl;
    std::cout << "root's children[0]=" << rtree.getRoot()->getChildren()[0] << std::endl;
    std::cout << "root's children[0] is leaf=" << rtree.getRoot()->getChildren()[0]->isLeaf() << std::endl;
    std::cout << "root's children[1]=" << rtree.getRoot()->getChildren()[1] << std::endl;
    std::cout << "root's children[1] is leaf=" << rtree.getRoot()->getChildren()[1]->isLeaf() << std::endl;
    std::cout << "root's children[0]'s children=" << rtree.getRoot()->getChildren()[0]->getChildren()[0] << std::endl;
    return 0;
}
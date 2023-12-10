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
    rtree.insert(Rect(Point(1, 1), Point(3, 3), 2));
    std::cout << "root=" << rtree.getRoot() << std::endl;
    std::cout << "size=" << rtree.getSize() << std::endl;
    std::cout << "root's children size=" << rtree.getRoot()->getChildren().size() << std::endl;
    std::cout << "root's children[0]=" << rtree.getRoot()->getChildren()[0] << std::endl;
    std::cout << "root's children[0] is leaf=" << rtree.getRoot()->getChildren()[0]->isLeaf() << std::endl;
    std::cout << "root's children[1]=" << rtree.getRoot()->getChildren()[1] << std::endl;
    // std::cout << "root's children[1]'s parent=" << rtree.getRoot()->getChildren()[1]->getParent() << std::endl;

    return 0;
}
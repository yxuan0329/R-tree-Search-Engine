#include <iostream>
#include <vector>

#include <Node.h>
#include <Rtree.h>

// Rtree
Rtree::Rtree() {}

Rtree::~Rtree() {
    // delete this;
}

Rtree::Rtree(Node* root) {
    this->m_root = root;
}

void Rtree::insert(Rect rect) {
    if (this->m_root == nullptr) { // if the tree is empty
        this->m_root = new Node(rect, nullptr, {}, true); // rect, parent, children, isLeaf=true
    } else { // if the tree is not empty
        Node *parent = chooseLeaf(this->m_root, rect);
        parent->insertChild(rect);

        // if the parent has more than m_maxChildren children, then split the parent
        if (parent->getChildren().size() > m_maxChildren) {
            Node *splitNode = splitNewNode(parent);
            adjustTree(parent, splitNode);
        }
    }
    this->m_treeSize ++;
}

void Rtree::remove(Rect rect) {
    //remove the rect from the tree
}

void Rtree::search(Rect rect) {
    // TODO
}

Node *Rtree::chooseLeaf(Node *currNode, Rect rect) {
    // search from root, find the leaf node that has the minimum area enlargement
    // and return the leaf node
    if (currNode->isLeaf()) {
        return currNode;
    } 

    Node *selectedChild = nullptr;
    double maxOverlappedArea = 0.0;

    for (auto *child : currNode->getChildren()) {
        // if overlap of rect and child.area > maxOverlappedArea,
        // then selectedChild = child, 
        // maxOverlappedArea = overlap of rect and child.area
        double overlapArea = getOverlapArea(rect, child->getRect());
        if (overlapArea > maxOverlappedArea) {
            selectedChild = child;
            maxOverlappedArea = overlapArea;
        }
    }

    // if maxOverlappedArea == 0.0, then set currNode as selectedChild,
    // rect will be slpit as a new leaf node
    if (maxOverlappedArea == 0.0) {
        selectedChild = currNode;
    }
    return chooseLeaf(selectedChild, rect);
    
}

double Rtree::getOverlapArea(Rect rect1, Rect rect2) {
    // given two rectangle, calculate the overlap area
    double overlapX = std::max(0.0, std::min(rect1.getUpperRight().getLong(), rect2.getUpperRight().getLong()) - std::max(rect1.getLowerLeft().getLong(), rect2.getLowerLeft().getLong()));
    double overlapY = std::max(0.0, std::min(rect1.getUpperRight().getLat(), rect2.getUpperRight().getLat()) - std::max(rect1.getLowerLeft().getLat(), rect2.getLowerLeft().getLat()));
    double overlapArea = overlapX * overlapY;
    return overlapArea;
}

Node *Rtree::splitNewNode(Node *currNode) {
    // split the currNode into two nodes, and return the new node
    // TODO
    return nullptr;
}

void Rtree::adjustTree(Node *currNode, Node *splitNode) {
    // adjust the tree after spliting the currNode
    // TODO
}
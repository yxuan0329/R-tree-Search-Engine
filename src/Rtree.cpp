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

void Rtree::insert(Rect rect1) {
    if (this->m_root == nullptr) {
        this->m_root = new Node(rect1, nullptr);
    } else {
        this->m_root->insertChild(rect1);
    }
    this->m_treeSize ++;
}

void Rtree::remove(Rect rect) {
    // TODO
}

void Rtree::search(Rect rect) {
    // TODO
}
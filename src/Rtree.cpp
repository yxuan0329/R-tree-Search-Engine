#include <iostream>
#include <vector>

#include "Node.h"
#include "Rtree.h"

// Rtree
Rtree::Rtree() {}

Rtree::~Rtree() {
    // delete this;
}

Rtree::Rtree(Node* root) {
    this->root = root;
}

void Rtree::insert(Rect rect1) {
    if (root == nullptr) {
        root = new Node(rect1, nullptr);
    } else {
        root->insertChild(rect1);
    }
    size++;
}

void Rtree::remove(Rect rect) {
    // TODO
}

void Rtree::search(Rect rect) {
    // TODO
}
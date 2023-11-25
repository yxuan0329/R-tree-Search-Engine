#ifndef RTREE_H
#define RTREE_H

#include "Node.h"

// create a R-tree with a root node
class Rtree {
public:
    Rtree();
    ~Rtree();

    Rtree(Node*);

    const Node* getRoot() const { return root; }

    void insert(Rect);
    void remove(Rect);
    void search(Rect);

private:
    Node* root;
};

#endif
#ifndef R_TREE_H
#define R_TREE_H

#include "node.h"

class Rtree{
public:
    Rtree();
    ~Rtree();

    void build(Node);
    void insert(Node);
    void remove(Node);
    void search(Node);

    bool isEmpty();
    int getHeight();
    int getSize();

private:
    Node* root;
    int height;
    int size;
};



#endif
#ifndef RTREE_H
#define RTREE_H

#include <Node.h>

// create a R-tree with a root node
class Rtree {
public:
    Rtree();
    ~Rtree();

    Rtree(Node*);

    const Node* getRoot() const { return m_root; }
    const int getSize() const { return m_treeSize; }

    void insert(Rect);
    void remove(Rect);
    void search(Rect);

private:
    Node* m_root = nullptr; // the root of tree
    int m_treeSize = 0; // the number of nodes in the tree
};

#endif
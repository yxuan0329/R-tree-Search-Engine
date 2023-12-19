#ifndef RTREE_H
#define RTREE_H

#include "Node.h"
#include <cstddef>
#include <vector>

// create a R-tree with a root node
class Rtree {
public:
    Rtree();
    ~Rtree();

    Rtree(Node*);

    Node* getRoot() const;
    const int getSize() const { return m_treeSize; }
    double getOverlapArea(Rect, Rect);
    void setRoot(Node* root) { this->m_root = root; }

    void insert(Rect);
    void remove(Node *, Rect);
    void search(Rect);
    Node *chooseLeafAsParent(Node*, Rect);
    Node *splitNewNode(Node*);
    void adjustTree(Node*, Node*);
    void clearTree();

    // traverse for debugging
    void traverse(Node*);  
    int getHeight(Node*);  

private:
    Node* m_root; // the root of tree
    int m_treeSize = 0; // the number of nodes in the tree
    size_t m_maxChildren = 4; // the maximum number of children in a node
};

#endif
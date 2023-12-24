#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>   
#include <cstddef>
#include <climits>

#include <../includes/Node.h>
#include <Rtree.h>

// Rtree
Rtree::Rtree() {
    this->m_root = new Node();
    this->m_treeSize = 1;
}

Rtree::Rtree(size_t m, size_t M) {
    this->m_root = new Node();
    this->m_treeSize = 1;
    this->m_maxChildren = M;
    this->m_minChildren = m;
}

Rtree::~Rtree() {
    // delete this;
}

Rtree::Rtree(Node* root) {
    this->m_root = root;
}

Node* Rtree::getRoot() const {
    return this->m_root;
}

void Rtree::insert(Rect rect) {
    // recursively search from root, find the leaf node that has requires minimum area increase
    Node *leaf = chooseLeaf(this->m_root, rect);
    leaf->insertChild(rect);

    // if the leaf has more than m_maxChildren children, then split the leaf
    if (leaf->getChildren().size() > m_maxChildren) {
        Node *splitNode = splitNewNode(leaf);
        adjustTree(leaf, splitNode);
    }
    this->m_treeSize ++;
}

void Rtree::remove(Node *node, Rect rect) {
    // check if the node's children has overlap with rect
    // if yes, then recursively search and delete rect that has overlap with rect
    // if no, then return
    for (auto *child : node->getChildren()) {
        // if child == rect, then remove child from node
        if (child->getRect() == rect) {
            node->removeChild(rect);
            this->m_treeSize --;

            // if no children left, then delete node
            if (node->getChildren().size() == 0) {
                Node *parent = node->getParent();
                parent->removeChild(node->getRect());
            }
        }

        // if child is not leaf, then recursively search
        if (child->isInside(rect, child->getRect())) {
            remove(child, rect);

            // update the rect of node since one of its children is removed
            Rect newRect = node->getRect();
            double llx = INT_MAX, lly = INT_MAX;
            double urx = INT_MIN, ury = INT_MIN;
            for (auto *child : node->getChildren()) {
                Rect childRect = child->getRect();
                llx = std::min(childRect.getLowerLeft().getLong(), llx);
                lly = std::min(childRect.getLowerLeft().getLat(), lly);
                urx = std::max(childRect.getUpperRight().getLong(), urx);
                ury = std::max(childRect.getUpperRight().getLat(), ury);
            }
            newRect = Rect(Point(llx, lly), Point(urx, ury), node->getRect().getId());
            node->setRect(newRect);
        }
    }
}

void Rtree::search(Node *root, Rect rect, std::vector<Rect> &result) {
    // start from the root node

    // If T is not a leaf node:
    // Check all entries E in T for overlap with the search region rect.
    // Recursively search in the subtree for all entries E.
    if (!root->isLeaf()) {
        for (auto *child : root->getChildren()) {
            if (child->isInside(child->getRect(), rect) || child->isOverlap(rect, child->getRect())) {
                search(child, rect, result);
            }
        }
    }

    // If T is a leaf node:
    // Check all entries E in T for overlap with the search region rect.
    // All overlapped entries E are part of the query result.
    if (root->isLeaf()) {
        // check all its rect children
        for (auto *child : root->getChildren()) {
            if (child->isInside(child->getRect(), rect) || child->isOverlap(rect, child->getRect())) {
                result.push_back(child->getRect());
            }
        }
    }
}

Node *Rtree::chooseLeaf(Node *currNode, Rect rect) {
    // search from root, find the leaf node that has requires minimum area increase
    // and return the leaf node
    if (currNode->isLeaf()) {
        return currNode;
    } 

    Node *selectedChild = nullptr;
    double minOverlappedIncrease = (double)INT_MAX;

    // update the rect of currNode itself to include inserted rect
    Rect newRect1 = currNode->getRect();
    double llx1 = std::min(currNode->getRect().getLowerLeft().getLong(), rect.getLowerLeft().getLong());
    double lly1 = std::min(currNode->getRect().getLowerLeft().getLat(), rect.getLowerLeft().getLat());
    double urx1 = std::max(currNode->getRect().getUpperRight().getLong(), rect.getUpperRight().getLong());
    double ury1 = std::max(currNode->getRect().getUpperRight().getLat(), rect.getUpperRight().getLat());
    newRect1 = Rect(Point(llx1, lly1), Point(urx1, ury1), currNode->getRect().getId());
    currNode->setRect(newRect1);


    for (auto *child : currNode->getChildren()) {
        // calculate the area increase if insert rect into child
        // set a new rect if insert rect into child
        Rect possibleChildRect = child->getRect();
        double llx = std::min(possibleChildRect.getLowerLeft().getLong(), rect.getLowerLeft().getLong());
        double lly = std::min(possibleChildRect.getLowerLeft().getLat(), rect.getLowerLeft().getLat());
        double urx = std::max(possibleChildRect.getUpperRight().getLong(), rect.getUpperRight().getLong());
        double ury = std::max(possibleChildRect.getUpperRight().getLat(), rect.getUpperRight().getLat());
        
        possibleChildRect = Rect(Point(llx, lly), Point(urx, ury), 0);

        // calculate the area increase
        double areaIncrease = possibleChildRect.getArea() - child->getRect().getArea();

        // if areaIncrease is smaller than minOverlappedIncrease, then update minOverlappedIncrease and selectedChild
        if (areaIncrease < minOverlappedIncrease) {
            minOverlappedIncrease = areaIncrease;
            selectedChild = child;
        } else if (areaIncrease == minOverlappedIncrease) {
            // if areaIncrease is equal to minOverlappedIncrease, then choose the one with smaller area
            if (possibleChildRect.getArea() < selectedChild->getRect().getArea()) {
                selectedChild = child;
            }
        }
    }

    // Update current rectangle of selectedChild to include rect
    // selectedChild->updateRect(selectedChild, rect);
    Rect newRect = selectedChild->getRect();
    double llx = std::min(selectedChild->getRect().getLowerLeft().getLong(), rect.getLowerLeft().getLong());
    double lly = std::min(selectedChild->getRect().getLowerLeft().getLat(), rect.getLowerLeft().getLat());
    double urx = std::max(selectedChild->getRect().getUpperRight().getLong(), rect.getUpperRight().getLong());
    double ury = std::max(selectedChild->getRect().getUpperRight().getLat(), rect.getUpperRight().getLat());
    newRect = Rect(Point(llx, lly), Point(urx, ury), selectedChild->getRect().getId());
    selectedChild->setRect(newRect);

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

    // sort children by x-coord of lower-left corner, 
    // if tie, then sort by y-coord of lower-left corner
    std::vector<Node*> children = currNode->getChildren();
    std::sort(children.begin(), children.end(), [](Node *a, Node *b) {
        if (a->getRect().getLowerLeft().getLong() == b->getRect().getLowerLeft().getLong()) {
            return a->getRect().getLowerLeft().getLat() < b->getRect().getLowerLeft().getLat();
        }
        return a->getRect().getLowerLeft().getLong() < b->getRect().getLowerLeft().getLong();
    });

    // split the children into two groups
    size_t splitIndex = children.size() / 2; // left side may be more or equal to right side
    std::vector<Node*> leftGroup(children.begin(), children.begin() + splitIndex);
    std::vector<Node*> rightGroup(children.begin() + splitIndex, children.end());

    // according to the rect in leftGroup, find minimum bounding rect
    Rect currRect = currNode->getChildren()[0]->getRect();
    bool currIsLeaf = currNode->isLeaf();
    bool newIsLeaf = currIsLeaf;
    for (auto *child : leftGroup) {
        Rect childRect = child->getRect();
        double llx = std::min(childRect.getLowerLeft().getLong(), currRect.getLowerLeft().getLong());
        double lly = std::min(childRect.getLowerLeft().getLat(), currRect.getLowerLeft().getLat());
        double urx = std::max(childRect.getUpperRight().getLong(), currRect.getUpperRight().getLong());
        double ury = std::max(childRect.getUpperRight().getLat(), currRect.getUpperRight().getLat());
        currRect = Rect(Point(llx, lly), Point(urx, ury), currNode->getRect().getId());
        currIsLeaf = currIsLeaf && child->isLeaf();
    }

    // update rect of currNode and update its children into half as before
    currNode->setRect(currRect);
    currNode->setChildren(leftGroup);

    // according to the rect in rightGroup, find minimum bounding rect
    Rect newRect = rightGroup[0]->getRect();
    for (auto *child : rightGroup) {
        Rect childRect = child->getRect();
        double llx = std::min(childRect.getLowerLeft().getLong(), newRect.getLowerLeft().getLong());
        double lly = std::min(childRect.getLowerLeft().getLat(), newRect.getLowerLeft().getLat());
        double urx = std::max(childRect.getUpperRight().getLong(), newRect.getUpperRight().getLong());
        double ury = std::max(childRect.getUpperRight().getLat(), newRect.getUpperRight().getLat());
        newRect = Rect(Point(llx, lly), Point(urx, ury), 0);

        newIsLeaf = newIsLeaf && child->isLeaf();
    }

    // create new node with the same coordinates as currNode
    Node *newNode = new Node(newRect, currNode->getParent(), rightGroup, newIsLeaf);

    return newNode;
}

void Rtree::adjustTree(Node *currNode, Node *splitNode) {
    // adjust the tree after a split operation

    if (currNode == m_root) {
        // if currNode is root, then create a new root
        // with currNode and splitNode as its children
        Rect newRect = currNode->getRect();
        double llx = std::min(currNode->getRect().getLowerLeft().getLong(), splitNode->getRect().getLowerLeft().getLong());
        double lly = std::min(currNode->getRect().getLowerLeft().getLat(), splitNode->getRect().getLowerLeft().getLat());
        double urx = std::max(currNode->getRect().getUpperRight().getLong(), splitNode->getRect().getUpperRight().getLong());
        double ury = std::max(currNode->getRect().getUpperRight().getLat(), splitNode->getRect().getUpperRight().getLat());
        newRect = Rect(Point(llx, lly), Point(urx, ury), 10);

        Node *newRoot = new Node(newRect, nullptr, {currNode, splitNode}, false);
        currNode->setParent(newRoot);
        splitNode->setParent(newRoot);
        this->m_root = newRoot;
    } else {
        // if currNode is not root, then update the parent of currNode
        // and insert splitNode into the parent
        Node *parent = currNode->getParent();
        parent->insertChild(splitNode);
        splitNode->setParent(parent);

        // if the parent has more than m_maxChildren children, then split the parent
        if (parent->getChildren().size() > m_maxChildren) {
            Node *splitParent = splitNewNode(parent);
            adjustTree(parent, splitParent);
        }
    }
}

void Rtree::clearTree() {
    // clear the tree
    delete this->m_root;
    m_root = nullptr;
}

// traverse in level order and print the tree area
void Rtree::traverse(Node *currNode) {
    std::vector<Node*> queue;
    queue.push_back(currNode);

    while (!queue.empty()) {
        Node *currNode = queue.front();
        queue.erase(queue.begin());
        if (!currNode->isRect()) std::cout << "Node: ";
        else std::cout << "Rect: ";

        std::cout << "(" << currNode->getRect().getLowerLeft().getLong() << ", " << currNode->getRect().getLowerLeft().getLat() << "), (" << currNode->getRect().getUpperRight().getLong() << ", " << currNode->getRect().getUpperRight().getLat() << ") size=" << currNode->getChildren().size() << " isLeaf=" << currNode->isLeaf() << std::endl;

        if (!currNode->isRect()) {
            for (auto *child : currNode->getChildren()) {
                queue.push_back(child);
            }
        }
    }
}

int Rtree::getHeight(Node *currNode) {
    // return the height of the tree
    if (currNode == nullptr) {
        return 0;
    }

    int h = 0;
    for (auto *child : currNode->getChildren()) {
        h = std::max(h, 1 + getHeight(child));
    }

    return h;
}

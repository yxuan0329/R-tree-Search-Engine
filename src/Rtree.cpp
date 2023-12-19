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
    Node *parent = chooseLeafAsParent(this->m_root, rect);
    parent->insertChild(rect);

    // if the parent has more than m_maxChildren children, then split the parent
    if (parent->getChildren().size() > m_maxChildren) {
        Node *splitNode = splitNewNode(parent);
        adjustTree(parent, splitNode);
    }
    this->m_treeSize ++;
}

void Rtree::remove(Rect rect) {
    //remove the rect from the tree
}

void Rtree::search(Rect rect) {
    // TODO
}

Node *Rtree::chooseLeafAsParent(Node *currNode, Rect rect) {
    // search from root, find the leaf node that has the maximum overlap area with rect
    // and return the leaf node
    if (currNode->isLeaf()) {
        return currNode;
    } 

    Node *selectedChild = nullptr;
    double maxOverlappedArea = 0.0;

    for (auto *child : currNode->getChildren()) {
        // if overlap of rect and child.area > maxOverlappedArea,
        // then selectedChild = child, 
        // maxOverlappedArea = overlap area of rect and child.area
        double overlapArea = getOverlapArea(rect, child->getRect());
        if (overlapArea > maxOverlappedArea) {
            selectedChild = child;
            maxOverlappedArea = overlapArea;
        }
    }

    // if maxOverlappedArea == 0.0, means there is no overlap between rect and currNode,
    // then set currNode as selectedChild,
    // rect will be split as a new leaf node
    if (maxOverlappedArea == 0.0) {
        return currNode;
    }

    // if maxOverlappedArea > 0.0, means there is overlap between rect and currNode,
    //  then update current rectangle of selectedChild to include rect
    // selectedChild->updateRect(selectedChild, rect);
    Rect newRect = selectedChild->getRect();
    double llx = std::min(selectedChild->getRect().getLowerLeft().getLong(), rect.getLowerLeft().getLong());
    double lly = std::min(selectedChild->getRect().getLowerLeft().getLat(), rect.getLowerLeft().getLat());
    double urx = std::max(selectedChild->getRect().getUpperRight().getLong(), rect.getUpperRight().getLong());
    double ury = std::max(selectedChild->getRect().getUpperRight().getLat(), rect.getUpperRight().getLat());
    newRect = Rect(Point(llx, lly), Point(urx, ury), 0);
    selectedChild->setRect(newRect);

    return chooseLeafAsParent(selectedChild, rect);
    
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

    // sort children by x-coord of lower-left corner
    std::vector<Node*> children = currNode->getChildren();
    std::sort(children.begin(), children.end(), [](Node *a, Node *b) {
        return a->getRect().getLowerLeft().getLong() < b->getRect().getLowerLeft().getLong();
    });

    // split the children into two groups
    size_t splitIndex = children.size() / 2;
    std::vector<Node*> leftGroup(children.begin(), children.begin() + splitIndex);
    std::vector<Node*> rightGroup(children.begin() + splitIndex, children.end());

    // according to the rect in leftGroup, find minimum bounding rect
    Rect currRect = currNode->getRect();
    bool currIsLeaf = true;
    for (auto *child : leftGroup) {
        Rect childRect = child->getRect();
        double llx = std::min(childRect.getLowerLeft().getLong(), currRect.getLowerLeft().getLong());
        double lly = std::min(childRect.getLowerLeft().getLat(), currRect.getLowerLeft().getLat());
        double urx = std::max(childRect.getUpperRight().getLong(), currRect.getUpperRight().getLong());
        double ury = std::max(childRect.getUpperRight().getLat(), currRect.getUpperRight().getLat());
        currRect = Rect(Point(llx, lly), Point(urx, ury), 0);

        currIsLeaf = currIsLeaf && child->isLeaf();
    }

    // update rect of currNode and update its children into half as before
    currNode->setRect(currRect);
    currNode->setChildren(leftGroup);

    // according to the rect in rightGroup, find minimum bounding rect
    Rect newRect = rightGroup[0]->getRect();
    bool newIsLeaf = true;
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
    Node *newNode = new Node(newRect, nullptr, rightGroup, newIsLeaf);

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
        newRect = Rect(Point(llx, lly), Point(urx, ury), 0);

        Node *newRoot = new Node(newRect, nullptr, {currNode, splitNode}, false);
        currNode->setParent(newRoot);
        splitNode->setParent(newRoot);
        this->m_root = newRoot;
    } else {
        // if currNode is not root, then update the parent of currNode
        // and insert splitNode into the parent
        Node *parent = currNode->getParent();
        parent->removeChild(currNode->getRect());
        parent->insertChild(splitNode->getRect());

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

        std::cout << "Node: (" << currNode->getRect().getLowerLeft().getLong() << ", " << currNode->getRect().getLowerLeft().getLat() << "), (" << currNode->getRect().getUpperRight().getLong() << ", " << currNode->getRect().getUpperRight().getLat() << ") size=" << currNode->getChildren().size() << std::endl;

        if (!currNode->isLeaf()) {
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

#include <iostream>
#include <algorithm>
#include <vector>
#include <../includes/Node.h>

// Point
Point::Point() {}

Point::~Point() {
    // delete this;
}

Point::Point(double longtitude, double latitude) {
    this->m_longtitude = longtitude;
    this->m_latitude = latitude;
    this->m_id = 0;
}

Point::Point(double longtitude, double latitude, int id) {
    this->m_longtitude = longtitude;
    this->m_latitude = latitude;
    this->m_id = id;
}

bool Point::operator==(const Point& p) const {
    return (this->m_longtitude == p.m_longtitude) && (this->m_latitude == p.m_latitude) && (this->m_id == p.m_id);
}

bool Point::operator!=(const Point& p) const {
    return !(*this == p);
}


// Rect
Rect::Rect() {}

Rect::~Rect() {
    // delete this;
}

Rect::Rect(Point lower, Point upper, int id) {
    this->m_ll = lower;
    this->m_ur = upper;
    this->m_id = id;
}

bool Rect::operator==(const Rect& r) const {
    return (this->m_ll == r.m_ll) && (this->m_ur == r.m_ur) && (this->m_id == r.m_id);
}

bool Rect::operator!=(const Rect& r) const {
    return !(*this == r);
}

// Node
Node::Node() { // create a single new leaf node in the tree
    // this->m_rect = Rect(Point(0, 0), Point(0, 0), 0);
    this->m_parent = nullptr;
    this->m_children = {};
}

Node::~Node() {
    for (auto child : m_children) {
        delete child;
    }
    delete this;
}

Node::Node(Rect rect, Node* parent=nullptr, std::vector<Node*> children={}, bool isLeaf=false) {
    this->m_rect = rect;
    this->m_parent = parent;
    this->m_children = children;
}

void Node::insertChild(Rect rect) {
    Node *newNode = new Node(rect);
    m_children.push_back(new Node(rect));
    newNode->setParent(this);
}

void Node::insertChild(Node* node) {
    m_children.push_back(node);
    node->setParent(this);
}

void Node::removeChild(Rect rect) {
    // remove rect in children
    this->m_children.erase(std::remove_if(this->m_children.begin(), this->m_children.end(), [rect](Node* n) { return n->getRect() == rect; }), this->m_children.end());
}

bool Node::operator==(const Node& n) const {
    return (this->m_rect == n.m_rect) && (this->m_children == n.m_children) && (this->m_parent == n.m_parent);
}

bool Node::operator!=(const Node& n) const {
    return !(*this == n);
}

const Node* Node::getChild(int index) const {
    return m_children[index];
}

const std::vector<Node*>& Node::getChildren() const {
    return m_children;
}

void Node::setChildren(std::vector<Node*> children) {
    this->m_children = children;
}

Node* Node::getParent() const {
    return m_parent;
}

void Node::setParent(Node* parent) {
    this->m_parent = parent;
}

void Node::setRect(Rect rect) {
    this->m_rect = rect;
}

void updateRect(Node* currNode, Rect rect) {
    // set a new rect that combine original and new rect
    Rect newRect = currNode->getRect();
    double llx = std::min(currNode->getRect().getLowerLeft().getLong(), rect.getLowerLeft().getLong());
    double lly = std::min(currNode->getRect().getLowerLeft().getLat(), rect.getLowerLeft().getLat());
    double urx = std::max(currNode->getRect().getUpperRight().getLong(), rect.getUpperRight().getLong());
    double ury = std::max(currNode->getRect().getUpperRight().getLat(), rect.getUpperRight().getLat());
    newRect = Rect(Point(llx, lly), Point(urx, ury), currNode->getRect().getId());
    currNode->setRect(newRect);
}

bool Node::isInside(Rect r1, Rect r2) {
    // check if r1 is inside r2
    return (r1.getLowerLeft().getLong() >= r2.getLowerLeft().getLong()) && (r1.getLowerLeft().getLat() >= r2.getLowerLeft().getLat()) && (r1.getUpperRight().getLong() <= r2.getUpperRight().getLong()) && (r1.getUpperRight().getLat() <= r2.getUpperRight().getLat());
}

bool Node::isOverlap(Rect r1, Rect r2) {
    // make sure r1 is the left rect and r2 is the right rect
    if (r1.getLowerLeft().getLong() > r2.getLowerLeft().getLong()) {
        std::swap(r1, r2);
    }
    // check if r1 is overlap with r2
    return (r1.getUpperRight().getLong() >= r2.getLowerLeft().getLong()) && (r1.getUpperRight().getLat() >= r2.getLowerLeft().getLat()) && (r1.getLowerLeft().getLong() <= r2.getUpperRight().getLong()) && (r1.getLowerLeft().getLat() <= r2.getUpperRight().getLat());    
}

bool Node::isLeaf() const {
    // this node is a leaf node if it has no children
    if (m_children.empty()) return true;

    // check if all children are rect nodes, 
    // if so, this node is a leaf node
    for (auto child : m_children) {
        if (!child->isRect()) return false;
    }
    return true;
}

bool Node::isRect() const {
    // if this node contains empty children, it is a rect node
    return m_children.empty();
}
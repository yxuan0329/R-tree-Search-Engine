#include <iostream>
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
Node::Node() {}

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
    this->m_isLeafNode = isLeaf;
}

void Node::insertChild(Rect rect) {
    m_children.push_back(new Node(rect));
}

void Node::removeChild(Rect rect) {
    // TODO
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

bool Node::isLeaf() const {
    return m_children.empty();
}
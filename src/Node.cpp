#include <iostream>
#include "Node.h"

// Point
Point::Point() {}

Point::~Point() {
    delete this;
}

Point::Point(double longtitude, double latitude) {
    this->longtitude = longtitude;
    this->latitude = latitude;
    this->id = 0;
}

Point::Point(double longtitude, double latitude, int id) {
    this->longtitude = longtitude;
    this->latitude = latitude;
    this->id = id;
}

bool Point::operator==(const Point& p) const {
    return (this->longtitude == p.longtitude) && (this->latitude == p.latitude) && (this->id == p.id);
}

bool Point::operator!=(const Point& p) const {
    return !(*this == p);
}


// Rect
Rect::Rect() {}

Rect::~Rect() {
    delete this;
}

Rect::Rect(Point lower, Point upper, int id) {
    this->lower = lower;
    this->upper = upper;
    this->id = id;
}

bool Rect::operator==(const Rect& r) const {
    return (this->lower == r.lower) && (this->upper == r.upper) && (this->id == r.id);
}

bool Rect::operator!=(const Rect& r) const {
    return !(*this == r);
}

// Node
Node::Node() {}

Node::~Node() {
    for (auto child : children) {
        delete child;
    }
    delete this;
}

Node::Node(Rect rect, Node* parent) {
    this->rect = rect;
    this->parent = parent;
}

bool Node::operator==(const Node& n) const {
    return (this->rect == n.rect) && (this->children == n.children) && (this->parent == n.parent);
}

bool Node::operator!=(const Node& n) const {
    return !(*this == n);
}

const Node* Node::getChild(int index) const {
    return children[index];
}

bool Node::isLeaf() const {
    return children.empty();
}
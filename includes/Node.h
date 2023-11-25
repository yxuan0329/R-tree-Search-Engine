#ifndef NODE_H
#define NODE_H

#include <vector>

// define point with logitude, latitude, 2 points make a Rect for bounding box
class Point {
public:
    Point();
    ~Point();

    Point(double, double); // longtitude, latitude
    Point(double, double, int);

    bool operator==(const Point&) const;
    bool operator!=(const Point&) const;

    const double& getLong() const { return longtitude; }
    const double& getLat() const { return latitude; }

private:    
    double longtitude, latitude;
    int id;
};

// define a bounding box with 2 points, left lower and right upper
class Rect {
public:
    Rect();
    ~Rect();

    Rect(Point, Point, int);

    bool operator==(const Rect&) const;
    bool operator!=(const Rect&) const;

    const Point& getLower() const { return lower; }
    const Point& getUpper() const { return upper; } 

private:
    Point lower;
    Point upper;
    int id;
};

// define a node with a bounding box for itself
// and a list of children nodes, representing the children bounding box that will 
// overlap with this node.
class Node {
public:
    Node();
    ~Node();

    Node(Rect, Node*);

    bool operator==(const Node&) const;
    bool operator!=(const Node&) const;

    const Rect& getRect() const { return rect; }
    const Node* getChild(int) const;

    bool isLeaf() const;

private:
    Rect rect;
    std::vector<Node*> children;
    Node* parent;
    bool isLeafNode;
};

#endif

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

    const double& getLong() const { return m_longtitude; }
    const double& getLat() const { return m_latitude; }

private:    
    double m_longtitude, m_latitude;
    int m_id;
};

// define a bounding box with 2 points, left lower and right upper
class Rect {
public:
    Rect();
    ~Rect();

    Rect(Point, Point, int);

    bool operator==(const Rect&) const;
    bool operator!=(const Rect&) const;

    const Point& getLowerLeft() const { return m_ll; }
    const Point& getUpperRight() const { return m_ur; } 
    double getArea() const { return (m_ur.getLong() - m_ll.getLong()) * (m_ur.getLat() - m_ll.getLat()); }

private:
    Point m_ll;
    Point m_ur;
    int m_id;
};

// define a node with a bounding box for itself
// and a list of children nodes, representing the children bounding box that
// overlap with this node.
class Node {
public:
    Node();
    ~Node();

    Node(Rect, Node*, std::vector<Node*>, bool);

    void insertChild(Rect);

    bool operator==(const Node&) const;
    bool operator!=(const Node&) const;

    const Rect& getRect() const { return m_rect; }
    const Node* getChild(int) const;
    const std::vector<Node*>& getChildren() const;

    bool isLeaf() const;

private:
    Rect m_rect;
    std::vector<Node*> m_children;
    Node* m_parent;
    bool m_isLeafNode;
    int maxChildrenSize = 4;
};

#endif

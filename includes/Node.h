#ifndef NODE_H
#define NODE_H

#include <vector>

// define point with logitude, latitude, 
// 2 points(lower-left, upper-right) will make a Rect for bounding box
class Point {
public:
    Point();
    ~Point();

    Point(double, double); // longtitude, latitude
    Point(double, double, int); // longtitude, latitude, id

    bool operator==(const Point&) const;
    bool operator!=(const Point&) const;

    const double& getLong() const { return m_longtitude; }
    const double& getLat() const { return m_latitude; }

private:    
    double m_longtitude; // x-coord of point
    double m_latitude; // y-coord of point
    int m_id; // id of point
};

// define a bounding box with 2 points, lower-left and upper-right
class Rect {
public:
    Rect();
    ~Rect();

    Rect(Point, Point, int); // lower-left, upper-right, id

    bool operator==(const Rect&) const;
    bool operator!=(const Rect&) const;

    const Point& getLowerLeft() const { return m_ll; }
    const Point& getUpperRight() const { return m_ur; } 
    double getArea() const { return (m_ur.getLong() - m_ll.getLong()) * (m_ur.getLat() - m_ll.getLat()); }

private:
    Point m_ll; // lower-left point
    Point m_ur; // upper-right point
    int m_id; // id of rect
};

// define a node with a bounding box for itself
// and a list of children nodes, representing the children bounding box that
// overlap with this node.
class Node {
public:
    Node();
    ~Node();

    Node(Rect, Node*, std::vector<Node*>, bool); // rect, parent, children, isLeaf

    void insertChild(Rect);
    void removeChild(Rect);

    bool operator==(const Node&) const;
    bool operator!=(const Node&) const;

    const Rect& getRect() const { return m_rect; }
    const Node* getChild(int) const;
    Node* getParent() const;
    const std::vector<Node*>& getChildren() const;
    void setChildren(std::vector<Node*>);
    void setParent(Node*);
    void setRect(Rect);

    bool isLeaf() const;

private:
    Rect m_rect; // bounding box of this node
    std::vector<Node*> m_children; // children nodes
    Node* m_parent; // parent node
    bool m_isLeafNode; // is leaf node or not
    int maxChildrenSize = 4; // the maximum number of children in a node
};

#endif

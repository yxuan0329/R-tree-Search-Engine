#ifndef NODE_H
#define NODE_H

#include <ostream>
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
    // operator <<
    friend std::ostream& operator<<(std::ostream& os, const Rect& rect) {
        os << "Rect(" << rect.m_ll.getLong() << ", " << rect.m_ll.getLat() << ", " << rect.m_ur.getLong() << ", " << rect.m_ur.getLat() << ", " << rect.m_id << ")";
        return os;
    }


    const Point& getLowerLeft() const { return m_ll; }
    const Point& getUpperRight() const { return m_ur; } 
    double getArea() const { return (m_ur.getLong() - m_ll.getLong()) * (m_ur.getLat() - m_ll.getLat()); }
    int getId() const { return m_id; }

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
    void insertChild(Node*);
    void removeChild(Rect);

    bool operator==(const Node&) const;
    bool operator!=(const Node&) const;
    
    // operator <<
    friend std::ostream& operator<<(std::ostream& os, const Node& node) {
        os << "Node(" << node.m_rect.getLowerLeft().getLong() << ", " << node.m_rect.getLowerLeft().getLat() << ", " << node.m_rect.getUpperRight().getLong() << ", " << node.m_rect.getUpperRight().getLat() << ", " << node.m_rect.getArea() << ")";
        return os;
    }

    const Rect& getRect() const { return m_rect; }
    const Node* getChild(int) const;
    Node* getParent() const;
    const std::vector<Node*>& getChildren() const;
    void setChildren(std::vector<Node*>);
    void setParent(Node*);
    void setRect(Rect);
    void setIsLeaf(bool);
    void updateRect(Node*, Rect);
    bool isInside(Rect, Rect);
    bool isOverlap(Rect, Rect);

    bool isLeaf() const;
    bool isRect() const;

private:
    Rect m_rect; // bounding box of this node
    std::vector<Node*> m_children; // children nodes
    Node* m_parent; // parent node
};

#endif

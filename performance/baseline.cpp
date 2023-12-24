#include <iostream>
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;


typedef bg::model::point<double, 2, bg::cs::cartesian> Point;
typedef bg::model::box<Point> Rect;
typedef bgi::rtree<Rect, bgi::quadratic<16>> Rtree;


class Node {
public:
    Rtree rtree;

    Node(int min_child, int max_child) : rtree(min_child, max_child) {}

    Rtree& getRtree() {
        return rtree;
    }
};

int main() {
    Node root(2, 4);

    // insert
    root.getRtree().insert(Rect(Point(0, 0), Point(2, 2)));
    root.getRtree().insert(Rect(Point(3, 3), Point(4, 4)));
    root.getRtree().insert(Rect(Point(0, 0), Point(1, 1)));
    root.getRtree().insert(Rect(Point(5, 5), Point(6, 6)));
    root.getRtree().insert(Rect(Point(7, 7), Point(8, 8)));
    root.getRtree().insert(Rect(Point(9, 9), Point(10, 10)));
    root.getRtree().insert(Rect(Point(3, 1), Point(4, 2)));
    root.getRtree().insert(Rect(Point(4, 7), Point(5, 8)));
    root.getRtree().insert(Rect(Point(6, 3), Point(7, 6)));
    root.getRtree().insert(Rect(Point(8, 2), Point(9, 6)));

    // delete
    root.getRtree().remove(Rect(Point(9, 9), Point(10, 10)));
    root.getRtree().remove(Rect(Point(8, 2), Point(9, 6)));
    root.getRtree().remove(Rect(Point(5, 5), Point(6, 6)));
    root.getRtree().remove(Rect(Point(7, 7), Point(8, 8)));

    // traverse
    std::cout << "Traverse the tree:" << std::endl;
    std::vector<Rect> vec;
    for (const auto& value : root.getRtree()) {
        vec.push_back(value);
    }

    // search
    std::cout << "Search:" << std::endl;
    std::vector<Rect> result;
    root.getRtree().query(bgi::intersects(Rect(Point(3.5, 1.5), Point(6, 6))), std::back_inserter(result));

    std::cout << result.size() << " valid rectangles: " << std::endl;
    for (const auto& rect : result) {
        std::cout << rect << std::endl;
    }

    return 0;
}

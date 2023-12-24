#include <Node.h>
#include <Rtree.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <vector>

namespace py = pybind11;

PYBIND11_MODULE(_Rtree, m) {
    m.doc() = "Rtree implementation";
    py::class_<Point>(m, "Point")
        .def(py::init<>())
        .def(py::init<double, double>())
        .def(py::init<double, double, int>())
        .def("getLong", &Point::getLong)
        .def("getLat", &Point::getLat)
        .def("__eq__", &Point::operator==)
        .def("__neq__", &Point::operator!=);

    py::class_<Rect>(m, "Rect")
        .def(py::init<>())
        .def(py::init<Point, Point, int>())
        .def("getLower", &Rect::getLowerLeft)
        .def("getUpper", &Rect::getUpperRight)
        .def("__eq__", &Rect::operator==)
        .def("__neq__", &Rect::operator!=);

    py::class_<Node>(m, "Node")
        .def(py::init<>())
        .def(py::init<Rect, Node*, std::vector<Node*>, bool>())
        .def("getRect", &Node::getRect)
        .def("getChild", &Node::getChild)
        .def("getChildren", &Node::getChildren)
        .def("getParent", &Node::getParent)
        .def("isLeaf", &Node::isLeaf)
        .def("__eq__", &Node::operator==)
        .def("__neq__", &Node::operator!=);

    py::class_<RtreeLib::Rtree>(m, "Rtree")
        .def(py::init<>())
        .def(py::init<Node*>())
        .def("getRoot", &RtreeLib::Rtree::getRoot, py::return_value_policy::reference)
        .def("getSize", &RtreeLib::Rtree::getSize)
        .def("insert", &RtreeLib::Rtree::insert)
        .def("remove", &RtreeLib::Rtree::remove)
        .def("search", &RtreeLib::Rtree::search)
        .def("chooseLeaf", &RtreeLib::Rtree::chooseLeaf)
        .def("getOverlapArea", &RtreeLib::Rtree::getOverlapArea)
        .def("clearTree", &RtreeLib::Rtree::clearTree)
        .def("traverse", &RtreeLib::Rtree::traverse)
        .def("getHeight", &RtreeLib::Rtree::getHeight);
}
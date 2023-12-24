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

    py::class_<Rtree>(m, "Rtree")
        .def(py::init<>())
        .def(py::init<Node*>())
        .def("getRoot", &Rtree::getRoot, py::return_value_policy::reference)
        .def("getSize", &Rtree::getSize)
        .def("insert", &Rtree::insert)
        .def("remove", &Rtree::remove)
        .def("search", &Rtree::search)
        .def("chooseLeaf", &Rtree::chooseLeaf)
        .def("getOverlapArea", &Rtree::getOverlapArea)
        .def("splitNewNode", &Rtree::splitNewNode)
        .def("adjustTree", &Rtree::adjustTree)
        .def("clearTree", &Rtree::clearTree)
        .def("traverse", &Rtree::traverse)
        .def("getHeight", &Rtree::getHeight);
}
#include <Node.h>
#include <Rtree.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(_myRtree, m) {
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
        .def(py::init<Rect, Node*>())
        .def("getRect", &Node::getRect)
        .def("getChild", &Node::getChild)
        .def("isLeaf", &Node::isLeaf)
        .def("__eq__", &Node::operator==)
        .def("__neq__", &Node::operator!=);

    py::class_<Rtree>(m, "Rtree")
        .def(py::init<>())
        .def(py::init<Node*>())
        .def("getRoot", &Rtree::getRoot)
        .def("getSize", &Rtree::getSize)
        .def("insert", &Rtree::insert)
        .def("remove", &Rtree::remove)
        .def("search", &Rtree::search);
}
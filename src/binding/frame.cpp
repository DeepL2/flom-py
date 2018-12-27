#include <flom/range.hpp>

#include <pybind11/operators.h>
#include <pybind11/pybind11.h>

#include "declarations.hpp"

namespace flom_py {

namespace py = pybind11;

void define_frame(py::module &m) {
  py::class_<flom::Frame>(m, "Frame")
      .def_readwrite("positions", &flom::Frame::positions)
      .def_readwrite("effectors", &flom::Frame::effectors)
      .def("joint_names", &flom::Frame::joint_names)
      .def("effector_names", &flom::Frame::effector_names)
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self += py::self)
      .def(py::self + py::self)
      .def(py::self -= py::self)
      .def(py::self - py::self)
      .def(py::self *= double())
      .def(py::self * double())
      .def(py::self *= float())
      .def(py::self * float());
}

} // namespace flom_py

#include <flom/interpolation.hpp>

#include <pybind11/pybind11.h>

#include "declarations.hpp"

namespace flom_py {

namespace py = pybind11;

void define_interpolate(py::module &m) {
  m.def(
      "interpolate",
      py::overload_cast<double, flom::Location const &, flom::Location const &>(
          &flom::interpolate));
  m.def(
      "interpolate",
      py::overload_cast<double, flom::Rotation const &, flom::Rotation const &>(
          &flom::interpolate));
  m.def(
      "interpolate",
      py::overload_cast<double, flom::Effector const &, flom::Effector const &>(
          &flom::interpolate));
  m.def("interpolate",
        py::overload_cast<double, flom::Frame const &, flom::Frame const &>(
            &flom::interpolate));
  m.def("interpolate",
        py::overload_cast<double, double, double>(&flom::interpolate));
}

} // namespace flom_py

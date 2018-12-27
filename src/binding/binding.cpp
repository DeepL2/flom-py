#include <flom/flom.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <string>

#include "declarations.hpp"

namespace py = pybind11;

PYBIND11_MODULE(flom, m) {
  m.doc() = "flom: Motion exchange format";

  m.def("load", [](std::string const &filename) {
    std::ifstream f(filename, std::ios::binary);
    return flom::Motion::load(f);
  });
  m.def("load_json", [](std::string const &filename) {
    std::ifstream f(filename);
    return flom::Motion::load_json(f);
  });
  m.def("load_json_string", &flom::Motion::load_json_string);

  flom_py::define_interpolate(m);
  flom_py::define_enums(m);

  flom_py::define_motion(m);
  flom_py::define_ranges(m);

  flom_py::define_frame(m);

  flom_py::define_effector(m);
}

#include <flom/range.hpp>

#include <pybind11/pybind11.h>

#include "declarations.hpp"

namespace flom_py {

namespace py = pybind11;

void define_ranges(py::module &m) {
  py::class_<flom::KeyRange<std::string>>(m, "KeyRange")
      .def("__iter__", [](flom::KeyRange<std::string> &range) {
        return py::make_iterator(range.begin(), range.end());
      });
}

} // namespace flom_py

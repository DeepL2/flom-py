#include <flom/flom.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <string>

namespace py = pybind11;

PYBIND11_MODULE(flom, m) {
  m.doc() = "flom: Motion exchange format";
  m.def("load", [](std::string const& filename) {
      std::ifstream f(filename, std::ios::binary);
      return flom::Motion::load(f);
    });
  m.def("load_json", [](std::string const& filename) {
      std::ifstream f(filename);
      return flom::Motion::load_json(f);
    });

  py::class_<flom::Motion>(m, "Motion")
    .def(py::init<std::string>(), py::arg("model"))
    .def("dump", [](flom::Motion const& motion, std::string const& filename) {
        std::ofstream f(filename, std::ios::binary);
        motion.dump(f);
      })
    .def("dump_json", [](flom::Motion const& motion, std::string const& filename) {
        std::ofstream f(filename);
        motion.dump_json(f);
      });
}

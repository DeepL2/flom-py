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
      })
    .def("frame_at", &flom::Motion::frame_at);

  py::class_<flom::Frame>(m, "Frame")
    .def_readwrite("positions", &flom::Frame::positions)
    .def_readwrite("effectors", &flom::Frame::effectors);

  py::class_<flom::Effector>(m, "Effector")
    .def_readwrite("location", &flom::Effector::location)
    .def_readwrite("rotation", &flom::Effector::rotation);

  py::class_<flom::Location>(m, "Location")
    .def_readwrite("weight", &flom::Location::weight)
    .def_readwrite("vec", &flom::Location::vec);

  py::class_<flom::Rotation>(m, "Rotation")
    .def_readwrite("weight", &flom::Rotation::weight)
    .def_readwrite("quat", &flom::Rotation::quat);
}

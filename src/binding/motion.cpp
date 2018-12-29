#include <flom/motion.hpp>
#include <flom/range.hpp>

#include <pybind11/operators.h>
#include <pybind11/pybind11.h>

#include "declarations.hpp"

namespace flom_py {

namespace py = pybind11;

void define_motion(py::module &m) {
  py::class_<flom::EffectorType>(m, "EffectorType")
      .def_readwrite("location", &flom::EffectorType::location)
      .def_readwrite("rotation", &flom::EffectorType::rotation);

  m.def("load", [](std::string const &filename) {
    std::ifstream f(filename, std::ios::binary);
    return flom::Motion::load(f);
  });
  m.def("load_json", [](std::string const &filename) {
    std::ifstream f(filename);
    return flom::Motion::load_json(f);
  });
  m.def("load_json_string", &flom::Motion::load_json_string);

  py::class_<flom::Motion>(m, "Motion")
      .def(py::init<std::string>(), py::arg("model"))
      .def("dump",
           [](flom::Motion const &motion, std::string const &filename) {
             std::ofstream f(filename, std::ios::binary);
             motion.dump(f);
           })
      .def("dump_json",
           [](flom::Motion const &motion, std::string const &filename) {
             std::ofstream f(filename);
             motion.dump_json(f);
           })
      .def("dump_json_string", &flom::Motion::dump_json_string)
      .def("frame_at", &flom::Motion::frame_at)
      .def("frames", &flom::Motion::frames)
      .def("loop", &flom::Motion::loop)
      .def("set_loop", &flom::Motion::set_loop)
      .def("model_id", &flom::Motion::model_id)
      .def("set_model_id", &flom::Motion::set_model_id)
      .def("effector_type", &flom::Motion::effector_type)
      .def("set_effector_type", &flom::Motion::set_effector_type)
      .def("is_in_range_at", &flom::Motion::is_in_range_at)
      .def("length", &flom::Motion::length)
      .def("joint_names", &flom::Motion::joint_names)
      .def("effector_names", &flom::Motion::effector_names)
      .def(py::self == py::self);
}

} // namespace flom_py

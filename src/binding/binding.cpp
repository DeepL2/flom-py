#include <flom/flom.hpp>

#include <pybind11/numpy.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <boost/qvm/quat_access.hpp>
#include <boost/qvm/vec_access.hpp>

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

  py::enum_<flom::LoopType>(m, "LoopType")
      .value("None", flom::LoopType::None)
      .value("Wrap", flom::LoopType::Wrap);

  py::enum_<flom::CoordinateSystem>(m, "CoordinateSystem")
      .value("World", flom::CoordinateSystem::World)
      .value("Local", flom::CoordinateSystem::Local);

  py::class_<flom::EffectorType>(m, "EffectorType")
      .def_readwrite("location", &flom::EffectorType::location)
      .def_readwrite("rotation", &flom::EffectorType::rotation);

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

  py::class_<flom::KeyRange<std::string>>(m, "KeyRange")
      .def("__iter__", [](flom::KeyRange<std::string> &range) {
        return py::make_iterator(range.begin(), range.end());
      });

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

  py::class_<flom::Effector>(m, "Effector")
      .def_readwrite("location", &flom::Effector::location)
      .def_readwrite("rotation", &flom::Effector::rotation)
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

  py::class_<flom::Location>(m, "Location")
      .def_readwrite("weight", &flom::Location::weight)
      .def_property("vec",
                    [](flom::Location const &l) {
                      py::array_t<double> ret(3);
                      auto *data = ret.mutable_data();
                      data[0] = boost::qvm::X(l.vec);
                      data[1] = boost::qvm::Y(l.vec);
                      data[2] = boost::qvm::Z(l.vec);
                      return ret;
                    },
                    [](flom::Location &l, py::array_t<double> const &ary) {
                      auto *data = ary.data();
                      boost::qvm::X(l.vec) = data[0];
                      boost::qvm::Y(l.vec) = data[1];
                      boost::qvm::Z(l.vec) = data[2];
                    })
      .def(py::self == py::self);

  py::class_<flom::Rotation>(m, "Rotation")
      .def_readwrite("weight", &flom::Rotation::weight)
      .def_property("quat",
                    [](flom::Rotation const &l) {
                      py::array_t<double> ret(4);
                      auto *data = ret.mutable_data();
                      data[0] = boost::qvm::S(l.quat);
                      data[1] = boost::qvm::X(l.quat);
                      data[2] = boost::qvm::Y(l.quat);
                      data[3] = boost::qvm::Z(l.quat);
                      return ret;
                    },
                    [](flom::Rotation &l, py::array_t<double> const &ary) {
                      auto *data = ary.data();
                      boost::qvm::S(l.quat) = data[0];
                      boost::qvm::X(l.quat) = data[1];
                      boost::qvm::Y(l.quat) = data[2];
                      boost::qvm::Z(l.quat) = data[3];
                    })
      .def(py::self == py::self);
}

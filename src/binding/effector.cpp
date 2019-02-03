//
// Copyright 2018 coord.e
//
// This file is part of flom-py.
//
// flom-py is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// flom-py is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with flom-py.  If not, see <http://www.gnu.org/licenses/>.
//

#include <flom/effector.hpp>

#include <pybind11/numpy.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "declarations.hpp"

namespace flom_py {

namespace py = pybind11;

void define_effector(py::module &m) {
  py::class_<flom::EffectorDifference>(m, "EffectorDifference")
      .def(py::init<const flom::Effector &, const flom::Effector &>())
      .def_property_readonly(
          "location",
          [](const flom::EffectorDifference &eff) { return eff.location(); })
      .def_property_readonly(
          "rotation",
          [](const flom::EffectorDifference &eff) { return eff.rotation(); })
      .def("is_compatible", &flom::EffectorDifference::is_compatible)
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self + py::self)
      .def(py::self += py::self)
      .def(py::self * std::size_t())
      .def(py::self *= std::size_t());

  py::class_<flom::Effector>(m, "Effector")
      .def(py::init<>())
      .def(py::init<const std::optional<flom::Location> &,
                    const std::optional<flom::Rotation> &>())
      .def_property("location",
                    [](const flom::Effector &eff) { return eff.location(); },
                    &flom::Effector::set_location)
      .def_property("rotation",
                    [](const flom::Effector &eff) { return eff.rotation(); },
                    &flom::Effector::set_rotation)
      .def("clear_location", &flom::Effector::clear_location)
      .def("clear_rotation", &flom::Effector::clear_rotation)
      .def("new_compatible_effector", &flom::Effector::new_compatible_effector)
      .def("is_compatible", py::overload_cast<const flom::Effector &>(
                                &flom::Effector::is_compatible, py::const_))
      .def("is_compatible", py::overload_cast<const flom::EffectorDifference &>(
                                &flom::Effector::is_compatible, py::const_))
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self - py::self)
      .def("__add__",
           [](const flom::Effector &e, const flom::EffectorDifference &diff) {
             return e + diff;
           })
      .def("__iadd__",
           [](flom::Effector &e, const flom::EffectorDifference &diff) {
             return e += diff;
           });

  py::class_<flom::Location>(m, "Location")
      .def(py::init<>())
      .def(py::init([](const py::array_t<double> &ary) {
        auto *data = ary.data();
        return flom::Location{data[0], data[1], data[2]};
      }))
      .def_property("vector",
                    [](flom::Location const &l) {
                      py::array_t<double> ret(3);
                      auto *data = ret.mutable_data();
                      auto const &vec = l.vector();
                      data[0] = vec.x();
                      data[1] = vec.y();
                      data[2] = vec.z();
                      return ret;
                    },
                    [](flom::Location &l, py::array_t<double> const &ary) {
                      auto *data = ary.data();
                      l.set_xyz(data[0], data[1], data[2]);
                    })
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self + py::self)
      .def(py::self += py::self)
      .def(py::self - py::self)
      .def(py::self -= py::self)
      .def(py::self * std::size_t())
      .def(py::self *= std::size_t());

  py::class_<flom::Rotation>(m, "Rotation")
      .def(py::init<>())
      .def(py::init([](const py::array_t<double> &ary) {
        auto *data = ary.data();
        return flom::Rotation{data[0], data[1], data[2], data[3]};
      }))
      .def_property("quaternion",
                    [](flom::Rotation const &l) {
                      py::array_t<double> ret(4);
                      auto *data = ret.mutable_data();
                      auto const &quat = l.quaternion();
                      data[0] = quat.w();
                      data[1] = quat.x();
                      data[2] = quat.y();
                      data[3] = quat.z();
                      return ret;
                    },
                    [](flom::Rotation &l, py::array_t<double> const &ary) {
                      auto *data = ary.data();
                      l.set_wxyz(data[0], data[1], data[2], data[3]);
                    })
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self + py::self)
      .def(py::self += py::self)
      .def(py::self - py::self)
      .def(py::self -= py::self)
      .def(py::self * std::size_t())
      .def(py::self *= std::size_t());
}

} // namespace flom_py

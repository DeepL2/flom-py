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

#include <boost/qvm/quat_access.hpp>
#include <boost/qvm/vec_access.hpp>

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
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self + py::self)
      .def(py::self += py::self)
      .def(py::self * std::size_t())
      .def(py::self *= std::size_t());

  py::class_<flom::Effector>(m, "Effector")
      .def(py::init<>())
      .def_property("location",
                    [](const flom::Effector &eff) { return eff.location(); },
                    &flom::Effector::set_location)
      .def_property("rotation",
                    [](const flom::Effector &eff) { return eff.rotation(); },
                    &flom::Effector::set_rotation)
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self - py::self);

  py::class_<flom::Location>(m, "Location")
      .def_property("vector",
                    [](flom::Location const &l) {
                      py::array_t<double> ret(3);
                      auto *data = ret.mutable_data();
                      auto const &vec = l.vector();
                      data[0] = boost::qvm::X(vec);
                      data[1] = boost::qvm::Y(vec);
                      data[2] = boost::qvm::Z(vec);
                      return ret;
                    },
                    [](flom::Location &l, py::array_t<double> const &ary) {
                      auto *data = ary.data();
                      flom::Location::value_type vec;
                      boost::qvm::X(vec) = data[0];
                      boost::qvm::Y(vec) = data[1];
                      boost::qvm::Z(vec) = data[2];
                      l.set_vector(vec);
                    })
      .def(py::self == py::self);

  py::class_<flom::Rotation>(m, "Rotation")
      .def_property("quaternion",
                    [](flom::Rotation const &l) {
                      py::array_t<double> ret(4);
                      auto *data = ret.mutable_data();
                      auto const &quat = l.quaternion();
                      data[0] = boost::qvm::S(quat);
                      data[1] = boost::qvm::X(quat);
                      data[2] = boost::qvm::Y(quat);
                      data[3] = boost::qvm::Z(quat);
                      return ret;
                    },
                    [](flom::Rotation &l, py::array_t<double> const &ary) {
                      auto *data = ary.data();
                      flom::Rotation::value_type quat;
                      boost::qvm::S(quat) = data[0];
                      boost::qvm::X(quat) = data[1];
                      boost::qvm::Y(quat) = data[2];
                      boost::qvm::Z(quat) = data[3];
                      l.set_quaternion(quat);
                    })
      .def(py::self == py::self);
}

} // namespace flom_py

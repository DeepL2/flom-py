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

#include <flom/range.hpp>

#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "declarations.hpp"

namespace flom_py {

namespace py = pybind11;

void define_frame(py::module &m) {
  py::class_<flom::FrameDifference>(m, "FrameDifference")
      .def(py::init<const flom::Frame &, const flom::Frame &>())
      .def_property_readonly(
          "positions",
          [](const flom::FrameDifference &frame) { return frame.positions(); })
      .def_property_readonly(
          "effectors",
          [](const flom::FrameDifference &frame) { return frame.effectors(); })
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self + py::self)
      .def(py::self += py::self)
      .def(py::self * std::size_t())
      .def(py::self *= std::size_t());

  py::class_<flom::Frame>(m, "Frame")
      .def(py::init<>())
      .def(py::init<const std::unordered_map<std::string, double> &,
                    const std::unordered_map<std::string, flom::Effector> &>())
      .def_property("positions",
                    [](const flom::Frame &frame) { return frame.positions(); },
                    &flom::Frame::set_positions)
      .def_property("effectors",
                    [](const flom::Frame &frame) { return frame.effectors(); },
                    &flom::Frame::set_effectors)
      .def("joint_names", &flom::Frame::joint_names)
      .def("effector_names", &flom::Frame::effector_names)
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self - py::self);
}

} // namespace flom_py

#include <flom/motion.hpp>

#include <pybind11/pybind11.h>

#include "declarations.hpp"

namespace flom_py {

namespace py = pybind11;

void define_enums(py::module &m) {
  py::enum_<flom::LoopType>(m, "LoopType")
      .value("None", flom::LoopType::None)
      .value("Wrap", flom::LoopType::Wrap);

  py::enum_<flom::CoordinateSystem>(m, "CoordinateSystem")
      .value("World", flom::CoordinateSystem::World)
      .value("Local", flom::CoordinateSystem::Local);
}

} // namespace flom_py

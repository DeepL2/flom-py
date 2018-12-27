#ifndef FLOM_PY_DECLARATIONS_HPP
#define FLOM_PY_DECLARATIONS_HPP

#include <pybind11/pybind11.h>

namespace flom_py {

void define_interpolate(pybind11::module&);
void define_enums(pybind11::module&);

}

#endif

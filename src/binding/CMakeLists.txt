cmake_minimum_required(VERSION 3.7)

pybind11_add_module(flom MODULE binding.cpp interpolate.cpp enums.cpp motion.cpp effector.cpp ranges.cpp frame.cpp)
target_link_libraries(flom PRIVATE -lflom)
enable_clang_format(flom)

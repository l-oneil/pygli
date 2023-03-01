#include <vector>
#include <cstdint>
#include <iostream>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <gli/gli.hpp>


namespace py = pybind11;


py::array load(std::string &filepath) {
    gli::texture tex = gli::load(filepath);
    assert(!tex.empty());
    auto format = tex.format();
    auto extent = tex.extent();
    std::vector<int> shape = {extent.y, extent.x};
    py::array arr;

    switch(format) {
        case gli::FORMAT_RGBA8_UNORM_PACK8:
            shape.push_back(4); // 4 channels
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;
        default:
            throw std::invalid_argument("Unrecognised Format");
    }

    return arr;
}


PYBIND11_MODULE(pygli, m) {
    m.doc() = "Wrapper for reading gli textures";
    m.def("load", &load, "Load texture file and return as NumPy array");
}

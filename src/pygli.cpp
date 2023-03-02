#include <vector>
#include <cstdint>
#include <iostream>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <gli/gli.hpp>

#include "float_convert.hpp"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;


py::array_t<float> half_to_float(py::array_t<uint16_t> half_arr) {
      py::buffer_info in = half_arr.request();

      /* No pointer is passed, so NumPy will allocate the buffer */
      auto out_arr = py::array_t<float>(in.shape);
      py::buffer_info out = out_arr.request();

      uint16_t *in_ptr = static_cast<uint16_t *>(in.ptr);
      float *out_ptr = static_cast<float *>(out.ptr);

      size_t length = 1;
      for (size_t n = 0; n < in.ndim; n++)
            length *= in.shape[n];
      
      for (size_t x = 0; x < length; x++)
            out_ptr[x] = half_to_float(in_ptr[x]);
      
      return out_arr;
}


py::array load(std::string &filepath) {
    gli::texture tex = gli::load(filepath);
    assert(!tex.empty());
    auto format = tex.format();
    auto extent = tex.extent();
    std::vector<int> shape = {extent.y, extent.x};
    py::array arr;
    py::array_t<std::uint16_t> half_arr;

    switch(format) {
      case gli::FORMAT_R8_UNORM_PACK8:
            shape.push_back(1);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;
      case gli::FORMAT_R8_SNORM_PACK8:
            shape.push_back(1);
            arr = py::array_t<std::int8_t>(shape, (std::int8_t *) tex.data());
            break;
      case gli::FORMAT_R8_USCALED_PACK8:
            shape.push_back(1);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;
      case gli::FORMAT_R8_SSCALED_PACK8:
            shape.push_back(1);
            arr = py::array_t<std::int8_t>(shape, (std::int8_t *) tex.data());
            break;
      case gli::FORMAT_R8_UINT_PACK8:
            shape.push_back(1);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;
      case gli::FORMAT_R8_SINT_PACK8:
            shape.push_back(1);
            arr = py::array_t<std::int8_t>(shape, (std::int8_t *) tex.data());
            break;
      case gli::FORMAT_R8_SRGB_PACK8:
            shape.push_back(1);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;

      case gli::FORMAT_RG8_UNORM_PACK8:
            shape.push_back(2);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;
      case gli::FORMAT_RG8_SNORM_PACK8:
            shape.push_back(2);
            arr = py::array_t<std::int8_t>(shape, (std::int8_t *) tex.data());
            break;
      case gli::FORMAT_RG8_USCALED_PACK8:
            shape.push_back(2);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;
      case gli::FORMAT_RG8_SSCALED_PACK8:
            shape.push_back(2);
            arr = py::array_t<std::int8_t>(shape, (std::int8_t *) tex.data());
            break;
      case gli::FORMAT_RG8_UINT_PACK8:
            shape.push_back(2);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;
      case gli::FORMAT_RG8_SINT_PACK8:
            shape.push_back(2);
            arr = py::array_t<std::int8_t>(shape, (std::int8_t *) tex.data());
            break;
      case gli::FORMAT_RG8_SRGB_PACK8:
            shape.push_back(2);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;

      case gli::FORMAT_RGB8_UNORM_PACK8:
            shape.push_back(3);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;
      case gli::FORMAT_RGB8_SNORM_PACK8:
            shape.push_back(3);
            arr = py::array_t<std::int8_t>(shape, (std::int8_t *) tex.data());
            break;
      case gli::FORMAT_RGB8_USCALED_PACK8:
            shape.push_back(3);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;
      case gli::FORMAT_RGB8_SSCALED_PACK8:
            shape.push_back(3);
            arr = py::array_t<std::int8_t>(shape, (std::int8_t *) tex.data());
            break;
      case gli::FORMAT_RGB8_UINT_PACK8:
            shape.push_back(3);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;
      case gli::FORMAT_RGB8_SINT_PACK8:
            shape.push_back(3);
            arr = py::array_t<std::int8_t>(shape, (std::int8_t *) tex.data());
            break;
      case gli::FORMAT_RGB8_SRGB_PACK8:
            shape.push_back(3);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;

      case gli::FORMAT_BGR8_UNORM_PACK8:
            shape.push_back(3);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;
      case gli::FORMAT_BGR8_SNORM_PACK8:
            shape.push_back(3);
            arr = py::array_t<std::int8_t>(shape, (std::int8_t *) tex.data());
            break;
      case gli::FORMAT_BGR8_USCALED_PACK8:
            shape.push_back(3);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;
      case gli::FORMAT_BGR8_SSCALED_PACK8:
            shape.push_back(3);
            arr = py::array_t<std::int8_t>(shape, (std::int8_t *) tex.data());
            break;
      case gli::FORMAT_BGR8_UINT_PACK8:
            shape.push_back(3);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;
      case gli::FORMAT_BGR8_SINT_PACK8:
            shape.push_back(3);
            arr = py::array_t<std::int8_t>(shape, (std::int8_t *) tex.data());
            break;
      case gli::FORMAT_BGR8_SRGB_PACK8:
            shape.push_back(3);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;

      case gli::FORMAT_RGBA8_UNORM_PACK8:
            shape.push_back(4);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;
      case gli::FORMAT_RGBA8_SNORM_PACK8:
            shape.push_back(4);
            arr = py::array_t<std::int8_t>(shape, (std::int8_t *) tex.data());
            break;
      case gli::FORMAT_RGBA8_USCALED_PACK8:
            shape.push_back(4);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;
      case gli::FORMAT_RGBA8_SSCALED_PACK8:
            shape.push_back(4);
            arr = py::array_t<std::int8_t>(shape, (std::int8_t *) tex.data());
            break;
      case gli::FORMAT_RGBA8_UINT_PACK8:
            shape.push_back(4);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;
      case gli::FORMAT_RGBA8_SINT_PACK8:
            shape.push_back(4);
            arr = py::array_t<std::int8_t>(shape, (std::int8_t *) tex.data());
            break;
      case gli::FORMAT_RGBA8_SRGB_PACK8:
            shape.push_back(4);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;

      case gli::FORMAT_RGBA8_UNORM_PACK32:
            shape.push_back(4);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;
      case gli::FORMAT_RGBA8_SNORM_PACK32:
            shape.push_back(4);
            arr = py::array_t<std::int8_t>(shape, (std::int8_t *) tex.data());
            break;
      case gli::FORMAT_RGBA8_USCALED_PACK32:
            shape.push_back(4);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;
      case gli::FORMAT_RGBA8_SSCALED_PACK32:
            shape.push_back(4);
            arr = py::array_t<std::int8_t>(shape, (std::int8_t *) tex.data());
            break;
      case gli::FORMAT_RGBA8_UINT_PACK32:
            shape.push_back(4);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;
      case gli::FORMAT_RGBA8_SINT_PACK32:
            shape.push_back(4);
            arr = py::array_t<std::int8_t>(shape, (std::int8_t *) tex.data());
            break;
      case gli::FORMAT_RGBA8_SRGB_PACK32:
            shape.push_back(4);
            arr = py::array_t<std::uint8_t>(shape, (std::uint8_t *) tex.data());
            break;

      case gli::FORMAT_R16_UNORM_PACK16:
            shape.push_back(1);
            arr = py::array_t<std::uint16_t>(shape, (std::uint16_t *) tex.data());
            break;
      case gli::FORMAT_R16_SNORM_PACK16:
            shape.push_back(1);
            arr = py::array_t<std::int16_t>(shape, (std::int16_t *) tex.data());
            break;
      case gli::FORMAT_R16_USCALED_PACK16:
            shape.push_back(1);
            arr = py::array_t<std::uint16_t>(shape, (std::uint16_t *) tex.data());
            break;
      case gli::FORMAT_R16_SSCALED_PACK16:
            shape.push_back(1);
            arr = py::array_t<std::int16_t>(shape, (std::int16_t *) tex.data());
            break;
      case gli::FORMAT_R16_UINT_PACK16:
            shape.push_back(1);
            arr = py::array_t<std::uint16_t>(shape, (std::uint16_t *) tex.data());
            break;
      case gli::FORMAT_R16_SINT_PACK16:
            shape.push_back(1);
            arr = py::array_t<std::int16_t>(shape, (std::int16_t *) tex.data());
            break;
      case gli::FORMAT_R16_SFLOAT_PACK16:
            shape.push_back(1);
            half_arr = py::array_t<std::uint16_t>(shape, (std::uint16_t *) tex.data());
            arr = half_to_float(half_arr);
            break;

      case gli::FORMAT_RG16_UNORM_PACK16:
            shape.push_back(2);
            arr = py::array_t<std::uint16_t>(shape, (std::uint16_t *) tex.data());
            break;
      case gli::FORMAT_RG16_SNORM_PACK16:
            shape.push_back(2);
            arr = py::array_t<std::int16_t>(shape, (std::int16_t *) tex.data());
            break;
      case gli::FORMAT_RG16_USCALED_PACK16:
            shape.push_back(2);
            arr = py::array_t<std::uint16_t>(shape,(std::uint16_t *) tex.data());
            break;
      case gli::FORMAT_RG16_SSCALED_PACK16:
            shape.push_back(2);
            arr = py::array_t<std::int16_t>(shape, (std::int16_t *) tex.data());
            break;
      case gli::FORMAT_RG16_UINT_PACK16:
            shape.push_back(2);
            arr = py::array_t<std::uint16_t>(shape, (std::uint16_t *) tex.data());
            break;
      case gli::FORMAT_RG16_SINT_PACK16:
            shape.push_back(2);
            arr = py::array_t<std::int16_t>(shape, (std::int16_t *) tex.data());
            break;
      case gli::FORMAT_RG16_SFLOAT_PACK16:
            shape.push_back(2);
            half_arr = py::array_t<std::uint16_t>(shape, (std::uint16_t *) tex.data());
            arr = half_to_float(half_arr);
            break;

      case gli::FORMAT_RGB16_UNORM_PACK16:
            shape.push_back(3);
            arr = py::array_t<std::uint16_t>(shape, (std::uint16_t *) tex.data());
            break;
      case gli::FORMAT_RGB16_SNORM_PACK16:
            shape.push_back(3);
            arr = py::array_t<std::int16_t>(shape, (std::int16_t *) tex.data());
            break;
      case gli::FORMAT_RGB16_USCALED_PACK16:
            shape.push_back(3);
            arr = py::array_t<std::uint16_t>(shape, (std::uint16_t *) tex.data());
            break;
      case gli::FORMAT_RGB16_SSCALED_PACK16:
            shape.push_back(3);
            arr = py::array_t<std::int16_t>(shape, (std::int16_t *) tex.data());
            break;
      case gli::FORMAT_RGB16_UINT_PACK16:
            shape.push_back(3);
            arr = py::array_t<std::uint16_t>(shape, (std::uint16_t *) tex.data());
            break;
      case gli::FORMAT_RGB16_SINT_PACK16:
            shape.push_back(3);
            arr = py::array_t<std::int16_t>(shape, (std::int16_t *) tex.data());
            break;
      case gli::FORMAT_RGB16_SFLOAT_PACK16:
            shape.push_back(3);
            half_arr = py::array_t<std::uint16_t>(shape, (std::uint16_t *) tex.data());
            arr = half_to_float(half_arr);
            break;

      case gli::FORMAT_RGBA16_UNORM_PACK16:
            shape.push_back(4);
            arr = py::array_t<std::uint16_t>(shape, (std::uint16_t *) tex.data());
            break;
      case gli::FORMAT_RGBA16_SNORM_PACK16:
            shape.push_back(4);
            arr = py::array_t<std::int16_t>(shape, (std::int16_t *) tex.data());
            break;
      case gli::FORMAT_RGBA16_USCALED_PACK16:
            shape.push_back(4);
            arr = py::array_t<std::uint16_t>(shape, (std::uint16_t *) tex.data());
            break;
      case gli::FORMAT_RGBA16_SSCALED_PACK16:
            shape.push_back(4);
            arr = py::array_t<std::int16_t>(shape, (std::int16_t *) tex.data());
            break;
      case gli::FORMAT_RGBA16_UINT_PACK16:
            shape.push_back(4);
            arr = py::array_t<std::uint16_t>(shape, (std::uint16_t *) tex.data());
            break;
      case gli::FORMAT_RGBA16_SINT_PACK16:
            shape.push_back(4);
            arr = py::array_t<std::int16_t>(shape, (std::int16_t *) tex.data());
            break;
      case gli::FORMAT_RGBA16_SFLOAT_PACK16:
            shape.push_back(4);
            half_arr = py::array_t<std::uint16_t>(shape, (std::uint16_t *) tex.data());
            arr = half_to_float(half_arr);
            break;

      case gli::FORMAT_R32_UINT_PACK32:
            shape.push_back(1);
            arr = py::array_t<std::uint32_t>(shape, (std::uint32_t *) tex.data());
            break;
      case gli::FORMAT_R32_SINT_PACK32:
            shape.push_back(1);
            arr = py::array_t<std::int32_t>(shape, (std::int32_t *) tex.data());
            break;
      case gli::FORMAT_R32_SFLOAT_PACK32:
            shape.push_back(1);
            arr = py::array_t<float>(shape, (float *) tex.data());
            break;

      case gli::FORMAT_RG32_UINT_PACK32:
            shape.push_back(2);
            arr = py::array_t<std::uint32_t>(shape, (std::uint32_t *) tex.data());
            break;
      case gli::FORMAT_RG32_SINT_PACK32:
            shape.push_back(2);
            arr = py::array_t<std::int32_t>(shape, (std::int32_t *) tex.data());
            break;
      case gli::FORMAT_RG32_SFLOAT_PACK32:
            shape.push_back(2);
            arr = py::array_t<float>(shape, (float *) tex.data());
            break;

      case gli::FORMAT_RGB32_UINT_PACK32:
            shape.push_back(3);
            arr = py::array_t<std::uint32_t>(shape, (std::uint32_t *) tex.data());
            break;
      case gli::FORMAT_RGB32_SINT_PACK32:
            shape.push_back(3);
            arr = py::array_t<std::int32_t>(shape, (std::int32_t *) tex.data());
            break;
      case gli::FORMAT_RGB32_SFLOAT_PACK32:
            shape.push_back(3);
            arr = py::array_t<float>(shape, (float *) tex.data());
            break;

      case gli::FORMAT_RGBA32_UINT_PACK32:
            shape.push_back(4);
            arr = py::array_t<std::uint32_t>(shape, (std::uint32_t *) tex.data());
            break;
      case gli::FORMAT_RGBA32_SINT_PACK32:
            shape.push_back(4);
            arr = py::array_t<std::int32_t>(shape, (std::int32_t *) tex.data());
            break;
      case gli::FORMAT_RGBA32_SFLOAT_PACK32:
            shape.push_back(4);
            arr = py::array_t<float>(shape, (float *) tex.data());
            break;

      case gli::FORMAT_R64_UINT_PACK64:
            shape.push_back(1);
            arr = py::array_t<std::uint64_t>(shape, (std::uint64_t *) tex.data());
            break;
      case gli::FORMAT_R64_SINT_PACK64:
            shape.push_back(1);
            arr = py::array_t<std::int64_t>(shape, (std::int64_t *) tex.data());
            break;
      case gli::FORMAT_R64_SFLOAT_PACK64:
            shape.push_back(1);
            arr = py::array_t<double>(shape, (double *) tex.data());
            break;

      case gli::FORMAT_RG64_UINT_PACK64:
            shape.push_back(2);
            arr = py::array_t<std::uint64_t>(shape, (std::uint64_t *) tex.data());
            break;
      case gli::FORMAT_RG64_SINT_PACK64:
            shape.push_back(2);
            arr = py::array_t<std::int64_t>(shape, (std::int64_t *) tex.data());
            break;
      case gli::FORMAT_RG64_SFLOAT_PACK64:
            shape.push_back(2);
            arr = py::array_t<double>(shape, (double *) tex.data());
            break;

      case gli::FORMAT_RGB64_UINT_PACK64:
            shape.push_back(3);
            arr = py::array_t<std::uint64_t>(shape, (std::uint64_t *) tex.data());
            break;
      case gli::FORMAT_RGB64_SINT_PACK64:
            shape.push_back(3);
            arr = py::array_t<std::int64_t>(shape, (std::int64_t *) tex.data());
            break;
      case gli::FORMAT_RGB64_SFLOAT_PACK64:
            shape.push_back(3);
            arr = py::array_t<double>(shape, (double *) tex.data());
            break;

      case gli::FORMAT_RGBA64_UINT_PACK64:
            shape.push_back(4);
            arr = py::array_t<std::uint64_t>(shape, (std::uint64_t *) tex.data());
            break;
      case gli::FORMAT_RGBA64_SINT_PACK64:
            shape.push_back(4);
            arr = py::array_t<std::int64_t>(shape, (std::int64_t *) tex.data());
            break;
      case gli::FORMAT_RGBA64_SFLOAT_PACK64:
            shape.push_back(4);
            arr = py::array_t<double>(shape, (double *) tex.data());
            break;

      //TODO:
      // FORMAT_RG11B10_UFLOAT_PACK32,
      // FORMAT_RGB9E5_UFLOAT_PACK32,
      // FORMAT_D16_UNORM_PACK16,
      // FORMAT_D24_UNORM_PACK32,
      // FORMAT_D32_SFLOAT_PACK32,
      // FORMAT_S8_UINT_PACK8,
      // FORMAT_D16_UNORM_S8_UINT_PACK32,
      // FORMAT_D24_UNORM_S8_UINT_PACK32,
      // FORMAT_D32_SFLOAT_S8_UINT_PACK64

        default:
            throw std::invalid_argument("Unrecognised Format");
    }

    return arr;
}


PYBIND11_MODULE(_core, m) {
    m.doc() = "Wrapper for reading gli textures";
    m.def("load", &load, "Load texture file and return as NumPy array");
#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}

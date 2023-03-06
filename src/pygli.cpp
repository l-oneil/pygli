#include <vector>
#include <cstdint>
#include <iostream>
#include <fstream>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <gli/gli.hpp>
#include "gli/type.hpp"

#include "float_convert.hpp"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;


inline bool file_exists (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}


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
    if (!file_exists(filepath)){
        throw std::invalid_argument("File doesn't exist");
    }
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
            throw std::invalid_argument("Unrecognised Load Format");
    }

    return arr;
}


template <typename T>
void write_texel(void *ptr, gli::texture &tex, const gli::extent3d &coord, const size_t idx) {
    const T *texel = reinterpret_cast<T *>(ptr);
    tex.store<T>(coord, 0, 0, 0, texel[idx]);
}


bool save(std::string filepath, py::array array, gli::format format) {
    py::buffer_info buf = array.request();
    if (buf.ndim != 3)
        throw std::runtime_error("Number of dimensions must be 3");
    
    // Create Texture 
    gli::extent3d ext = {buf.shape[1], buf.shape[0], 1};
    gli::texture tex = gli::texture(gli::TARGET_3D, format, ext, 1, 1, 1);

    // Populate Texture 
    //TODO: move switch-case out of the inner-loop
    //TODO: Fix writing 1-channel - seems to be broken
    for (size_t y = 0; y < array.shape(0); y++) {
        for (size_t x = 0; x < array.shape(1); x++) {
            const gli::extent3d coord(x, y, 0);
            const size_t idx = y * array.shape(1) + x;
            switch(format){
                case gli::FORMAT_R8_UNORM_PACK8:
                    write_texel<glm::u8>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_R8_SNORM_PACK8:
                    write_texel<glm::u8>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_R8_USCALED_PACK8:
                    write_texel<glm::u8>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_R8_SSCALED_PACK8:
                    write_texel<std::uint8_t>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_R8_UINT_PACK8:
                    write_texel<glm::u8>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_R8_SINT_PACK8:
                    write_texel<glm::u8>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_R8_SRGB_PACK8:
                    write_texel<glm::u8>(buf.ptr, tex, coord, idx);
                    break;

                case gli::FORMAT_RG8_UNORM_PACK8:
                    write_texel<glm::u8vec2>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RG8_SNORM_PACK8:
                    write_texel<glm::u8vec2>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RG8_USCALED_PACK8:
                    write_texel<glm::u8vec2>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RG8_SSCALED_PACK8:
                    write_texel<glm::u8vec2>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RG8_UINT_PACK8:
                    write_texel<glm::u8vec2>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RG8_SINT_PACK8:
                    write_texel<glm::u8vec2>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RG8_SRGB_PACK8:
                    write_texel<glm::u8vec2>(buf.ptr, tex, coord, idx);
                    break;

                case gli::FORMAT_RGB8_UNORM_PACK8:
                    write_texel<glm::u8vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGB8_SNORM_PACK8:
                    write_texel<glm::u8vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGB8_USCALED_PACK8:
                    write_texel<glm::u8vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGB8_SSCALED_PACK8:
                    write_texel<glm::u8vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGB8_UINT_PACK8:
                    write_texel<glm::u8vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGB8_SINT_PACK8:
                    write_texel<glm::u8vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGB8_SRGB_PACK8:
                    write_texel<glm::u8vec3>(buf.ptr, tex, coord, idx);
                    break;

                case gli::FORMAT_BGR8_UNORM_PACK8:
                    write_texel<glm::u8vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_BGR8_SNORM_PACK8:
                    write_texel<glm::u8vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_BGR8_USCALED_PACK8:
                    write_texel<glm::u8vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_BGR8_SSCALED_PACK8:
                    write_texel<glm::u8vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_BGR8_UINT_PACK8:
                    write_texel<glm::u8vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_BGR8_SINT_PACK8:
                    write_texel<glm::u8vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_BGR8_SRGB_PACK8:
                    write_texel<glm::u8vec3>(buf.ptr, tex, coord, idx);
                    break;

                case gli::FORMAT_RGBA8_UNORM_PACK8:
                    write_texel<glm::u8vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA8_SNORM_PACK8:
                    write_texel<glm::u8vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA8_USCALED_PACK8:
                    write_texel<glm::u8vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA8_SSCALED_PACK8:
                    write_texel<glm::u8vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA8_UINT_PACK8:
                    write_texel<glm::u8vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA8_SINT_PACK8:
                    write_texel<glm::u8vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA8_SRGB_PACK8:
                    write_texel<glm::u8vec4>(buf.ptr, tex, coord, idx);
                    break;

                case gli::FORMAT_RGBA8_UNORM_PACK32:
                    write_texel<glm::u8vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA8_SNORM_PACK32:
                    write_texel<glm::u8vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA8_USCALED_PACK32:
                    write_texel<glm::u8vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA8_SSCALED_PACK32:
                    write_texel<glm::u8vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA8_UINT_PACK32:
                    write_texel<glm::u8vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA8_SINT_PACK32:
                    write_texel<glm::u8vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA8_SRGB_PACK32:
                    write_texel<glm::u8vec4>(buf.ptr, tex, coord, idx);
                    break;

                case gli::FORMAT_R16_UNORM_PACK16:
                    write_texel<glm::u16>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_R16_SNORM_PACK16:
                    write_texel<glm::u16>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_R16_USCALED_PACK16:
                    write_texel<glm::u16>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_R16_SSCALED_PACK16:
                    write_texel<glm::u16>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_R16_UINT_PACK16:
                    write_texel<glm::u16>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_R16_SINT_PACK16:
                    write_texel<glm::u16>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_R16_SFLOAT_PACK16:
                    write_texel<glm::u16>(buf.ptr, tex, coord, idx);
                    break;

                case gli::FORMAT_RG16_UNORM_PACK16:
                    write_texel<glm::u16vec2>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RG16_SNORM_PACK16:
                    write_texel<glm::u16vec2>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RG16_USCALED_PACK16:
                    write_texel<glm::u16vec2>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RG16_SSCALED_PACK16:
                    write_texel<glm::u16vec2>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RG16_UINT_PACK16:
                    write_texel<glm::u16vec2>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RG16_SINT_PACK16:
                    write_texel<glm::u16vec2>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RG16_SFLOAT_PACK16:
                    write_texel<glm::u16vec2>(buf.ptr, tex, coord, idx);
                    break;

                case gli::FORMAT_RGB16_UNORM_PACK16:
                    write_texel<glm::u16vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGB16_SNORM_PACK16:
                    write_texel<glm::u16vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGB16_USCALED_PACK16:
                    write_texel<glm::u16vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGB16_SSCALED_PACK16:
                    write_texel<glm::u16vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGB16_UINT_PACK16:
                    write_texel<glm::u16vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGB16_SINT_PACK16:
                    write_texel<glm::u16vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGB16_SFLOAT_PACK16:
                    write_texel<glm::u16vec3>(buf.ptr, tex, coord, idx);
                    break;

                case gli::FORMAT_RGBA16_UNORM_PACK16:
                    write_texel<glm::u16vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA16_SNORM_PACK16:
                    write_texel<glm::u16vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA16_USCALED_PACK16:
                    write_texel<glm::u16vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA16_SSCALED_PACK16:
                    write_texel<glm::u16vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA16_UINT_PACK16:
                    write_texel<glm::u16vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA16_SINT_PACK16:
                    write_texel<glm::u16vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA16_SFLOAT_PACK16:
                    write_texel<glm::u16vec4>(buf.ptr, tex, coord, idx);
                    break;

                case gli::FORMAT_R32_UINT_PACK32:
                    write_texel<glm::u32>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_R32_SINT_PACK32:
                    write_texel<glm::u32>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_R32_SFLOAT_PACK32:
                    write_texel<glm::u32>(buf.ptr, tex, coord, idx);
                    break;

                case gli::FORMAT_RG32_UINT_PACK32:
                    write_texel<glm::u32vec2>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RG32_SINT_PACK32:
                    write_texel<glm::u32vec2>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RG32_SFLOAT_PACK32:
                    write_texel<glm::u32vec2>(buf.ptr, tex, coord, idx);
                    break;

                case gli::FORMAT_RGB32_UINT_PACK32:
                    write_texel<glm::u32vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGB32_SINT_PACK32:
                    write_texel<glm::u32vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGB32_SFLOAT_PACK32:
                    write_texel<glm::u32vec3>(buf.ptr, tex, coord, idx);
                    break;

                case gli::FORMAT_RGBA32_UINT_PACK32:
                    write_texel<glm::u32vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA32_SINT_PACK32:
                    write_texel<glm::u32vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA32_SFLOAT_PACK32:
                    write_texel<glm::u32vec4>(buf.ptr, tex, coord, idx);
                    break;

                case gli::FORMAT_R64_UINT_PACK64:
                    write_texel<glm::u64>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_R64_SINT_PACK64:
                    write_texel<glm::u64>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_R64_SFLOAT_PACK64:
                    write_texel<glm::u64>(buf.ptr, tex, coord, idx);
                    break;

                case gli::FORMAT_RG64_UINT_PACK64:
                    write_texel<glm::u64vec2>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RG64_SINT_PACK64:
                    write_texel<glm::u64vec2>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RG64_SFLOAT_PACK64:
                    write_texel<glm::u64vec2>(buf.ptr, tex, coord, idx);
                    break;

                case gli::FORMAT_RGB64_UINT_PACK64:
                    write_texel<glm::u64vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGB64_SINT_PACK64:
                    write_texel<glm::u64vec3>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGB64_SFLOAT_PACK64:
                    write_texel<glm::u64vec3>(buf.ptr, tex, coord, idx);
                    break;

                case gli::FORMAT_RGBA64_UINT_PACK64:
                    write_texel<glm::u64vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA64_SINT_PACK64:
                    write_texel<glm::u64vec4>(buf.ptr, tex, coord, idx);
                    break;
                case gli::FORMAT_RGBA64_SFLOAT_PACK64:
                    write_texel<glm::u64vec4>(buf.ptr, tex, coord, idx);
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
                    throw std::invalid_argument("Unrecognised Save Format");
            }
        }
    }

    // Save Texture
    bool ret = gli::save(tex, filepath);
      
    return ret;
}


void add_format_enum(py::module &m) {
    py::enum_<gli::format>(m, "Format")
        .value("UNDEFINED", gli::FORMAT_UNDEFINED)
		.value("RG4_UNORM_PACK8", gli::FORMAT_RG4_UNORM_PACK8)
		.value("RGBA4_UNORM_PACK16", gli::FORMAT_RGBA4_UNORM_PACK16)
		.value("BGRA4_UNORM_PACK16", gli::FORMAT_BGRA4_UNORM_PACK16)
		.value("R5G6B5_UNORM_PACK16", gli::FORMAT_R5G6B5_UNORM_PACK16)
		.value("B5G6R5_UNORM_PACK16", gli::FORMAT_B5G6R5_UNORM_PACK16)
		.value("RGB5A1_UNORM_PACK16", gli::FORMAT_RGB5A1_UNORM_PACK16)
		.value("BGR5A1_UNORM_PACK16", gli::FORMAT_BGR5A1_UNORM_PACK16)
		.value("A1RGB5_UNORM_PACK16", gli::FORMAT_A1RGB5_UNORM_PACK16)
		.value("R8_UNORM_PACK8", gli::FORMAT_R8_UNORM_PACK8)
		.value("R8_SNORM_PACK8", gli::FORMAT_R8_SNORM_PACK8)
		.value("R8_USCALED_PACK8", gli::FORMAT_R8_USCALED_PACK8)
		.value("R8_SSCALED_PACK8", gli::FORMAT_R8_SSCALED_PACK8)
		.value("R8_UINT_PACK8", gli::FORMAT_R8_UINT_PACK8)
		.value("R8_SINT_PACK8", gli::FORMAT_R8_SINT_PACK8)
		.value("R8_SRGB_PACK8", gli::FORMAT_R8_SRGB_PACK8)
		.value("RG8_UNORM_PACK8", gli::FORMAT_RG8_UNORM_PACK8)
		.value("RG8_SNORM_PACK8", gli::FORMAT_RG8_SNORM_PACK8)
		.value("RG8_USCALED_PACK8", gli::FORMAT_RG8_USCALED_PACK8)
		.value("RG8_SSCALED_PACK8", gli::FORMAT_RG8_SSCALED_PACK8)
		.value("RG8_UINT_PACK8", gli::FORMAT_RG8_UINT_PACK8)
		.value("RG8_SINT_PACK8", gli::FORMAT_RG8_SINT_PACK8)
		.value("RG8_SRGB_PACK8", gli::FORMAT_RG8_SRGB_PACK8)
		.value("RGB8_UNORM_PACK8", gli::FORMAT_RGB8_UNORM_PACK8)
		.value("RGB8_SNORM_PACK8", gli::FORMAT_RGB8_SNORM_PACK8)
		.value("RGB8_USCALED_PACK8", gli::FORMAT_RGB8_USCALED_PACK8)
		.value("RGB8_SSCALED_PACK8", gli::FORMAT_RGB8_SSCALED_PACK8)
		.value("RGB8_UINT_PACK8", gli::FORMAT_RGB8_UINT_PACK8)
		.value("RGB8_SINT_PACK8", gli::FORMAT_RGB8_SINT_PACK8)
		.value("RGB8_SRGB_PACK8", gli::FORMAT_RGB8_SRGB_PACK8)
		.value("BGR8_UNORM_PACK8", gli::FORMAT_BGR8_UNORM_PACK8)
		.value("BGR8_SNORM_PACK8", gli::FORMAT_BGR8_SNORM_PACK8)
		.value("BGR8_USCALED_PACK8", gli::FORMAT_BGR8_USCALED_PACK8)
		.value("BGR8_SSCALED_PACK8", gli::FORMAT_BGR8_SSCALED_PACK8)
		.value("BGR8_UINT_PACK8", gli::FORMAT_BGR8_UINT_PACK8)
		.value("BGR8_SINT_PACK8", gli::FORMAT_BGR8_SINT_PACK8)
		.value("BGR8_SRGB_PACK8", gli::FORMAT_BGR8_SRGB_PACK8)
		.value("RGBA8_UNORM_PACK8", gli::FORMAT_RGBA8_UNORM_PACK8)
		.value("RGBA8_SNORM_PACK8", gli::FORMAT_RGBA8_SNORM_PACK8)
		.value("RGBA8_USCALED_PACK8", gli::FORMAT_RGBA8_USCALED_PACK8)
		.value("RGBA8_SSCALED_PACK8", gli::FORMAT_RGBA8_SSCALED_PACK8)
		.value("RGBA8_UINT_PACK8", gli::FORMAT_RGBA8_UINT_PACK8)
		.value("RGBA8_SINT_PACK8", gli::FORMAT_RGBA8_SINT_PACK8)
		.value("RGBA8_SRGB_PACK8", gli::FORMAT_RGBA8_SRGB_PACK8)
		.value("BGRA8_UNORM_PACK8", gli::FORMAT_BGRA8_UNORM_PACK8)
		.value("BGRA8_SNORM_PACK8", gli::FORMAT_BGRA8_SNORM_PACK8)
		.value("BGRA8_USCALED_PACK8", gli::FORMAT_BGRA8_USCALED_PACK8)
		.value("BGRA8_SSCALED_PACK8", gli::FORMAT_BGRA8_SSCALED_PACK8)
		.value("BGRA8_UINT_PACK8", gli::FORMAT_BGRA8_UINT_PACK8)
		.value("BGRA8_SINT_PACK8", gli::FORMAT_BGRA8_SINT_PACK8)
		.value("BGRA8_SRGB_PACK8", gli::FORMAT_BGRA8_SRGB_PACK8)
		.value("RGBA8_UNORM_PACK32", gli::FORMAT_RGBA8_UNORM_PACK32)
		.value("RGBA8_SNORM_PACK32", gli::FORMAT_RGBA8_SNORM_PACK32)
		.value("RGBA8_USCALED_PACK32", gli::FORMAT_RGBA8_USCALED_PACK32)
		.value("RGBA8_SSCALED_PACK32", gli::FORMAT_RGBA8_SSCALED_PACK32)
		.value("RGBA8_UINT_PACK32", gli::FORMAT_RGBA8_UINT_PACK32)
		.value("RGBA8_SINT_PACK32", gli::FORMAT_RGBA8_SINT_PACK32)
		.value("RGBA8_SRGB_PACK32", gli::FORMAT_RGBA8_SRGB_PACK32)
		.value("RGB10A2_UNORM_PACK32", gli::FORMAT_RGB10A2_UNORM_PACK32)
		.value("RGB10A2_SNORM_PACK32", gli::FORMAT_RGB10A2_SNORM_PACK32)
		.value("RGB10A2_USCALED_PACK32", gli::FORMAT_RGB10A2_USCALED_PACK32)
		.value("RGB10A2_SSCALED_PACK32", gli::FORMAT_RGB10A2_SSCALED_PACK32)
		.value("RGB10A2_UINT_PACK32", gli::FORMAT_RGB10A2_UINT_PACK32)
		.value("RGB10A2_SINT_PACK32", gli::FORMAT_RGB10A2_SINT_PACK32)
		.value("BGR10A2_UNORM_PACK32", gli::FORMAT_BGR10A2_UNORM_PACK32)
		.value("BGR10A2_SNORM_PACK32", gli::FORMAT_BGR10A2_SNORM_PACK32)
		.value("BGR10A2_USCALED_PACK32", gli::FORMAT_BGR10A2_USCALED_PACK32)
		.value("BGR10A2_SSCALED_PACK32", gli::FORMAT_BGR10A2_SSCALED_PACK32)
		.value("BGR10A2_UINT_PACK32", gli::FORMAT_BGR10A2_UINT_PACK32)
		.value("BGR10A2_SINT_PACK32", gli::FORMAT_BGR10A2_SINT_PACK32)
		.value("R16_UNORM_PACK16", gli::FORMAT_R16_UNORM_PACK16)
		.value("R16_SNORM_PACK16", gli::FORMAT_R16_SNORM_PACK16)
		.value("R16_USCALED_PACK16", gli::FORMAT_R16_USCALED_PACK16)
		.value("R16_SSCALED_PACK16", gli::FORMAT_R16_SSCALED_PACK16)
		.value("R16_UINT_PACK16", gli::FORMAT_R16_UINT_PACK16)
		.value("R16_SINT_PACK16", gli::FORMAT_R16_SINT_PACK16)
		.value("R16_SFLOAT_PACK16", gli::FORMAT_R16_SFLOAT_PACK16)
		.value("RG16_UNORM_PACK16", gli::FORMAT_RG16_UNORM_PACK16)
		.value("RG16_SNORM_PACK16", gli::FORMAT_RG16_SNORM_PACK16)
		.value("RG16_USCALED_PACK16", gli::FORMAT_RG16_USCALED_PACK16)
		.value("RG16_SSCALED_PACK16", gli::FORMAT_RG16_SSCALED_PACK16)
		.value("RG16_UINT_PACK16", gli::FORMAT_RG16_UINT_PACK16)
		.value("RG16_SINT_PACK16", gli::FORMAT_RG16_SINT_PACK16)
		.value("RG16_SFLOAT_PACK16", gli::FORMAT_RG16_SFLOAT_PACK16)
		.value("RGB16_UNORM_PACK16", gli::FORMAT_RGB16_UNORM_PACK16)
		.value("RGB16_SNORM_PACK16", gli::FORMAT_RGB16_SNORM_PACK16)
		.value("RGB16_USCALED_PACK16", gli::FORMAT_RGB16_USCALED_PACK16)
		.value("RGB16_SSCALED_PACK16", gli::FORMAT_RGB16_SSCALED_PACK16)
		.value("RGB16_UINT_PACK16", gli::FORMAT_RGB16_UINT_PACK16)
		.value("RGB16_SINT_PACK16", gli::FORMAT_RGB16_SINT_PACK16)
		.value("RGB16_SFLOAT_PACK16", gli::FORMAT_RGB16_SFLOAT_PACK16)
		.value("RGBA16_UNORM_PACK16", gli::FORMAT_RGBA16_UNORM_PACK16)
		.value("RGBA16_SNORM_PACK16", gli::FORMAT_RGBA16_SNORM_PACK16)
		.value("RGBA16_USCALED_PACK16", gli::FORMAT_RGBA16_USCALED_PACK16)
		.value("RGBA16_SSCALED_PACK16", gli::FORMAT_RGBA16_SSCALED_PACK16)
		.value("RGBA16_UINT_PACK16", gli::FORMAT_RGBA16_UINT_PACK16)
		.value("RGBA16_SINT_PACK16", gli::FORMAT_RGBA16_SINT_PACK16)
		.value("RGBA16_SFLOAT_PACK16", gli::FORMAT_RGBA16_SFLOAT_PACK16)
		.value("R32_UINT_PACK32", gli::FORMAT_R32_UINT_PACK32)
		.value("R32_SINT_PACK32", gli::FORMAT_R32_SINT_PACK32)
		.value("R32_SFLOAT_PACK32", gli::FORMAT_R32_SFLOAT_PACK32)
		.value("RG32_UINT_PACK32", gli::FORMAT_RG32_UINT_PACK32)
		.value("RG32_SINT_PACK32", gli::FORMAT_RG32_SINT_PACK32)
		.value("RG32_SFLOAT_PACK32", gli::FORMAT_RG32_SFLOAT_PACK32)
		.value("RGB32_UINT_PACK32", gli::FORMAT_RGB32_UINT_PACK32)
		.value("RGB32_SINT_PACK32", gli::FORMAT_RGB32_SINT_PACK32)
		.value("RGB32_SFLOAT_PACK32", gli::FORMAT_RGB32_SFLOAT_PACK32)
		.value("RGBA32_UINT_PACK32", gli::FORMAT_RGBA32_UINT_PACK32)
		.value("RGBA32_SINT_PACK32", gli::FORMAT_RGBA32_SINT_PACK32)
		.value("RGBA32_SFLOAT_PACK32", gli::FORMAT_RGBA32_SFLOAT_PACK32)
		.value("R64_UINT_PACK64", gli::FORMAT_R64_UINT_PACK64)
		.value("R64_SINT_PACK64", gli::FORMAT_R64_SINT_PACK64)
		.value("R64_SFLOAT_PACK64", gli::FORMAT_R64_SFLOAT_PACK64)
		.value("RG64_UINT_PACK64", gli::FORMAT_RG64_UINT_PACK64)
		.value("RG64_SINT_PACK64", gli::FORMAT_RG64_SINT_PACK64)
		.value("RG64_SFLOAT_PACK64", gli::FORMAT_RG64_SFLOAT_PACK64)
		.value("RGB64_UINT_PACK64", gli::FORMAT_RGB64_UINT_PACK64)
		.value("RGB64_SINT_PACK64", gli::FORMAT_RGB64_SINT_PACK64)
		.value("RGB64_SFLOAT_PACK64", gli::FORMAT_RGB64_SFLOAT_PACK64)
		.value("RGBA64_UINT_PACK64", gli::FORMAT_RGBA64_UINT_PACK64)
		.value("RGBA64_SINT_PACK64", gli::FORMAT_RGBA64_SINT_PACK64)
		.value("RGBA64_SFLOAT_PACK64", gli::FORMAT_RGBA64_SFLOAT_PACK64)
		.value("RG11B10_UFLOAT_PACK32", gli::FORMAT_RG11B10_UFLOAT_PACK32)
		.value("RGB9E5_UFLOAT_PACK32", gli::FORMAT_RGB9E5_UFLOAT_PACK32)
		.value("D16_UNORM_PACK16", gli::FORMAT_D16_UNORM_PACK16)
		.value("D24_UNORM_PACK32", gli::FORMAT_D24_UNORM_PACK32)
		.value("D32_SFLOAT_PACK32", gli::FORMAT_D32_SFLOAT_PACK32)
		.value("S8_UINT_PACK8", gli::FORMAT_S8_UINT_PACK8)
		.value("D16_UNORM_S8_UINT_PACK32", gli::FORMAT_D16_UNORM_S8_UINT_PACK32)
		.value("D24_UNORM_S8_UINT_PACK32", gli::FORMAT_D24_UNORM_S8_UINT_PACK32)
		.value("D32_SFLOAT_S8_UINT_PACK64", gli::FORMAT_D32_SFLOAT_S8_UINT_PACK64)
		.value("RGB_DXT1_UNORM_BLOCK8", gli::FORMAT_RGB_DXT1_UNORM_BLOCK8)
		.value("RGB_DXT1_SRGB_BLOCK8", gli::FORMAT_RGB_DXT1_SRGB_BLOCK8)
		.value("RGBA_DXT1_UNORM_BLOCK8", gli::FORMAT_RGBA_DXT1_UNORM_BLOCK8)
		.value("RGBA_DXT1_SRGB_BLOCK8", gli::FORMAT_RGBA_DXT1_SRGB_BLOCK8)
		.value("RGBA_DXT3_UNORM_BLOCK16", gli::FORMAT_RGBA_DXT3_UNORM_BLOCK16)
		.value("RGBA_DXT3_SRGB_BLOCK16", gli::FORMAT_RGBA_DXT3_SRGB_BLOCK16)
		.value("RGBA_DXT5_UNORM_BLOCK16", gli::FORMAT_RGBA_DXT5_UNORM_BLOCK16)
		.value("RGBA_DXT5_SRGB_BLOCK16", gli::FORMAT_RGBA_DXT5_SRGB_BLOCK16)
		.value("R_ATI1N_UNORM_BLOCK8", gli::FORMAT_R_ATI1N_UNORM_BLOCK8)
		.value("R_ATI1N_SNORM_BLOCK8", gli::FORMAT_R_ATI1N_SNORM_BLOCK8)
		.value("RG_ATI2N_UNORM_BLOCK16", gli::FORMAT_RG_ATI2N_UNORM_BLOCK16)
		.value("RG_ATI2N_SNORM_BLOCK16", gli::FORMAT_RG_ATI2N_SNORM_BLOCK16)
		.value("RGB_BP_UFLOAT_BLOCK16", gli::FORMAT_RGB_BP_UFLOAT_BLOCK16)
		.value("RGB_BP_SFLOAT_BLOCK16", gli::FORMAT_RGB_BP_SFLOAT_BLOCK16)
		.value("RGBA_BP_UNORM_BLOCK16", gli::FORMAT_RGBA_BP_UNORM_BLOCK16)
		.value("RGBA_BP_SRGB_BLOCK16", gli::FORMAT_RGBA_BP_SRGB_BLOCK16)
		.value("RGB_ETC2_UNORM_BLOCK8", gli::FORMAT_RGB_ETC2_UNORM_BLOCK8)
		.value("RGB_ETC2_SRGB_BLOCK8", gli::FORMAT_RGB_ETC2_SRGB_BLOCK8)
		.value("RGBA_ETC2_UNORM_BLOCK8", gli::FORMAT_RGBA_ETC2_UNORM_BLOCK8)
		.value("RGBA_ETC2_SRGB_BLOCK8", gli::FORMAT_RGBA_ETC2_SRGB_BLOCK8)
		.value("RGBA_ETC2_UNORM_BLOCK16", gli::FORMAT_RGBA_ETC2_UNORM_BLOCK16)
		.value("RGBA_ETC2_SRGB_BLOCK16", gli::FORMAT_RGBA_ETC2_SRGB_BLOCK16)
		.value("R_EAC_UNORM_BLOCK8", gli::FORMAT_R_EAC_UNORM_BLOCK8)
		.value("R_EAC_SNORM_BLOCK8", gli::FORMAT_R_EAC_SNORM_BLOCK8)
		.value("RG_EAC_UNORM_BLOCK16", gli::FORMAT_RG_EAC_UNORM_BLOCK16)
		.value("RG_EAC_SNORM_BLOCK16", gli::FORMAT_RG_EAC_SNORM_BLOCK16)
		.value("RGBA_ASTC_4X4_UNORM_BLOCK16", gli::FORMAT_RGBA_ASTC_4X4_UNORM_BLOCK16)
		.value("RGBA_ASTC_4X4_SRGB_BLOCK16", gli::FORMAT_RGBA_ASTC_4X4_SRGB_BLOCK16)
		.value("RGBA_ASTC_5X4_UNORM_BLOCK16", gli::FORMAT_RGBA_ASTC_5X4_UNORM_BLOCK16)
		.value("RGBA_ASTC_5X4_SRGB_BLOCK16", gli::FORMAT_RGBA_ASTC_5X4_SRGB_BLOCK16)
		.value("RGBA_ASTC_5X5_UNORM_BLOCK16", gli::FORMAT_RGBA_ASTC_5X5_UNORM_BLOCK16)
		.value("RGBA_ASTC_5X5_SRGB_BLOCK16", gli::FORMAT_RGBA_ASTC_5X5_SRGB_BLOCK16)
		.value("RGBA_ASTC_6X5_UNORM_BLOCK16", gli::FORMAT_RGBA_ASTC_6X5_UNORM_BLOCK16)
		.value("RGBA_ASTC_6X5_SRGB_BLOCK16", gli::FORMAT_RGBA_ASTC_6X5_SRGB_BLOCK16)
		.value("RGBA_ASTC_6X6_UNORM_BLOCK16", gli::FORMAT_RGBA_ASTC_6X6_UNORM_BLOCK16)
		.value("RGBA_ASTC_6X6_SRGB_BLOCK16", gli::FORMAT_RGBA_ASTC_6X6_SRGB_BLOCK16)
		.value("RGBA_ASTC_8X5_UNORM_BLOCK16", gli::FORMAT_RGBA_ASTC_8X5_UNORM_BLOCK16)
		.value("RGBA_ASTC_8X5_SRGB_BLOCK16", gli::FORMAT_RGBA_ASTC_8X5_SRGB_BLOCK16)
		.value("RGBA_ASTC_8X6_UNORM_BLOCK16", gli::FORMAT_RGBA_ASTC_8X6_UNORM_BLOCK16)
		.value("RGBA_ASTC_8X6_SRGB_BLOCK16", gli::FORMAT_RGBA_ASTC_8X6_SRGB_BLOCK16)
		.value("RGBA_ASTC_8X8_UNORM_BLOCK16", gli::FORMAT_RGBA_ASTC_8X8_UNORM_BLOCK16)
		.value("RGBA_ASTC_8X8_SRGB_BLOCK16", gli::FORMAT_RGBA_ASTC_8X8_SRGB_BLOCK16)
		.value("RGBA_ASTC_10X5_UNORM_BLOCK16", gli::FORMAT_RGBA_ASTC_10X5_UNORM_BLOCK16)
		.value("RGBA_ASTC_10X5_SRGB_BLOCK16", gli::FORMAT_RGBA_ASTC_10X5_SRGB_BLOCK16)
		.value("RGBA_ASTC_10X6_UNORM_BLOCK16", gli::FORMAT_RGBA_ASTC_10X6_UNORM_BLOCK16)
		.value("RGBA_ASTC_10X6_SRGB_BLOCK16", gli::FORMAT_RGBA_ASTC_10X6_SRGB_BLOCK16)
		.value("RGBA_ASTC_10X8_UNORM_BLOCK16", gli::FORMAT_RGBA_ASTC_10X8_UNORM_BLOCK16)
		.value("RGBA_ASTC_10X8_SRGB_BLOCK16", gli::FORMAT_RGBA_ASTC_10X8_SRGB_BLOCK16)
		.value("RGBA_ASTC_10X10_UNORM_BLOCK16", gli::FORMAT_RGBA_ASTC_10X10_UNORM_BLOCK16)
		.value("RGBA_ASTC_10X10_SRGB_BLOCK16", gli::FORMAT_RGBA_ASTC_10X10_SRGB_BLOCK16)
		.value("RGBA_ASTC_12X10_UNORM_BLOCK16", gli::FORMAT_RGBA_ASTC_12X10_UNORM_BLOCK16)
		.value("RGBA_ASTC_12X10_SRGB_BLOCK16", gli::FORMAT_RGBA_ASTC_12X10_SRGB_BLOCK16)
		.value("RGBA_ASTC_12X12_UNORM_BLOCK16", gli::FORMAT_RGBA_ASTC_12X12_UNORM_BLOCK16)
		.value("RGBA_ASTC_12X12_SRGB_BLOCK16", gli::FORMAT_RGBA_ASTC_12X12_SRGB_BLOCK16)
		.value("RGB_PVRTC1_8X8_UNORM_BLOCK32", gli::FORMAT_RGB_PVRTC1_8X8_UNORM_BLOCK32)
		.value("RGB_PVRTC1_8X8_SRGB_BLOCK32", gli::FORMAT_RGB_PVRTC1_8X8_SRGB_BLOCK32)
		.value("RGB_PVRTC1_16X8_UNORM_BLOCK32", gli::FORMAT_RGB_PVRTC1_16X8_UNORM_BLOCK32)
		.value("RGB_PVRTC1_16X8_SRGB_BLOCK32", gli::FORMAT_RGB_PVRTC1_16X8_SRGB_BLOCK32)
		.value("RGBA_PVRTC1_8X8_UNORM_BLOCK32", gli::FORMAT_RGBA_PVRTC1_8X8_UNORM_BLOCK32)
		.value("RGBA_PVRTC1_8X8_SRGB_BLOCK32", gli::FORMAT_RGBA_PVRTC1_8X8_SRGB_BLOCK32)
		.value("RGBA_PVRTC1_16X8_UNORM_BLOCK32", gli::FORMAT_RGBA_PVRTC1_16X8_UNORM_BLOCK32)
		.value("RGBA_PVRTC1_16X8_SRGB_BLOCK32", gli::FORMAT_RGBA_PVRTC1_16X8_SRGB_BLOCK32)
		.value("RGBA_PVRTC2_4X4_UNORM_BLOCK8", gli::FORMAT_RGBA_PVRTC2_4X4_UNORM_BLOCK8)
		.value("RGBA_PVRTC2_4X4_SRGB_BLOCK8", gli::FORMAT_RGBA_PVRTC2_4X4_SRGB_BLOCK8)
		.value("RGBA_PVRTC2_8X4_UNORM_BLOCK8", gli::FORMAT_RGBA_PVRTC2_8X4_UNORM_BLOCK8)
		.value("RGBA_PVRTC2_8X4_SRGB_BLOCK8", gli::FORMAT_RGBA_PVRTC2_8X4_SRGB_BLOCK8)
		.value("RGB_ETC_UNORM_BLOCK8", gli::FORMAT_RGB_ETC_UNORM_BLOCK8)
		.value("RGB_ATC_UNORM_BLOCK8", gli::FORMAT_RGB_ATC_UNORM_BLOCK8)
		.value("RGBA_ATCA_UNORM_BLOCK16", gli::FORMAT_RGBA_ATCA_UNORM_BLOCK16)
		.value("RGBA_ATCI_UNORM_BLOCK16", gli::FORMAT_RGBA_ATCI_UNORM_BLOCK16)
		.value("L8_UNORM_PACK8", gli::FORMAT_L8_UNORM_PACK8)
		.value("A8_UNORM_PACK8", gli::FORMAT_A8_UNORM_PACK8)
		.value("LA8_UNORM_PACK8", gli::FORMAT_LA8_UNORM_PACK8)
		.value("L16_UNORM_PACK16", gli::FORMAT_L16_UNORM_PACK16)
		.value("A16_UNORM_PACK16", gli::FORMAT_A16_UNORM_PACK16)
		.value("LA16_UNORM_PACK16", gli::FORMAT_LA16_UNORM_PACK16)
		.value("BGR8_UNORM_PACK32", gli::FORMAT_BGR8_UNORM_PACK32)
		.value("BGR8_SRGB_PACK32", gli::FORMAT_BGR8_SRGB_PACK32)
		.value("RG3B2_UNORM_PACK8", gli::FORMAT_RG3B2_UNORM_PACK8)
        .export_values();
}


PYBIND11_MODULE(_core, m) {
    m.doc() = "Wrapper for reading gli textures";
    add_format_enum(m);
    m.def("load", &load, "Load texture file and return as NumPy array");
    m.def("save", &save, "Save texture file and return as NumPy array");
#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}

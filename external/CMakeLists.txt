# STB Image
# --------------------------------------------------------------------------------------------------
FetchContent_Declare(
  stb
  GIT_REPOSITORY https://github.com/nothings/stb.git
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)
FetchContent_MakeAvailable(stb)
add_library(stb_lib INTERFACE)
target_include_directories(stb_lib INTERFACE ${CMAKE_BINARY_DIR}/_deps/stb-src/)


# GLI
# --------------------------------------------------------------------------------------------------
FetchContent_Declare(
  gli
  GIT_REPOSITORY https://github.com/g-truc/gli.git
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)
FetchContent_MakeAvailable(gli)
add_library(gli_lib INTERFACE)
target_include_directories(gli_lib INTERFACE ${CMAKE_BINARY_DIR}/_deps/gli-src/ 
                                             ${CMAKE_BINARY_DIR}/_deps/gli-src/external)
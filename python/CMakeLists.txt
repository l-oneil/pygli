pybind11_add_module(pygli pygli.cpp)
target_link_libraries(pygli PUBLIC gli_lib)
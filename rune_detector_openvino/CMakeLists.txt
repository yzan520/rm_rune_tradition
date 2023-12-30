cmake_minimum_required(VERSION 3.25)
project(rune_detector_openvino)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON) # 将当前目录包含在头文件搜索路径中
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 要求编译器严格遵循所设定的 C++ 标准
set(CMAKE_CXX_EXTENSIONS OFF) # 禁用编译器的 C++ 扩展功能

# sub library
add_subdirectory(src/rune_detector)
add_subdirectory(src/solver)
add_subdirectory(src/rune_auto_aim)


add_executable(rune_detector_openvino src/main.cpp)
target_link_libraries(rune_detector_openvino
        rune_auto_aim
        )

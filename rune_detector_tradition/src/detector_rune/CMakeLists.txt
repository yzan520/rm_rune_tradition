cmake_minimum_required(VERSION 3.15)
project(rune_detector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp include/*.h)
add_library(rune_detector STATIC ${sources})
set_target_properties(rune_detector PROPERTIES
    LINKER_LANGUAGE CXX
)
target_include_directories(rune_detector PUBLIC include)

find_package(OpenCV REQUIRED)
find_package(glog 0.6.0 REQUIRED)
find_package(fmt REQUIRED)
find_package(Eigen3 REQUIRED)

target_link_libraries(rune_detector PUBLIC
        ${OpenCV_LIBS}
        glog::glog
        solver
        fmt::fmt
        Eigen3::Eigen
        serial_port
        )
cmake_minimum_required(VERSION 3.16)
project(rm_rune_detection LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src/detector_rune)
add_subdirectory(src/HikDriver)
add_subdirectory(src/google_logger)
add_subdirectory(src/vision_debug_widgets)
add_subdirectory(src/buff_auto_aim)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(rm_rune_detection PUBLIC
        vision_debug_widgets
        buff_auto_aim
        )







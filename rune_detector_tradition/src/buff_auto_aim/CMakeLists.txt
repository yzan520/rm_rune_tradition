set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp include/*.h)
find_package(Qt5 COMPONENTS Core Gui Widgets SerialPort REQUIRED)
add_library(buff_auto_aim STATIC ${sources})
set_target_properties(buff_auto_aim PROPERTIES
        LINKER_LANGUAGE CXX
        )
target_include_directories(buff_auto_aim PUBLIC include)
target_include_directories(buff_auto_aim PUBLIC ${Qt5_INCLUDE_DIRS})
target_link_libraries(buff_auto_aim PUBLIC
        rune_detector
        google_logger
        hik_driver
        hik_ui
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::SerialPort
        solver
        serial_port
        )





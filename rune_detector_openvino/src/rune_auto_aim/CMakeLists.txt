file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp include/*hpp)
add_library(rune_auto_aim STATIC ${sources})
set_target_properties(rune_auto_aim PROPERTIES
        LINKER_LANGUAGE CXX
        )
target_include_directories(rune_auto_aim PUBLIC include)

target_link_libraries(rune_auto_aim PUBLIC
        rune_detector
        solver
        )
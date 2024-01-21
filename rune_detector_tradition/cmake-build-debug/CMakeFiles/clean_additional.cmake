# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "src/buff_auto_aim/CMakeFiles/buff_auto_aim_autogen.dir/AutogenUsed.txt"
  "src/buff_auto_aim/CMakeFiles/buff_auto_aim_autogen.dir/ParseCache.txt"
  "src/buff_auto_aim/buff_auto_aim_autogen"
  "src/serial_port/CMakeFiles/serial_port_autogen.dir/AutogenUsed.txt"
  "src/serial_port/CMakeFiles/serial_port_autogen.dir/ParseCache.txt"
  "src/serial_port/serial_port_autogen"
  "src/vision_debug_widgets/CMakeFiles/vision_debug_widgets_autogen.dir/AutogenUsed.txt"
  "src/vision_debug_widgets/CMakeFiles/vision_debug_widgets_autogen.dir/ParseCache.txt"
  "src/vision_debug_widgets/vision_debug_widgets_autogen"
  )
endif()

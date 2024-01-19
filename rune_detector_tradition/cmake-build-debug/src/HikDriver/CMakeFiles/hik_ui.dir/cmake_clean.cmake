file(REMOVE_RECURSE
  "libhik_ui.a"
  "libhik_ui.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/hik_ui.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

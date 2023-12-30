file(REMOVE_RECURSE
  "libsolver.a"
  "libsolver.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/solver.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

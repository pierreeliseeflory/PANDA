if(NOT NTL_LIB)
  message(FATAL_ERROR "ntl library not found.  Rerun cmake with -DCMAKE_PREFIX_PATH=\"<path to lib1>;<path to lib2>\"")
endif()

add_executable(polynomial polynomial.cpp)

if (NTL_FOUND)
  include_directories(${NTL_INCLUDE_DIRS})
  set(NTL ${NTL} ${NTL_LIBRARIES})
  target_link_libraries(polynomial ${NTL_LIBRARIES} ${GMP_LIBRARIES} m pthread)
endif (NTL_FOUND)
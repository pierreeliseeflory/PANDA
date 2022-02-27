# NTL needs GMP 3.1.1 or newer, this script will fail if an old version is
# detected

find_package( GMP REQUIRED )

find_library(m REQUIRED)

find_path(NTL_INCLUDE_DIR
          NAMES NTL/ZZ.h
          HINTS ENV NTL_INC_DIR
                ENV NTL_DIR
          PATH_SUFFIXES include
          DOC "The directory containing the NTL include files"
          )

find_library(NTL_LIBRARY
              NAMES ntl
              HINTS ENV NTL_LIB_DIR
                    ENV NTL_DIR
              PATH_SUFFIXES lib
              DOC "Path to the NTL library"
            )

set ( NTL_INCLUDE_DIRS ${NTL_INCLUDE_DIR} )
set ( NTL_LIBRARIES ${NTL_LIBRARY} )

get_filename_component(NTL_LIBRARIES_DIR ${NTL_LIBRARIES} PATH CACHE )

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args( NTL
                                    DEFAULT_MSG
                                    NTL_LIBRARY
                                    NTL_INCLUDE_DIR )

mark_as_advanced( NTL_INCLUDE_DIR NTL_LIBRARY )
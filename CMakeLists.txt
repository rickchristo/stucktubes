cmake_minimum_required (VERSION 2.8)
enable_testing()
project (StuckTubes)

set (StuckTubes_VERSION_MAJOR 0)
set (StuckTubes_VERSION_MINOR 1)

configure_file (
    "${PROJECT_SOURCE_DIR}/src/StuckTubesConfig.h.in"
    "${PROJECT_SOURCE_DIR}/include/StuckTubesConfig.h"
)

include_directories("${PROJECT_SOURCE_DIR}/include")
add_subdirectory(src bin)
#add_subdirectory(bin)

#install(TARGETS StuckTubes DESTINATION bin)
#install(FILES "${PROJECT_BINARY_DIR}/src/StuckTubesConfig.h"
#            DESTINATION include)


#~~~~~~~~~~~~CMake CTests~~~~~~~~~~~~
#add_test(StuckTubesRuns StuckTubes)

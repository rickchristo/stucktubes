cmake_minimum_required (VERSION 2.8)
project (StuckTubes)

set (StuckTubes_VERSION_MAJOR 0)
set (StuckTubes_VERSION_MINOR 1)

configure_file (
    "${PROJECT_SOURCE_DIR}/src/StuckTubesConfig.h.in"
    "${PROJECT_SOURCE_DIR}/src/StuckTubesConfig.h"
)

include_directories("${PROJECT_SOURCE_DIR}/src")
add_subdirectory(src)
add_subdirectory(bin)


#find_package (OpenCV REQUIRED)
#add_executable (${PROJECT_SOURCE_DIR}/src/StuckTubes ${PROJECT_SOURCE_DIR}/src/StuckTubes.cpp)
#target_link_libraries (${PROJECT_SOURCE_DIR}/src/StuckTubes ${OpenCV_LIBS})

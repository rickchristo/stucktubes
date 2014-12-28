find_package(OpenCV REQUIRED)
add_executable(../bin/StuckTubes StuckTubes.cpp)
target_link_libraries(../bin/StuckTubes ${OpenCV_LIBS})

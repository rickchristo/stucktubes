find_package(OpenCV REQUIRED)
add_executable(StuckTubes.out StuckTubes.cpp)
#install(TARGETS StuckTubes DESTINATION bin)
target_link_libraries(StuckTubes.out ${OpenCV_LIBS})

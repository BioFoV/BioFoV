cmake_minimum_required(VERSION 2.8)
project( Framework )
find_package( OpenCV REQUIRED )
add_executable( Framework Framework.cpp )
target_link_libraries( Framework ${OpenCV_LIBS} )

SET(CMAKE_CXX_FLAGS "-Wall")
add_definitions(${CMAKE_CXX_FLAGS})

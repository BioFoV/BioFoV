cmake_minimum_required(VERSION 2.8)
project( Framework )
find_package( OpenCV REQUIRED )

SET(CPP_FILES
	Framework.cpp
	Video/Video.cpp
	Feature/Feature.cpp
	Frame/Frame.cpp
	Individual/Individual.cpp
	Snapshot/Snapshot.cpp
	Video/Video.cpp)

add_executable( Framework ${CPP_FILES} )
target_link_libraries( Framework ${OpenCV_LIBS} )

SET(CMAKE_CXX_FLAGS "-Wall")
add_definitions(${CMAKE_CXX_FLAGS})

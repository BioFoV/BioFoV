cmake_minimum_required(VERSION 2.8)
project( Framework )
find_package( OpenCV REQUIRED )

SET(CPP_FILES
	Framework.cpp
	Video/Video.cpp
	Feature/Feature.cpp
	Frame/Frame.cpp
	Event/Event.cpp
	Individual/Individual.cpp
	Snapshot/Snapshot.cpp
	Video/Video.cpp
	Video/BackgroundSubtraction.cpp)

add_executable( Framework ${CPP_FILES} )
target_link_libraries( Framework ${OpenCV_LIBS} )

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Linux specific code
    MESSAGE("Building for Linux")
    SET(OperatingSystem "Linux")
    SET(CMAKE_CXX_FLAGS "-Wall -static-libgcc -static-libstdc++")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # Windows specific code
    MESSAGE("Building for Windows")
    SET(OperatingSystem "Windows")
    SET(CMAKE_CXX_FLAGS "-Wall -static-libgcc -static -lstdc++")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

add_definitions(${CMAKE_CXX_FLAGS})

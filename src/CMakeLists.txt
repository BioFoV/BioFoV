cmake_minimum_required(VERSION 2.8)
project( Framework )
find_package( OpenCV REQUIRED )

# All files in src will be used, so be careful what you put there...
File(GLOB_RECURSE SRC_FILES *.cpp)
File(GLOB_RECURSE HEAD_FILES *.hpp)

add_executable( Framework ${SRC_FILES} )
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

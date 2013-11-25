#due to qt5 restrictions cmake has to be >= 2.8.9
cmake_minimum_required(VERSION 2.8.9)
project( Framework )

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Linux specific code
    MESSAGE("Building for Linux")
    SET(OperatingSystem "Linux")
    SET(CMAKE_CXX_FLAGS ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} )
    SET(CMAKE_PREFIX_PATH "../third-party/opencv/linux-install/" "../third-party/qt/linux-install/lib/cmake/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # Windows specific code
    MESSAGE("Building for Windows")
    SET(OperatingSystem "Windows")
    SET(CMAKE_CXX_FLAGS "-Wall -static-libgcc -static -lstdc++")

ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

find_package( OpenCV REQUIRED )
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

#install(TARGETS hello_cmake DESTINATION /usr/bin)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR} )

# All files in src will be used, so be careful what you put there...
File(GLOB_RECURSE SRCS *.cpp)
File(GLOB_RECURSE HEADERS *.hpp)
File(GLOB_RECURSE FORMS *.ui)
#File(GLOB_RECURSE RESOURCES *.qrc)

qt5_wrap_ui(UI_HEADERS ${FORMS})

add_executable( Framework ${SRCS} ${UI_HEADERS} )
target_link_libraries( Framework ${OpenCV_LIBS} )
target_link_libraries( Framework ${QT_LIBRARIES} )

qt5_use_modules(Framework Core Gui Widgets)

add_definitions(${CMAKE_CXX_FLAGS})

